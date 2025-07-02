#ifndef FILA_ESPERA_H
#define FILA_ESPERA_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct{
  int vetor[MAX];
  int inicio;
  int final;
  int tamanho;
} Deque;

void inicia_deque(Deque *d);
int esta_cheio(Deque *d);
int esta_vazio(Deque *d);
void insere_inicio(Deque *d, int valor);
void insere_final(Deque *d, int valor);
int remove_inicio(Deque *d);
int remove_final(Deque *d);
int pega_inicio(Deque *d);
int pega_final(Deque *d);
void imprime(Deque *d);
void sortearPaciente(tabela_hash *th, Deque *fila);



#endif
