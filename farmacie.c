#include "farmacie.h"

#include <string.h>
#include <assert.h>
#include <stdlib.h>

Medicament* createMedicament(int cod, char* nume, int concentratie, int cantitate) {
	int lung_nume;
	Medicament* rez = malloc(sizeof(Medicament));

	if (rez == NULL) {
		return NULL;
	}

	rez->cod = cod;

	lung_nume = (int)strlen(nume) + 1;
	rez->nume = malloc(lung_nume * sizeof(char));

	if (rez->nume == NULL) {
		free(rez);
		return NULL;
	}

	strcpy_s(rez->nume, lung_nume, nume);

	rez->concentratie = concentratie;
	rez->cantitate = cantitate;

	return rez;
}

void destroyMedicament(Medicament* m) {

	//marcam ca medicamentul este distrus, ca sa evitam folosirea accidentala
	free(m->nume);
	free(m);
}

int valideazaMedicament(Medicament* m) {

	if (m->cod <= 0) {
		return 1;
	}

	if (strlen(m->nume) == 0) {
		return 2;
	}

	if (m->concentratie < 0) {
		return 3;
	}

	if (m->cantitate < 0) {
		return 4;
	}

	return 0;
}
int egalCod(Medicament* m1, Medicament* m2) {
	if (m1->cod == m2->cod) {
		return 1;
	}
	return 0;
}
int egalMedicamente(Medicament* m1, Medicament* m2) {
	if (m1->cod == m2->cod && strcmp(m1->nume, m2->nume) == 0 &&
		m1->concentratie == m2->concentratie) {
		return 1;
	}
	return 0;

}

int egalModify(Medicament* m1, Medicament* m2) {
	if (m1->cod == m2->cod && m1->cantitate > 0) {
		return 1;
	}
	return 0;

}

void adaugaCantitate(Medicament* m1, Medicament* m2) {
	m1->cantitate += m2->cantitate;

}

int returnCod(Medicament* m) {
	return m->cod;
}

int verifStoc(Medicament* m) {
	if (m->cantitate > 0) {
		return 1;
	}
	return 0;
}

void stergeCantitate(Medicament* m) {
	m->cantitate = 0;
}

int compNume(Medicament* m1, Medicament* m2) {
	return strcmp(m1->nume, m2->nume);
}

int compCantitate(Medicament* m1, Medicament* m2) {
	if (m1->cantitate > m2->cantitate) {
		return 1;
	}
	return 0;
}

int filterNume(Medicament* m, char nume) {
	if (m->nume[0] == nume) {
		return 1;
	}
	return 0;
}

int filterCantitate(Medicament* m, int cantitate) {
	if (m->cantitate > 0 && m->cantitate < cantitate) {
		return 1;
	}
	return 0;
}

Medicament* copyMedicament(Medicament* m) {

	return createMedicament(m->cod, m->nume, m->concentratie, m->cantitate);

}


