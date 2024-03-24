#ifndef REPO_H_
#define REPO_H_

#include "farmacie.h"

typedef void* ElemType;

typedef void(*destroy_fct)(ElemType);

typedef ElemType(*copy_fct)(ElemType);

typedef int(*egale_coduri)(ElemType, ElemType);

typedef int(*egale_fct)(ElemType, ElemType);

typedef int(*egal_modify)(ElemType, ElemType);

typedef void(*cantitate_fct)(ElemType, ElemType);

typedef int(*return_cod)(ElemType);

typedef void(*sterge_cant)(ElemType);

typedef void(*print_fct)(ElemType);


typedef struct {
	ElemType* elemente;
	int lungime;
	int capacitate;
	destroy_fct dest;
} Repo;

/*
* Creeaza o lista goala.
*
* Parametri:
* - f: Pointer la functia pentru distrugerea elementelor din lista.
*
* Returneaza:
* Pointer la o noua structura Repo sau NULL daca alocarea de memorie esueaza.
*/
Repo* createEmpty(destroy_fct f);

/*
* Extinde capacitatea listei dubland-o.
*
* Parametri:
* - lista: Pointer la lista pe care se efectueaza operatia de extindere.
*/
void extind(Repo* lista);

/*
* Distrugerea unei liste.
*
* Parametri:
* - lista: Pointer la lista care trebuie distrusa.
*/
void destroy(Repo* lista);

/*
 * Adauga un medicament nou în lista data sau actualizeaza cantitatea pentru un medicament existent.
 *
 * Parametri:
 *     lista: Pointer catre structura Repo ce reprezinta lista de medicamente.
 *     element: Elementul de tipul Medicament ce urmeaza sa fie adaugat sau actualizat in lista.
 * Returneaza:
 *     0 - daca adaugarea a fost efectuata cu succes (medicamentul nou a fost adaugat în lista)
 *     1 - daca exista deja un medicament cu acelasi cod in lista, dar cu un nume diferit
 */
int add(Repo* lista, ElemType* element, egale_fct eq, egale_coduri ec, cantitate_fct cant);

/*
 * Modifica un medicament din lista data cu un alt medicament dat.
 *
 * Parametri:
 *     lista: Pointer c?tre structura Repo ce reprezint? lista de medicamente.
 *     element: Elementul de tipul Medicament cu care sa fie modificat medicamentul din lista.
 * Returneaza:
 *     0 dac? modificarea a fost efectuata cu succes, altfel 1.
 */
int modify(Repo* lista, ElemType* element, egal_modify eg, cantitate_fct cant);

/*
 * Sterge stocul pentru un medicament din lista data, pe baza codului medicamentului.
 *
 * Parametri:
 *     lista: Pointer catre structura Repo ce reprezinta lista de medicamente.
 *     cod: Codul unic al medicamentului pentru care sa fie sters stocul.
 * Returneaza:
 *     0 daca stergerea a fost efectuata cu succes, altfel 1.
 */
int deleteStoc(Repo* lista, int cod, return_cod cd, sterge_cant sterge);

/*
* Facem o copie listei
* returneaza Repo care contine aceleasi elemente ca si lista
*/
Repo* copyList(Repo* lista, copy_fct cpy);

#endif /* REPO_H_ */
