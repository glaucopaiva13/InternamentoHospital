#ifndef FILA_ESPERA_H
#define FILA_ESPERA_H

#include <stdio.h>
#include <stdlib.h>
#include "tabela.h"

#define MAX 20

typedef struct{
  No* vetor[MAX];
  int inicio;
  int final;
  int tamanho;
} Deque;

void inicia_deque(Deque *d);
int esta_cheio(Deque *d);
int esta_vazio(Deque *d);
void insere_inicio(Deque *d, No* paciente);
void insere_final(Deque *d, No* paciente);
No* remove_inicio(Deque *d);
No* remove_final(Deque *d);
No* pega_inicio(Deque *d);
No* pega_final(Deque *d);
void imprime(Deque *d);
No* sortearPaciente(tabela_hash *th, Deque *fila);
No* dequeParaLista(Deque *fila);
preencherFila(tabela_hash *th, Deque *fila);

#endif