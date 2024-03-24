#include "repo.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

Repo* createEmpty(destroy_fct f) {
	Repo* lista = malloc(sizeof(Repo));

	if (lista == NULL) {
		return NULL;
	}

	lista->capacitate = 2;
	lista->lungime = 0;
	lista->elemente = malloc(lista->capacitate * sizeof(ElemType));

	if (lista->elemente == NULL) {
		free(lista);
		return NULL;
	}

	lista->dest = f;

	return lista;
}

void destroy(Repo* lista) {
	for (int i = 0; i < lista->lungime; ++i) {
		lista->dest(lista->elemente[i]);
	}
	free(lista->elemente);
	free(lista);
}

void extind(Repo* lista) {
	 
	lista->capacitate *= 2;
	ElemType* temporar = malloc(lista->capacitate * sizeof(ElemType));

	for (int i = 0; i < lista->lungime; ++i) {
		temporar[i] = lista->elemente[i];
	}
	free(lista->elemente);
	lista->elemente = temporar;
	
}

int add(Repo* lista, ElemType* element, egale_fct eq, egale_coduri ec, cantitate_fct cant) {

	int succes = 0;
	for (int i = 0; i < lista->lungime; ++i) {
		if (eq(lista->elemente[i], element)) {
			cant(lista->elemente[i], element);
			succes = 1;
		}
		else if (ec(lista->elemente[i], element)) {
			succes = -1;
		}
	}
	if (succes == 1) {
		lista->dest(element);
		return 0;
	}
	else if (succes == -1) {
		lista->dest(element);
		return 1;
	}

	if (lista->lungime == lista->capacitate) {
		extind(lista);
	}
	lista->elemente[lista->lungime++] = element;

	return 0;
	
}

int modify(Repo* lista, ElemType* element, egal_modify eg, cantitate_fct cant) {

	for (int i = 0; i < lista->lungime; ++i) {
		if (eg(lista->elemente[i], element)) {

			cant(element, lista->elemente[i]);
			lista->dest(lista->elemente[i]);
			lista->elemente[i] = element;
			return 0;
		}
	}
	lista->dest(element);
	return 1;
}

int deleteStoc(Repo* lista, int cod, return_cod cd, sterge_cant sterge) {

	for (int i = 0; i < lista->lungime; ++i) {

		if (cd(lista->elemente[i]) == cod) {
			sterge(lista->elemente[i]);
			return 0;
		}
	}
	return 1;
}


Repo* copyList(Repo* lista, copy_fct cpy) {

	Repo* lista_noua = createEmpty(lista->dest);

	for (int i = 0; i < lista->lungime; ++i) {
		add(lista_noua, cpy(lista->elemente[i]), (egale_fct) egalMedicamente, (egale_coduri) egalCod,
			(cantitate_fct) adaugaCantitate);
	}
	return lista_noua;
}

