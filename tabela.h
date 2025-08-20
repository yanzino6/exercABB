#ifndef TABELA_H_
#define TABELA_H_
#include "pais.h"

typedef struct tabela tHash;

tHash *criaHash(int tamTabela);
int funcHash(char *sigla, tHash *tab);
tHash *insereElemHash(tPais *pais, tHash *tabela);
int verificaElemExiste(tHash *tabela, tPais *elem);
void liberaHash(tHash *tabela);
tPais *getElemTabela(tHash *tabela, char *sigla);
tHash *redimensionaTabela(tHash *tabela);  // Agora retorna tHash*

#endif