#ifndef SERVICE_H_
#define SERVICE_H_

#include "repo.h"
#include "farmacie.h"

typedef int(*sort_fct)(ElemType m1, ElemType m2);

typedef int(*filter_fct_nume)(ElemType m, char );

typedef int(*filter_fct_cantitate)(ElemType m, int);


typedef struct {
	Repo* actual;
}Service;

/*
* Creeaza un service pentru medicamente
* 
* Returneaza:
*	service-ul
*/
Service createService();

/*
 * Adauga un medicament nou în lista data sau actualizeaza cantitatea pentru un medicament existent.
 *
 * Parametri:
 *     lista: Pointer catre structura Repo ce reprezinta lista de medicamente.
 *     campurile elementului: codul - int, numele - string, concentratie - float, cantitate - int
 * Returneaza:
 *     0 - daca adaugarea a fost efectuata cu succes (medicamentul nou a fost adaugat în lista)
 *     1 - 4 Daca NU ESTE VALID!!
 */
int addMedicament(Service* lista, int cod, char* nume, int concentratie, int cantitate);

/*
 * Modifica un medicament din lista data cu un alt medicament dat.
 *
 * Parametri:
 *     lista: Pointer c?tre structura Repo ce reprezint? lista de medicamente.
 *     campurile elementului nou de modificat: codul (ramane acelasi) - int, numele nou - string, concetratia noua - float 
 * Returneaza:
 *     0 dac? modificarea a fost efectuata cu succes, altfel 1.
 */
int modifyMedicament(Service* lista, int cod, char* nume_nou, int concentratie_noua);

/*
 * Sterge stocul pentru un medicament din lista data, pe baza codului medicamentului.
 *
 * Parametri:
 *     lista: Pointer catre structura Repo ce reprezinta lista de medicamente.
 *     cod: Codul unic al medicamentului pentru care sa fie sters stocul.
 * Returneaza:
 *     0 daca stergerea a fost efectuata cu succes, altfel 1.
 */
int deleteMedicament(Service* lista, int cod);

/*
* returneaza o copie a listei
*/
Repo* getAllMedicamente(Service* lista);

/*
 * Sorteaza lista de medicamente data in functie de nume si/sau cantitate.
 *
 * Parametri:
 *     lista: Pointer catre structura Repo care reprezinta lista de medicamente de sortat.
 *     crescator: Indicator pentru ordinea de sortare; 1 pentru ordine crescatoare, 0 pentru ordine descrescatoare - int.
 * Returneaza:
 *     Repo: Lista sortata de medicamente.
 */
Repo* sort(Repo* lista, int crescator, sort_fct cmp1, sort_fct cmp2);

/*
 * Creeaza o copie a listei de medicamente data, selectand doar acele medicamente
 * ale caror cantitate este mai mica decat o valoare specificata.
 *
 * Parametri:
 *     lista: Pointer catre structura Repo care reprezinta lista de medicamente originala.
 *     cantitate: Cantitatea maxima admisa pentru a fi incluse in copie - int.
 * Returneaza:
 *     Repo: O noua lista de medicamente continand elementele copiate.
 */
Repo* copyListCantitate(Repo* lista, int cantitate, filter_fct_cantitate filter);


/*
 * Creeaza o copie a listei de medicamente data, selectand doar acele medicamente
 * ale caror nume incep cu o litera specificata.
 *
 * Parametri:
 *     lista: Pointer catre structura Repo care reprezinta lista de medicamente originala.
 *     litera: Litera dupa care se filtreaza medicamentele - char.
 * Returneaza:
 *     Repo: O noua lista de medicamente continand elementele copiate.
 */
Repo* copyListNume(Repo* lista, char litera, filter_fct_nume filter);

/*
* Destructor pentru service
* 
* Parametri:
*	Service-ul de distrus
*/
void destroyService(Service* lista);

#endif /* SERVICE_H_ */