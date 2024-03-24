#ifndef FARMACIE_H_
#define FARMACIE_H_

typedef struct {
	int cod; //cod unic
	char* nume;
	int concentratie;
	int cantitate; //in grame
} Medicament;

/*
* Creeaza un nou medicament.
*
* Parametri:
* - cod: codul unic al medicamentului
* - nume: numele medicamentului
* - concentratie: concentratia medicamentului
* - cantitate: cantitatea medicamentului in grame
*
* Returneaza:
* Un pointer la un nou obiect de tip Medicament sau NULL daca alocarea de memorie esueaza.
*/
Medicament* createMedicament(int cod, char* nume, int concentratie, int cantitate);

/*
* Distrugerea unui medicament.
*
* Parametri:
* - m: pointer la medicamentul care trebuie distrus
*/
void destroyMedicament(Medicament* m);

/*
* Valideaza un medicament.
*
* Parametri:
* - m: pointer la medicamentul care trebuie validat
*
* Returneaza:
* 0: medicamentul este validat
* 1: codul este negativ
* 2: numele este vid
* 3: concentratia este negativa
* 4: cantitatea este negativa
*/

int valideazaMedicament(Medicament* m);

/*
* Verifica daca doua medicamente au acelasi cod.
*
* Parametri:
* - m1: pointer la primul medicament
* - m2: pointer la al doilea medicament
*
* Returneaza:
* 1 daca medicamentele au acelasi cod, altfel 0
*/
int egalCod(Medicament* m1, Medicament* m2);

/*
* Verifica daca doua medicamente sunt identice.
*
* Parametri:
* - m1: pointer la primul medicament
* - m2: pointer la al doilea medicament
*
* Returneaza:
* 1 daca medicamentele sunt identice, altfel 0
*/
int egalMedicamente(Medicament* m1, Medicament* m2);

/*
* Verifica daca doua medicamente au acelasi cod si daca primul medicament are o cantitate mai mare decat zero.
*
* Parametri:
* - m1: pointer la primul medicament
* - m2: pointer la al doilea medicament
*
* Returneaza:
* 1 daca medicamentele au acelasi cod si primul medicament are o cantitate mai mare decat zero, altfel 0
*/
int egalModify(Medicament* m1, Medicament* m2);

/*
* Adauga cantitatea unui medicament la alt medicament.
*
* Parametri:
* - m1: pointer la medicamentul la care se adauga cantitatea
* - m2: pointer la medicamentul din care se ia cantitatea
*/
void adaugaCantitate(Medicament* m1, Medicament* m2);

/*
* Returneaza codul unui medicament.
*
* Parametri:
* - m: pointer la medicament
*
* Returneaza:
* Codul unic al medicamentului
*/
int returnCod(Medicament* m);

/*
* Verifica daca medicamentul este in stoc.
*
* Parametri:
* - m: pointer la medicament
*
* Returneaza:
* 1 daca medicamentul este in stoc, altfel 0
*/
int verifStoc(Medicament* m);

/*
* Sterge cantitatea unui medicament (seteaza cantitatea la 0).
*
* Parametri:
* - m: pointer la medicament
*/
void stergeCantitate(Medicament* m);

/*
* Compara numele a doua medicamente.
*
* Parametri:
* - m1: pointer la primul medicament
* - m2: pointer la al doilea medicament
*
* Returneaza:
* Un numar negativ daca numele primului medicament este mai mic, 0 daca numele sunt egale, 
* si un numar pozitiv daca numele primului medicament este mai mare.
* 
*/
int compNume(Medicament* m1, Medicament* m2);

/*
* Compara cantitatea a doua medicamente.
*
* Parametri:
* - m1: pointer la primul medicament
* - m2: pointer la al doilea medicament
*
* Returneaza:
* 1 daca cantitatea primului medicament este mai mare decat a celui de-al doilea, altfel 0
*/
int compCantitate(Medicament* m1, Medicament* m2);

/*
* Filtreaza medicamentele dupa nume.
*
* Parametri:
* - m: pointer la medicamentul care trebuie verificat
* - nume: prima litera a numele dupa care se filtreaza
*
* Returneaza:
* 1 daca prima litera a numelui medicamentului coincide cu litera data, altfel 0
*/
int filterNume(Medicament* m, char nume);

/*
* Filtreaza medicamentele dupa cantitate.
*
* Parametri:
* - m: pointer la medicamentul care trebuie verificat
* - cantitate: valoarea maxima a cantitatii pentru filtrare
*
* Returneaza:
* 1 daca medicamentul are cantitatea mai mica decat valoarea data, altfel 0
*/
int filterCantitate(Medicament* m, int cantitate);

/*
* Copiaza un medicament.
*
* Parametri:
* - m: pointer la medicamentul care trebuie copiat
*
* Returneaza:
* Pointer la o copie a medicamentului dat sau NULL daca alocarea de memorie esueaza.
*/
Medicament* copyMedicament(Medicament* m);

#endif /* FARMACIE_H_ */
