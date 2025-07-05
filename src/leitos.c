#include "../include/leitos.h"
#include "../include/filaEspera.h"

void inicializar_lista(Lista *l){
    l->inicio = NULL;
    l->tamanho = 0;
}

int esta_cheio_lista(Lista *l)
{
  return l->tamanho == 20;
}

int esta_vazio_lista(Lista *l)
{
  return l->tamanho == 0;
}

void insereNaLista(Lista *l, No *paciente){
    if (esta_cheio_lista(l)) {
        printf("Leitos ocupados!\n");
        return;
    }

    paciente->proximo = NULL;

    if (l->inicio == NULL) {
        l->inicio = paciente;
    } else {
        No* atual = l->inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = paciente;
    }

    l->tamanho++;
}

No* doLeitoParaPilha(Lista *l){
        if (esta_vazio_lista(l)) {
        printf("Nenhum leito ocupado\n");
        return NULL;
    }

    int indice = rand() % l->tamanho;

    No* anterior = NULL;
    No* atual = l->inicio;

    for (int i = 0; i < indice; i++) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (anterior == NULL) {
        l->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    l->tamanho--;
    atual->proximo = NULL;
    return atual;
}

void imprimir_lista(Lista *l) {
    printf("Lista de Leitos (%d ocupados):\n", l->tamanho);

    No* atual = l->inicio;
    int i = 1;
    while (atual != NULL) {
        printf("Leito %d: ID do paciente: %s\n", i++, atual->id);
        atual = atual->proximo;
    }

    if (l->tamanho == 0) {
        printf("Nenhum leito ocupado.\n");
    }
}