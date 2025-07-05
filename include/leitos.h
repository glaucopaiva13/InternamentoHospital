#ifndef LEITOS_H
#define LEITOS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tabela.h"
#include "filaEspera.h"

typedef struct{
    No* inicio; 
    int tamanho;
} Lista;


void inicializar_lista(Lista *l);
int esta_cheio_lista(Lista *l);
int esta_vazio_lista(Lista *l);
void insereNaLista(Lista *l, No *paciente);
No* doLeitoParaPilha(Lista *l);
void imprimir_lista(Lista *l);

#endif