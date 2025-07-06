#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>
#include "tabela.h"

// Estrutura de dados de pilha contendo um vetor de ponteiros e uma variável para o topo
typedef struct {
    No* vetor[100];
    int topo;
} Pilha;

// Declaração das funções
void inicializar_pilha(Pilha *p);
int esta_vazia(Pilha *p);
void push(Pilha* p, No* paciente);
void imprimir_pilha(Pilha *p);
 


#endif