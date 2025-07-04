#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../include/tabela.h"
#include "../include/filaEspera.h"

int main()
{
    srand(time(NULL));

    // Inicializa a tabela hash e carrega dados
    tabela_hash th;
    Deque fila;
    inicializar_tabela(&th);
    ler_csv(&th);
    inicia_deque(&fila);

    printf("====PACIENTES NA TABELA HASH====\n");
    imprimir_tabela(&th);

    printf("\n====PREENCHENDO FILA INICIAL====\n");

    preencherFila(&th, &fila);

    // utilize a função dequeParaLista para remover pacientes da fila e adicionar na lista de leitos

    // colocar aqui a função de preenchimento dos leitos, pra preencher os leitos iniciais

    printf("\n====INICIANDO ATENDIMENTO CONTÍNUO====\n");

    int ciclos = 0;

    while (!esta_vazio(&fila))
    {
        printf("\n====CICLO %d====\n", ++ciclos);
        if (esta_cheio(&fila))
        {
            printf("Fila cheia, não é possível adicionar mais pacientes.\n");
            printf("Esperando a liberação de um leito para liberar vaga na fila!\n");
            continue;
        }
        else
        {
            preencherFila(&th, &fila);
        }

        No *paciente = dequeParaLista(&fila);
        if (paciente == NULL)
        {
            printf("Nenhum paciente disponível para atendimento.\n");
            printf("Encerrando a execução...\n");
            break;
            // Código para ter a alta aleatória do leito
        }

        return 0;
    }