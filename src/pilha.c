#include "../include/pilha.h"
#include "../include/log.h"

// Função para iniciar pilha
void inicializar_pilha(Pilha *p){
    p->topo = -1;
}

// Verifica se está vazia
int esta_vazia(Pilha *p){
  return p->topo == -1;
}

// Insere o elemento no topo da pilha
void push(Pilha* p, No* paciente) {
  if(p->topo < 100-1){
    p->vetor[++p->topo] = paciente;
  }else{
    log_printf("Erro: Pilha cheia!\n");
  }
}

// Imprime pilha
void imprimir_pilha(Pilha *p) {
  if (esta_vazia(p)) {
    log_printf("Pilha vazia!\n");
    return;
  }

  log_printf("Conteúdo da pilha (do topo ao fundo):\n");
  for (int i = p->topo ; i >= 0; i--) {
    No* paciente = p->vetor[i];
    log_printf("Posição %d: ID = %s\n", i, paciente->id);
  }
}