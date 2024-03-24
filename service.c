#include "service.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

Service createService() {
	Service lista;
	lista.actual = createEmpty((destroy_fct)destroyMedicament);
	return lista;
}

int addMedicament(Service* lista, int cod, char* nume, int concentratie, int cantitate) {
	
	Medicament* m = createMedicament(cod, nume, concentratie, cantitate);
	
	int succes = valideazaMedicament(m);
	if (succes != 0) {
		free(m->nume);
		free(m);
		return succes;
	}

	return add(lista->actual, (ElemType* ) m, (egale_fct) egalMedicamente, (egale_coduri) egalCod, (cantitate_fct) adaugaCantitate);
}

int modifyMedicament(Service* lista, int cod, char* nume_nou, int concentratie_noua) {
	
	Medicament *m = createMedicament(cod, nume_nou, concentratie_noua, 0);

	int succes = valideazaMedicament(m);
	if (succes != 0) {
		free(m->nume);
		free(m);
		return succes;
	}

	return modify(lista->actual, (ElemType* ) m, (egal_modify) egalModify, (cantitate_fct) adaugaCantitate);

}

int deleteMedicament(Service* lista, int cod) {

	if (cod <= 0)
		return 1;

	return deleteStoc(lista->actual, cod, (return_cod) returnCod, (sterge_cant) stergeCantitate);
}

Repo* getAllMedicamente(Service* lista) {

	return copyList(lista->actual, (copy_fct) copyMedicament);
}

Repo* sort(Repo* lista, int crescator, sort_fct cmp1, sort_fct cmp2) {
	Repo* list = copyList(lista, (copy_fct) copyMedicament);

	for (int i = 0; i < list->lungime - 1; ++i) 
		for (int j = i + 1; j < list->lungime; ++j) {
			if ((crescator && cmp1(list->elemente[i], list->elemente[j]) > 0) ||
				(!crescator && cmp1(list->elemente[i], list->elemente[j]) < 0)) {
				ElemType* temporar = list->elemente[i];
				list->elemente[i] = list->elemente[j];
				list->elemente[j] = temporar;
			}
			else if (cmp1(list->elemente[i], list->elemente[j]) == 0) {
				if ((crescator && cmp2(list->elemente[i], list->elemente[j]) == 1) ||
					(!crescator && cmp2(list->elemente[i], list->elemente[j]) == 0)) {
					ElemType* temporar = list->elemente[i];
					list->elemente[i] = list->elemente[j];
					list->elemente[j] = temporar;
				}
			}
		}
		
	return list;
}

Repo* copyListCantitate(Repo* lista, int cantitate, filter_fct_cantitate filter) {

	Repo* copie = createEmpty(lista->dest);

	for (int i = 0; i < lista->lungime; ++i) {
		if (filter(lista->elemente[i], cantitate)) {
			add(copie, (ElemType* ) copyMedicament(lista->elemente[i]), (egale_fct) egalMedicamente, (egale_coduri) egalCod,
				(cantitate_fct) adaugaCantitate);
		}
	}
	return copie;
}

Repo* copyListNume(Repo* lista, char litera, filter_fct_nume filter) {

	Repo* copie = createEmpty(lista->dest);

	for (int i = 0; i < lista->lungime; ++i) {
		if (filter(lista->elemente[i], litera)) {
			add(copie, (ElemType* )copyMedicament(lista->elemente[i]), (egale_fct) egalMedicamente, (egale_fct) egalCod, 
				(cantitate_fct) adaugaCantitate);
		}
	}
	return copie;
}

void destroyService(Service* lista) {
	destroy(lista->actual);
}
