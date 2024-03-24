#ifndef TESTE_H_
#define TESTE_H

/// 
/// TESTE DOMENIU
/// 
void test_createMedicament();
void test_adaugaCantitate();
void test_compCantitate();
void test_compNume();
void test_destroyMedicament();
void test_egalCod();
void test_egalMedicamente();
void test_egalModify();
void test_filterCantitate();
void test_filterNume();
void test_returnCod();
void test_stergeCantitate();
void test_valideazaMedicament();
void test_verifStoc();

/// 
/// TESTE REPO
///
void test_createEmpty();
void test_destroy();
void test_extind();
void test_add();
void test_modify();
void test_deleteStoc();
void test_copyList();

/// 
/// TESTE SERVICE
/// 
void test_addMedicament();
void test_modifyMedicament();
void test_deleteMedicament();
void test_getAllMedicamente();
void test_sort();
void test_copyListCantitate();
void test_copyListNume();

#endif /* TESTE_H_ */