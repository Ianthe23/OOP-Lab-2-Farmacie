#include "farmacie.h"
#include "repo.h"
#include "service.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/// 
/// TESTE DOMENIU
///

void test_createMedicament() {
    Medicament* m = createMedicament(1, "Paracetamol", 500, 20);
    assert(m != NULL);
    assert(m->cod == 1);
    assert(strcmp(m->nume, "Paracetamol") == 0);
    assert(m->concentratie == 500);
    assert(m->cantitate == 20);
    destroyMedicament(m);
}

void test_destroyMedicament() {
    Medicament* m = createMedicament(1, "Paracetamol", 500, 20);
    destroyMedicament(m);
  
    assert(m->cod != 1);
    assert(m->concentratie != 500);
    assert(m->cantitate != 20);
}

void test_valideazaMedicament() {
    Medicament* m = createMedicament(1, "Paracetamol", 500, 20);
    assert(valideazaMedicament(m) == 0);
    
    m->cod = 0;
    assert(valideazaMedicament(m) == 1);
    m->cod = 1; 
    free(m->nume);
    m->nume = "";
    assert(valideazaMedicament(m) == 2);
    free(m);

    m = createMedicament(1, "Paracetamol", 500, 20);
    m->concentratie = -500;
    assert(valideazaMedicament(m) == 3);
    m->concentratie = 500; 
    m->cantitate = -20;
    assert(valideazaMedicament(m) == 4);
    destroyMedicament(m);
}

void test_egalCod() {
    Medicament* m1 = createMedicament(1, "Paracetamol", 500, 20);
    Medicament* m2 = createMedicament(1, "Aspirin", 300, 15);
    Medicament* m3 = createMedicament(2, "Ibuprofen", 400, 30);
    assert(egalCod(m1, m2) == 1);
    assert(egalCod(m1, m3) == 0);
    destroyMedicament(m1);
    destroyMedicament(m2);
    destroyMedicament(m3);
}

void test_egalMedicamente() {
    Medicament* m1 = createMedicament(1, "Paracetamol", 500, 20);
    Medicament* m2 = createMedicament(1, "Paracetamol", 500, 20);
    Medicament* m3 = createMedicament(2, "Ibuprofen", 400, 30);
    assert(egalMedicamente(m1, m2) == 1);
    assert(egalMedicamente(m1, m3) == 0);
    destroyMedicament(m1);
    destroyMedicament(m2);
    destroyMedicament(m3);
}

void test_egalModify() {
    Medicament* m1 = createMedicament(1, "Paracetamol", 500, 20);
    Medicament* m2 = createMedicament(1, "Paracetamol", 500, 20);
    Medicament* m3 = createMedicament(2, "Ibuprofen", 400, -30);
    assert(egalModify(m1, m2) == 1);
    assert(egalModify(m1, m3) == 0);
    destroyMedicament(m1);
    destroyMedicament(m2);
    destroyMedicament(m3);
}

void test_adaugaCantitate() {
    Medicament* m1 = createMedicament(1, "Paracetamol", 500, 20);
    Medicament* m2 = createMedicament(2, "Ibuprofen", 400, 30);
    adaugaCantitate(m1, m2);
    assert(m1->cantitate == 50);
    destroyMedicament(m1);
    destroyMedicament(m2);
}

void test_returnCod() {
    Medicament* m = createMedicament(1, "Paracetamol", 500, 20);
    assert(returnCod(m) == 1);
    destroyMedicament(m);
}

void test_verifStoc() {
    Medicament* m1 = createMedicament(1, "Paracetamol", 500, 20);
    Medicament* m2 = createMedicament(2, "Ibuprofen", 400, -30);
    assert(verifStoc(m1) == 1);
    assert(verifStoc(m2) == 0);
    destroyMedicament(m1);
    destroyMedicament(m2);
}

void test_stergeCantitate() {
    Medicament* m = createMedicament(1, "Paracetamol", 500, 20);
    stergeCantitate(m);
    assert(m->cantitate == 0);
    destroyMedicament(m);
}

void test_compNume() {
    Medicament* m1 = createMedicament(1, "Paracetamol", 500, 20);
    Medicament* m2 = createMedicament(2, "Ibuprofen", 400, 30);
    assert(compNume(m1, m2) > 0);
    assert(compNume(m2, m1) < 0);
    destroyMedicament(m1);
    destroyMedicament(m2);
}

void test_compCantitate() {
    Medicament* m1 = createMedicament(1, "Paracetamol", 500, 20);
    Medicament* m2 = createMedicament(2, "Ibuprofen", 400, 30);
    assert(compCantitate(m1, m2) == 0);
    assert(compCantitate(m2, m1) == 1);
    destroyMedicament(m1);
    destroyMedicament(m2);
}

void test_filterNume() {
    Medicament* m = createMedicament(1, "Paracetamol", 500, 20);
    assert(filterNume(m, 'P') == 1);
    assert(filterNume(m, 'I') == 0);
    destroyMedicament(m);
}

void test_filterCantitate() {
    Medicament* m1 = createMedicament(1, "Paracetamol", 500, 20);
    Medicament* m2 = createMedicament(2, "Ibuprofen", 400, -30);
    assert(filterCantitate(m1, 30) == 1);
    assert(filterCantitate(m2, 0) == 0);
    destroyMedicament(m1);
    destroyMedicament(m2);
}

///
/// TESTE REPO
/// 


void test_createEmpty() {
    Repo* repo = createEmpty(&destroyMedicament);
    assert(repo != NULL);
    assert(repo->capacitate == 2);
    assert(repo->lungime == 0);
    destroy(repo);
}

void test_destroy() {
    Repo* repo = createEmpty(&destroyMedicament);
    Medicament* m1 = createMedicament(1, "Paracetamol", 500, 20);
    Medicament* m2 = createMedicament(2, "Ibuprofen", 400, 30);
    add(repo, (ElemType* )m1, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);
    add(repo, (ElemType* )m2, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);

    destroy(repo);

    assert(repo->lungime != 2);
    assert(repo->capacitate != 2);
}

void test_extind() {
    Repo* repo = createEmpty(&destroyMedicament);
    assert(repo->capacitate == 2);

    for (int i = 0; i < 3; ++i) {
        Medicament* m = createMedicament(i + 1, "Med", 100, 10);
        add(repo, (ElemType* )m, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate); \
    }

    assert(repo->capacitate == 4);

    destroy(repo);

}

void test_add() {
    Repo* repo = createEmpty(&destroyMedicament);
    Medicament* m1 = createMedicament(1, "Paracetamol", 500, 20);
    Medicament* m2 = createMedicament(2, "Ibuprofen", 400, 30);
    assert(add(repo, (ElemType* )m1, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate) == 0);
    assert(add(repo, (ElemType* )m2, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate) == 0);

    Medicament* m3 = createMedicament(1, "Paracetamol", 500, 10);
    assert(add(repo, (ElemType* )m3, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate) == 0);
    Medicament* m4 = createMedicament(1, "Paracetamol", 400, 10);
    assert(add(repo, (ElemType* )m4, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate) == 1);
    assert(returnCod(repo->elemente[0]) == 1);
    assert(repo->lungime == 2);

    destroy(repo);
}

void test_modify() {
    Repo* repo = createEmpty(&destroyMedicament);
    Medicament* m1 = createMedicament(1, "Paracetamol", 500, 20);
    add(repo, (ElemType* )m1, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);

    Medicament* m2 = createMedicament(1, "Paracetamol", 500, 10);
    assert(modify(repo, (ElemType* )m2, (egal_modify)egalModify, (cantitate_fct)adaugaCantitate) == 0);

    Medicament* m3 = createMedicament(2, "Paracetamol", 500, 10);
    assert(modify(repo, (ElemType* )m3, (egal_modify)egalModify, (cantitate_fct)adaugaCantitate) == 1);

    destroy(repo);
}

void test_deleteStoc() {
    Repo* repo = createEmpty(&destroyMedicament);
    Medicament* m1 = createMedicament(1, "Paracetamol", 500, 20);
    Medicament* m2 = createMedicament(2, "Ibuprofen", 400, 30);
    add(repo, (ElemType* )m1, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);
    add(repo, (ElemType* )m2, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);

    assert(deleteStoc(repo, 1, (return_cod)returnCod, (sterge_cant)stergeCantitate) == 0);
    assert(repo->lungime == 2);

    assert(deleteStoc(repo, 3, (return_cod)returnCod, (sterge_cant)stergeCantitate) == 1);

    destroy(repo);
}

void test_copyList() {
    Repo* repo = createEmpty(&destroyMedicament);
    Medicament* m1 = createMedicament(1, "Paracetamol", 500, 20);
    Medicament* m2 = createMedicament(2, "Ibuprofen", 400, 30);
    add(repo, (ElemType* )m1, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);
    add(repo, (ElemType* )m2, (egale_fct)egalMedicamente, (egale_coduri)egalCod, (cantitate_fct)adaugaCantitate);

    Repo* copiedRepo = copyList(repo, (copy_fct)copyMedicament);
    assert(copiedRepo->lungime == 2);

    destroy(repo);
    destroy(copiedRepo);

}

///
/// TESTE SERVICE
/// 

void test_addMedicament() {

    Service lista = createService();
    destroyService(&lista);

    lista = createService();
    assert(addMedicament(&lista, 1, "Paracetamol", 500, 20) == 0);

    assert(addMedicament(&lista, 2, "Ibuprofen", -400, 30) == 3);

    destroyService(&lista);
}

void test_modifyMedicament() {
    Service lista = createService();
    addMedicament(&lista, 1, "Paracetamol", 500, 20);

    assert(modifyMedicament(&lista, 1, "Aspirin", 300) == 0);

    assert(modifyMedicament(&lista, 1, "Paracetamol", -500) == 3);

    destroyService(&lista);
}

void test_deleteMedicament() {
    Service lista = createService();
    addMedicament(&lista, 1, "Paracetamol", 500, 20);

    assert(deleteMedicament(&lista, 1) == 0);

    assert(deleteMedicament(&lista, -1) == 1);

    destroyService(&lista);
}

void test_getAllMedicamente() {
    Service lista = createService();
    addMedicament(&lista, 1, "Paracetamol", 500, 20);
    addMedicament(&lista, 2, "Ibuprofen", 400, 30);

    Repo* allMedicaments = getAllMedicamente(&lista);
    assert(allMedicaments->lungime == 2);

    destroyService(&lista);
    destroy(allMedicaments);
}

void test_sort() {
    Service lista = createService();

    addMedicament(&lista, 1, "Paracetamol", 500, 20);
    addMedicament(&lista, 2, "Ibuprofen", 400, 30);

    Repo* sortedAsc = sort(lista.actual, 1, (sort_fct)compNume, (sort_fct)compCantitate);
    assert(((Medicament*)sortedAsc->elemente[0])->cantitate == 30);

    Repo* sortedDesc = sort(lista.actual, 0, (sort_fct)compNume, (sort_fct)compCantitate);
    assert(((Medicament*)sortedDesc->elemente[0])->cantitate == 20);

    destroy(sortedAsc);
    destroy(sortedDesc);

    addMedicament(&lista, 3, "Paracetamol", 200, 10);
    sortedAsc = sort(lista.actual, 1, (sort_fct)compNume, (sort_fct)compCantitate);
    assert(((Medicament*)sortedAsc->elemente[0])->cantitate == 30);

    sortedDesc = sort(lista.actual, 0, (sort_fct)compNume, (sort_fct)compCantitate);
    assert(((Medicament*)sortedDesc->elemente[0])->cantitate == 20);

    destroyService(&lista);
    destroy(sortedAsc);
    destroy(sortedDesc);
}

void test_copyListCantitate() {
    Service lista = createService();
    addMedicament(&lista, 1, "Paracetamol", 500, 20);
    addMedicament(&lista, 2, "Ibuprofen", 400, 30);

    Repo* copiedList = copyListCantitate(lista.actual, 20, (filter_fct_cantitate)filterCantitate);
    assert(copiedList->lungime == 0);

    destroy(copiedList);
    copiedList = copyListCantitate(lista.actual, 30, (filter_fct_cantitate)filterCantitate);
    assert(copiedList->lungime == 1);

    destroyService(&lista);
    destroy(copiedList);
}

void test_copyListNume() {
    Service lista = createService();
    addMedicament(&lista, 1, "Paracetamol", 500, 20);
    addMedicament(&lista, 2, "Ibuprofen", 400, 30);

    Repo* copiedList = copyListNume(lista.actual, 'P', (filter_fct_nume)filterNume);
    assert(copiedList->lungime == 1);

    destroyService(&lista);
    destroy(copiedList);
}