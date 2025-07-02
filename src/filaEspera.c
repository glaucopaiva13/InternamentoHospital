#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/tabela.h"
#include "../include/filaEspera.h"

void inicia_deque(Deque *d)
{
  d->inicio = -1;
  d->final = -1;
  d->tamanho = 0;
}

int esta_cheio(Deque *d)
{
  return d->tamanho == MAX;
}

int esta_vazio(Deque *d)
{

  return d->tamanho == 0;
}

void insere_inicio(Deque *d, int valor)
{
  if (esta_cheio(d))
  {
    printf("Deque cheio!\n");
    return;
  }

  if (esta_vazio(d))
  {
    d->inicio = d->final = 0;
    d->vetor[d->inicio] = valor;
  }
  else
  {
    for (int i = d->tamanho; i > 0; i--)
    {
      d->vetor[i] = d->vetor[i - 1];
    }
    d->inicio = 0;
    d->vetor[d->inicio] = valor;
    d->final++;
  }

  d->tamanho++;
}

void insere_final(Deque *d, int valor)
{
  if (esta_cheio(d))
  {
    printf("Fila cheia!\n");
    return;
  }
  if (esta_vazio(d))
  {
    d->inicio = d->final = 0;
  }
  else
  {
    d->final = d->final + 1;
  }

  d->vetor[d->final] = valor;
  d->tamanho++;
}

int remove_inicio(Deque *d)
{
  if (esta_vazio(d))
  {
    printf("Deque vazio!\n");
    return -1;
  }

  int valor = d->vetor[d->inicio];

  for (int i = d->inicio; i < d->final; i++)
  {
    d->vetor[i] = d->vetor[i + 1];
  }

  d->final--;
  d->tamanho--;

  if (d->tamanho == 0)
  {
    d->inicio = d->final = -1;
  }

  return valor;
}

int remove_final(Deque *d)
{
  if (esta_vazio(d))
  {
    printf("FIla vazia!\n");
    return -1;
  }

  int valor = d->vetor[d->final];

  d->tamanho--;

  if (d->tamanho == 0)
  {
    d->inicio = d->final = -1;
  }
  else
  {
    d->final--;
  }

  return valor;
}

int pega_inicio(Deque *d)
{
  if (esta_vazio(d))
  {
    printf("FIla vazia!\n");
    return -1;
  }

  return d->vetor[d->inicio];
}

int pega_final(Deque *d)
{
  if (esta_vazio(d))
  {
    printf("FIla vazia!\n");
    return -1;
  }

  return d->vetor[d->final];
}

void imprime(Deque *d)
{
  if (esta_vazio(d))
  {
    printf("FIla vazia!\n");
    return;
  }

  printf("Fila: ");

  for (int i = 0; i < d->tamanho; i++)
    printf("%d ", d->vetor[i]);

  printf("\n");
}

// Sorteia um paciente da tabela hash e insere o id no deque conforme prioridade
void sortearPaciente(tabela_hash *th, Deque *fila) {
    No *pacientes[TAMANHO * 10]; // Suporte para até 10 pacientes por slot
    int total = 0;
    for (int i = 0; i < TAMANHO; i++) {
        No *atual = th->tabela[i];
        while (atual != NULL) {
            pacientes[total++] = atual;
            atual = atual->proximo;
        }
    }
    if (total == 0) return;
    int sorteado = rand() % total;
    No *p = pacientes[sorteado];
    if (p->prioridade >= 4) {
        insere_inicio(fila, atoi(p->id));
    } else {
        insere_final(fila, atoi(p->id));
    }
}
