#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/tabela.h"
#include "../include/filaEspera.h"
#include "../include/log.h"

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

void insere_inicio(Deque *d, No *paciente)
{
  if (esta_cheio(d))
  {
    log_printf("Deque cheio!\n");
    return;
  }

  if (esta_vazio(d))
  {
    d->inicio = d->final = 0;
  }
  else
  {
    for (int i = d->final; i >= d->inicio; i--)
    {
      d->vetor[i + 1] = d->vetor[i];
    }
    d->final++;
  }

  d->vetor[d->inicio] = paciente;
  d->tamanho++;
}

void insere_final(Deque *d, No *paciente)
{
  if (esta_cheio(d))
  {
    log_printf("Deque cheio!\n");
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

  d->vetor[d->final] = paciente;
  d->tamanho++;
}

No *remove_inicio(Deque *d)
{
  if (esta_vazio(d))
  {
    log_printf("Deque vazio!\n");
    return NULL;
  }

  No *paciente = d->vetor[d->inicio];

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

  return paciente;
}

No *remove_final(Deque *d)
{
  if (esta_vazio(d))
  {
    log_printf("Fila vazia!\n");
    return NULL;
  }

  No *paciente = d->vetor[d->final];

  d->tamanho--;

  if (d->tamanho == 0)
  {
    d->inicio = d->final = -1;
  }
  else
  {
    d->final--;
  }

  return paciente;
}

No *pega_inicio(Deque *d)
{
  if (esta_vazio(d))
  {
    log_printf("Fila vazia!\n");
    return NULL;
  }

  return d->vetor[d->inicio];
}

No *pega_final(Deque *d)
{
  if (esta_vazio(d))
  {
    log_printf("Fila vazia!\n");
    return NULL;
  }

  return d->vetor[d->final];
}

void imprime(Deque *d)
{
  if (esta_vazio(d))
  {
    log_printf("Fila vazia!\n");
    return;
  }

  log_printf("Fila: ");

  for (int i = 0; i < d->tamanho; i++)
    log_printf("%s ", d->vetor[i]->id);

  log_printf("\n");
}

// Sorteia um paciente da tabela hash e insere no deque conforme prioridade
No *sortearPaciente(tabela_hash *th, Deque *fila)
{
  No *pacientes[TAMANHO * 10];
  int total = 0;
  for (int i = 0; i < TAMANHO; i++)
  {
    No *atual = th->tabela[i];
    while (atual != NULL)
    {
      if (atual->atendido == 0 && atual->em_fila == 0)
      {
        pacientes[total++] = atual;
      }
      atual = atual->proximo;
    }
  }
  if (total == 0)
    return NULL;

  int sorteado = rand() % total;
  No *paciente = pacientes[sorteado];
  paciente->em_fila = 1;

  if (paciente->prioridade >= 4)
  {
    insere_inicio(fila, paciente);
  }
  else
  {
    insere_final(fila, paciente);
  }

  return paciente;
}

No *dequeParaLista(Deque *fila)
{
  if (esta_vazio(fila))
  {
    log_printf("Fila vazia!\n");
    return NULL;
  }

  No *paciente_inicio = pega_inicio(fila);
  No *paciente_final = pega_final(fila);

  No *pacienteSair;

  if (paciente_inicio->prioridade > paciente_final->prioridade)
  {
    pacienteSair = remove_inicio(fila);
  }
  else if (paciente_final->prioridade > paciente_inicio->prioridade)
  {
    // Casos de prioridade diferente: remove o de maior prioridade
    pacienteSair = remove_final(fila);
  }
  else
  {
    // Caso de empate: prioriza quem está no início da fila
    pacienteSair = remove_inicio(fila);
  }

  // Marca como atendido e remove  da fila
  pacienteSair->atendido = 1;
  pacienteSair->em_fila = 0;

  return pacienteSair;
}

void preencherFila(tabela_hash *th, Deque *fila)
{
  while (!esta_cheio(fila))
  {
    No *paciente = sortearPaciente(th, fila);
    if (paciente != NULL)
    {
      log_printf("NOVO PACIENTE CHEGOU!\n");
      log_printf("ID: %s\n", paciente->id);
      log_printf("Nome: %s\n", paciente->nome);
      log_printf("Idade: %d\n", paciente->idade);
      log_printf("Sexo: %c\n", paciente->sexo);
      log_printf("CPF: %s\n", paciente->cpf);
      log_printf("Prioridade: %d\n", paciente->prioridade);
      log_printf("Atendido: %s\n", paciente->atendido ? "Sim" : "Não");
      log_printf("Em Fila: %s\n", paciente->em_fila ? "Sim" : "Não");
    }
    else
    {
      log_printf("Nenhum paciente disponível para adicionar à fila.\n");
      break;
    }
  }
}