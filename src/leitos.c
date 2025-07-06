#include "../include/leitos.h"
#include "../include/filaEspera.h"
#include "../include/log.h"


// Inicializa a lista fazendo o ponteiro cabeça apontar para nulo e o tamanho 0
void inicializar_lista(Lista *l){
    l->inicio = NULL;
    l->tamanho = 0;
}

// Verifica se a lista está cheia
int esta_cheio_lista(Lista *l)
{
  return l->tamanho == 20;
}

// Verifica se está vazia
int esta_vazio_lista(Lista *l)
{
  return l->tamanho == 0;
}

// Insere na lista
void insereNaLista(Lista *l, No *paciente){
     // Verifica se a lista está cheia
    if (esta_cheio_lista(l)) {
        log_printf("Leitos ocupados!\n");
        return;
    }

    paciente->proximo = NULL; // Garante que o novo paciente não aponte para nenhum outro nó

    // Se a lista estiver vazia, o paciente será o primeiro da lista
    if (l->inicio == NULL) {
        l->inicio = paciente;
    } else {
        // Caso contrário, percorre até o final da lista e insere o paciente no final
        No* atual = l->inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = paciente;
    }

    l->tamanho++; // Incrementa o número de leitos ocupados
}

// Remove um paciente aleatório da lista de leitos e o retorna
No* doLeitoParaPilha(Lista *l){
    // Verifica se a lista está vazia
    if (esta_vazio_lista(l)) {
        log_printf("Nenhum leito ocupado\n");
        return NULL;
    }

    // Gera um índice aleatóro
    int indice = rand() % l->tamanho;

    No* anterior = NULL;
    No* atual = l->inicio;

    // Percorre a lista até o índice sorteado
    for (int i = 0; i < indice; i++) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Remove o nó sorteado da lista
    if (anterior == NULL) {
        // Caso o primeiro nó seja o sorteado
        l->inicio = atual->proximo;
    } else {
        // Caso contrário, pula o nó atual na ligação
        anterior->proximo = atual->proximo;
    }

    l->tamanho--;          // Decrementa o tamanho da lista
    atual->proximo = NULL; 
    return atual;          // Retorna o paciente removido
}

// Imprime todos os pacientes ocupando leitos
void imprimir_lista(Lista *l) {
    log_printf("Lista de Leitos (%d ocupados):\n", l->tamanho);

    No* atual = l->inicio;
    int i = 1;

    // Percorre e imprime todos os nós da lista
    while (atual != NULL) {
        log_printf("Leito %d: ID do paciente: %s\n", i++, atual->id);
        atual = atual->proximo;
    }

    // Mensagem adicional caso não haja pacientes
    if (l->tamanho == 0) {
        log_printf("Nenhum leito ocupado.\n");
    }
}