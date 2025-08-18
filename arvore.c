#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

struct tArv 
{
    char *nomeAluno;
    int presenca;
    arv *esq;
    arv *dir;
};

arv *criaArvore ();

void insereArv(arv *inserido, arv *arvore);

void imprimeArv(arv *arvore);

void liberaArv(arv *arvore);