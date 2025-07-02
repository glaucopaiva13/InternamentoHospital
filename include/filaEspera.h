#ifndef FILA_ESPERA_H
#define FILA_ESPERA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"

#define MAX 100

typedef struct{
  int vetor[MAX];
  int inicio;
  int final;
  int tamanho;
} Deque;

// Deque para armazenar IDs de pacientes
typedef struct{
  char ids[MAX][50];  // Array de IDs de pacientes
  int inicio;
  int final;
  int tamanho;
} DequePacientes;

// Deque para armazenar ponteiros diretos para pacientes
typedef struct{
  No* pacientes[MAX];  // Array de ponteiros para nós de pacientes
  int inicio;
  int final;
  int tamanho;
} DequePonteiros;

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

// Funções para DequePacientes
void inicia_deque_pacientes(DequePacientes *d);
int esta_cheio_pacientes(DequePacientes *d);
int esta_vazio_pacientes(DequePacientes *d);
void insere_paciente_inicio(DequePacientes *d, char *id);
void insere_paciente_final(DequePacientes *d, char *id);
char* remove_paciente_inicio(DequePacientes *d);
char* remove_paciente_final(DequePacientes *d);
void imprime_fila_pacientes(DequePacientes *d);

// Funções para DequePonteiros (acesso direto aos dados)
void inicia_deque_ponteiros(DequePonteiros *d);
int esta_cheio_ponteiros(DequePonteiros *d);
int esta_vazio_ponteiros(DequePonteiros *d);
void insere_paciente_ponteiro_inicio(DequePonteiros *d, No *paciente);
void insere_paciente_ponteiro_final(DequePonteiros *d, No *paciente);
No* remove_paciente_ponteiro_inicio(DequePonteiros *d);
No* remove_paciente_ponteiro_final(DequePonteiros *d);
void imprime_fila_ponteiros(DequePonteiros *d);

#endif
