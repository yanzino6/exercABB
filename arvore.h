#ifndef ARVORE_H_
#define ARVORE_H_

typedef struct tArv arv;

arv *criaArvore ();

void insereArv(arv *inserido, arv *arvore);

void imprimeArv(arv *arvore);

void liberaArv(arv *arvore);

#endif