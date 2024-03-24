#define _CRTDBG_MAP_ALLOC

#include "ui.h"
#include "teste.h"

#include <stdio.h>
#include <crtdbg.h>

/*
Administratorul unei farmacii are nevoie de o aplicatie care permite gestiunea stocului din farmacie.
Fiecare medicament din stoc are un cod unic, un nume,concentratie, cantitate disponibila in stoc.
Creati o aplicatie care permite:
 a) Adaugare de noi medicamente. Daca medicamentul este deja in stoc trebuie actualizat cantitatea
 b) Actualizare medicamente (modificare nume, concentratie pentru un medicament din stoc)
 c) Stergerea intregului stoc dintr-un medicament dat
 d) Vizualizare medicamente din stoc, ordonat dupa nume, cantitate (crescator/descrescator)
 e) Vizualizare lista de medicamente filtrate dupa un criteriu. Medicamente unde stocul disponibil este
mai mic decat o valoare data; medicamente cu numele incepand cu o litera data.
*/

void testAll() {
	
	test_createMedicament();
	test_adaugaCantitate();
	test_compCantitate();
	test_compNume();
	test_destroyMedicament();
	test_egalCod();
	test_egalMedicamente();
	test_egalModify();
	test_filterCantitate();
	test_filterNume();
	test_returnCod();
	test_stergeCantitate();
	test_valideazaMedicament();
	test_verifStoc();
	
	test_createEmpty();
	test_destroy();
	test_extind();
	test_add();
	test_modify();
	test_deleteStoc();
	test_copyList();

	test_addMedicament();
	test_modifyMedicament();
	test_deleteMedicament();
	test_getAllMedicamente();
	test_sort();
	test_copyListCantitate();
    test_copyListNume();
	
}


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	testAll();
	run();

	_CrtDumpMemoryLeaks();
	return 0;

}