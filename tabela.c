// ========== tabela.c CORRIGIDO ==========
#include "tabela.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tabela
{
    int tamTabela;
    int qtdItens;
    tPais **paises;
};

tHash *criaHash(int tamTabela)
{
    tHash *criada = (tHash *)malloc(sizeof(tHash));
    criada->tamTabela = tamTabela;
    criada->qtdItens = 0;  // ✅ CORREÇÃO: Inicializar qtdItens
    criada->paises = (tPais **)malloc(tamTabela * sizeof(tPais *));
    for (int i = 0; i < criada->tamTabela; i++)
    {
        criada->paises[i] = NULL;
    }
    return criada;
}

int funcHash(char *sigla, tHash *tab)
{
    int val = 0;
    int dimSigla = strlen(sigla);
    for (int i = 0; i < dimSigla; i++)
    {
        val += sigla[i];
    }
    return val % tab->tamTabela;
}

tHash *insereElemHash(tPais *pais, tHash *tabela)
{
    // ✅ CORREÇÃO: Verificar redimensionamento ANTES e atualizar ponteiro
    if (tabela->qtdItens > 0.75 * tabela->tamTabela)
    {
        tabela = redimensionaTabela(tabela);  // Atualiza ponteiro!
    }
    
    int indice = funcHash(getSiglaPais(pais), tabela);
    
    // Caso 1: Posição vazia
    if (tabela->paises[indice] == NULL)
    {
        tabela->paises[indice] = pais;
        tabela->qtdItens++;
    }
    // Caso 2: Posição ocupada - verificar se é o mesmo país
    else
    {
        tPais *paisExistente = buscaPaisNaLista(tabela->paises[indice], getSiglaPais(pais));
        
        if (paisExistente != NULL)
        {
            // País já existe - atualizar medalhas
            atualizaMedalhas(paisExistente, pais);
            liberaPais(pais);
        }
        else
        {
            // País não existe - adicionar na lista (colisão)
            adicionaPaisColisao(tabela->paises[indice], pais);
            tabela->qtdItens++;  // ✅ CORREÇÃO: Incrementar contador
        }
    }
    
    return tabela;
}

// ✅ CORREÇÃO: Lógica correta para verificar existência
int verificaElemExiste(tHash *tabela, tPais *elem)
{
    int indice = funcHash(getSiglaPais(elem), tabela);
    if (tabela->paises[indice] != NULL)
    {
        return verificaPaisNaLista(tabela->paises[indice], elem);
    }
    return 0;
}

void liberaHash(tHash *tabela)
{
    for (int i = 0; i < tabela->tamTabela; i++)
    {
        liberaPais(tabela->paises[i]);
    }
    free(tabela->paises);
    free(tabela);
}

// ✅ CORREÇÃO: Buscar na lista encadeada
tPais *getElemTabela(tHash *tabela, char *sigla)
{
    int indice = funcHash(sigla, tabela);
    if (tabela->paises[indice] != NULL)
    {
        return buscaPaisNaLista(tabela->paises[indice], sigla);
    }
    return NULL;
}

// ✅ CORREÇÃO COMPLETA: Redimensionamento correto
tHash *redimensionaTabela(tHash *tabela)
{
    printf("Redimensionando tabela de %d para ", tabela->tamTabela);
    
    int tamAntigo = tabela->tamTabela;
    tPais **paisesAntigos = tabela->paises;
    
    // Cria NOVA tabela
    int novoTamanho = (int)(tabela->tamTabela * 1.947);
    printf("%d posições\n", novoTamanho);
    
    tHash *novaTabela = criaHash(novoTamanho);
    
    // Reinsere TODOS os elementos (incluindo listas encadeadas)
    for (int i = 0; i < tamAntigo; i++)
    {
        tPais *atual = paisesAntigos[i];
        while (atual != NULL)
        {
            tPais *proximo = getProx(atual);
            setProx(atual,NULL);  // Desconecta da lista antiga
            
            // Insere diretamente na nova tabela
            int novoIndice = funcHash(getSiglaPais(atual), novaTabela);
            
            if (novaTabela->paises[novoIndice] == NULL)
            {
                novaTabela->paises[novoIndice] = atual;
            }
            else
            {
                adicionaPaisColisao(novaTabela->paises[novoIndice], atual);
            }
            novaTabela->qtdItens++;
            
            atual = proximo;
        }
    }
    
    // Libera estrutura antiga
    free(paisesAntigos);
    free(tabela);
    
    return novaTabela;  // Retorna a NOVA tabela
}