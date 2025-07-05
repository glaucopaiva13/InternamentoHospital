#include "../include/pilha.h"

void inicializar_pilha(Pilha *p){
    p->topo = -1;
}

int esta_vazia(Pilha *p){
  return p->topo == -1;
}

void push(Pilha* p, No* paciente) {
  if(p->topo < 100-1){
    p->vetor[++p->topo] = paciente;
  }else{
    printf("Erro: Pilha cheia!\n");
  }
}

void imprimir_pilha(Pilha *p) {
  if (esta_vazia(p)) {
    printf("Pilha vazia!\n");
    return;
  }

  printf("Conteúdo da pilha (do topo ao fundo):\n");
  for (int i = p->topo ; i >= 0; i--) {
    No* paciente = p->vetor[i];
    printf("Posição %d: ID = %s\n", i, paciente->id);
  }
}