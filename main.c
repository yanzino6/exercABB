// ========== main.c CORRIGIDO ==========
#include "tabela.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE *leEntrada = fopen("teste.txt", "r");
    if (leEntrada == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }
    
    char nomepais[4];
    int ouros, pratas, bronzes, total;
    tPais *pais;
    tHash *tabela = criaHash(7);  // Começa pequeno para testar redimensionamento
    
    printf("=== INSERINDO PAÍSES ===\n\n");
    
    while (fscanf(leEntrada, "%s %d %d %d %d\n", nomepais, &ouros, &pratas, &bronzes, &total) == 5)
    {
        pais = criaPais(ouros, pratas, bronzes, nomepais);
        printf("Inserindo: %s\n", nomepais);
        tabela = insereElemHash(pais, tabela);  // ✅ CORREÇÃO: Atualiza ponteiro!
    }
    
    printf("\n=== TESTANDO BUSCA ===\n");
    
    // Testa busca
    char *testes[] = {"BRA", "USA", "AUS", "CHN", "XXX"};
    for (int i = 0; i < 5; i++)
    {
        tPais *encontrado = getElemTabela(tabela, testes[i]);
        if (encontrado != NULL)
        {
            printf("\nEncontrado:\n");
            imprimePais(encontrado);
        }
        else
        {
            printf("\nPaís %s não encontrado\n", testes[i]);
        }
    }
    
    // Verifica se duplicatas foram tratadas corretamente
    printf("\n=== VERIFICANDO TRATAMENTO DE DUPLICATAS ===\n");
    printf("BRA deve ter 0 0 1 1 (última entrada)\n");
    printf("USA deve ter 1 2 3 6 (última entrada)\n");
    printf("AUS deve ter 3 2 2 7 (última entrada)\n");
    
    printf("\n=== LIBERANDO MEMÓRIA ===\n");
    liberaHash(tabela);
    fclose(leEntrada);
    
    return 0;
}
