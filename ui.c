#include "farmacie.h"
#include "repo.h"
#include "service.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void printMedicament(Medicament* m) {
	printf("\033[1;33mCod\033[0m: %d  ", m->cod);
	printf("\033[1;33mNume\033[0m: %s  ", m->nume);
	printf("\033[1;33mConcentratie\033[0m: %d  ", m->concentratie);
	printf("\033[1;33mCantitate\033[0m: %d\n", m->cantitate);
}

void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {
		// scapam de input-ul nedorit
	}
}

void readMedicament(Service* lista) {

	int cod = -1, cantitate = -1, concentratie = -1;
	char nume[31] = "";

	printf("\033[1;36mIntroduceti medicamentul\033[0m:\n");
	printf("Cod: ");
	scanf_s("%d", &cod);
	clearInputBuffer();

	printf("Nume: ");
	scanf_s("%s", nume, 31);

	printf("Concentratie: ");
	scanf_s("%d", &concentratie);
	clearInputBuffer();

	printf("Cantitate: ");
	scanf_s("%d", &cantitate);
	clearInputBuffer();

	int error = addMedicament(lista, cod, nume, concentratie, cantitate);
	if (error != 0) {
		printf("\033[1;31mMedicament invalid!\033[0m\n");
	}
	else {
		printf("\033[1;32mMedicament adaugat!\033[0m\n");
	}

}

void modifyMedicamentDat(Service* lista) {

	int cod, cantitate_noua, concentratie_noua;
	cod = -1;
	cantitate_noua = -1, 
	concentratie_noua = -1;
	char nume_nou[31];

	printf("\033[1;36mIntroduceti codul medicamentului\033[0m: ");
	scanf_s("%d", &cod);
	clearInputBuffer();
	printf("\n");

	printf("Numele nou: ");
	scanf_s("%s", nume_nou, 31);

	printf("Concentratia noua: ");
	scanf_s("%d", &concentratie_noua);
	clearInputBuffer();

	int error = modifyMedicament(lista, cod, nume_nou, concentratie_noua);
	if (error != 0) {
		printf("\033[1;31mModificare neefectuata!\033[0m\n");
	}
	else {
		printf("\033[1;32mMedicament modificat!\033[0m\n");
	}
}

void deleteMedicamentDat(Service* lista) {
	int cod = -1;

	printf("\033[1;36mIntroduceti codul medicamentului\033[0m: ");
	scanf_s("%d", &cod);
	clearInputBuffer();

	int error = deleteMedicament(lista, cod);
	if (error != 0) {
		printf("\033[1;31mStergere neefectuata!\033[0m\n");
	}
	else {
		printf("\033[1;32mStergerea stocului efectuat!\033[0m\n");
	}

}

void sortMedicamente(Service* lista) {
	int crescator = -1;

	printf("\033[1;36mIntroduceti 1 pentru sortare crescatoare sau 0, altfel\033[0m: ");
	scanf_s("%d", &crescator);
	clearInputBuffer();
	printf("\n");

	if (crescator == 1 || crescator == 0) {
		Repo* copie = sort(lista->actual, crescator, (sort_fct)compNume, (sort_fct)compCantitate);

		printf("\033[1;32mMedicamentele sortate sunt:\033[0m\n");
		for (int i = 0; i < copie->lungime; ++i) {
			if (verifStoc(copie->elemente[i])) {
				printMedicament(copie->elemente[i]);
			}
		}
		printf("\n");
		destroy(copie);
	}
	else {
		printf("\033[1;31mOptiune invalida!\033[0m\n");
	}

}
void printAllMedicamente(Repo* lista) {

	printf("\n\033[1;35mMedicamente\033[0m:\n");

	for (int i = 0; i < lista->lungime; ++i) {
		printMedicament(lista->elemente[i]);
	}
	printf("\n");
}

void filterMedicamente(Service* lista) {
	int cantitate = -1, optiune = -1;
	char litera;

	printf("\033[1;36mIntroduceti 1 - filtrare dupa cantitate sau 0 - dupa nume\033[0m: ");
	scanf_s("%d", &optiune);
	clearInputBuffer();
	printf("\n");

	switch (optiune) {
	case 1:
		printf("\033[1;36mIntroduceti cantitatea\033[0m: ");
		scanf_s("%d", &cantitate);
		clearInputBuffer();

		Repo* copie = copyListCantitate(lista->actual, cantitate, (filter_fct_cantitate)filterCantitate);
		printAllMedicamente(copie);
		destroy(copie);

		break;
	case 0:
		printf("\033[1;36mIntroduceti prima litera\033[0m: ");
		scanf_s(" %c", &litera, 1);

		copie = copyListNume(lista->actual, litera, (filter_fct_nume)filterNume);
		printAllMedicamente(copie);
		destroy(copie);

		break;
	default:
		printf("\033[1;31mOptiune invalida!\033[0m\n");

	}

}

void run() {
	printf("\033[1;33mBun venit la farmacie!\033[0m\n");

	Service allMedicamente = createService();
	int ruleaza = 1;

	addMedicament(&allMedicamente, 1, "nurofen", 200, 300);
	addMedicament(&allMedicamente, 2, "ibuprofen", 300, 100);
	addMedicament(&allMedicamente, 3, "nurofen", 400, 500);

	while (ruleaza) {
		printAllMedicamente(allMedicamente.actual);

		printf("\033[1;33m1.\033[0m Adauga medicament\n");
		printf("\033[1;33m2.\033[0m Modifica medicament\n");
		printf("\033[1;33m3.\033[0m Sterge stocul unui medicament\n");
		printf("\033[1;33m4.\033[0m Sorteaza medicamentele dupa nume si cantitate\n");
		printf("\033[1;33m5.\033[0m Filtreaza medicamentele dupa un anumit criteriu\n");
		printf("\033[1;33m0.\033[0m Exit\n\nComanda: ");

		int comanda = -1;
		scanf_s("%d", &comanda);
		clearInputBuffer();
		printf("\n");

		switch (comanda) {
		case 1:
			readMedicament(&allMedicamente);
			break;
		case 2:
			modifyMedicamentDat(&allMedicamente);
			break;
		case 3:
			deleteMedicamentDat(&allMedicamente);
			break;
		case 4:
			sortMedicamente(&allMedicamente);
			break;
		case 5:
			filterMedicamente(&allMedicamente);
			break;
		case 0:
			printf("\033[1;36mLa revedere!\033[0m\n");
			ruleaza = 0;
			break;
		default:
			printf("\033[1;31mComanda invalida!!!\033[0m\n");
		}
	}
	destroyService(&allMedicamente);
}