#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "../include/tabela.h"
#include "../include/filaEspera.h"
#include "../include/pilha.h"
#include "../include/leitos.h"

int main()
{
    srand(time(NULL));

    // Inicializa a tabela hash e carrega dados
    tabela_hash th;
    Deque fila;
    Lista leitos;
    Pilha pilha;
    inicializar_tabela(&th);
    ler_csv(&th);
    inicia_deque(&fila);
    inicializar_lista(&leitos);
    inicializar_pilha(&pilha);

    // Contadores para estatísticas
    int total_atendimentos = 0;
    int total_altas = 0;
    int pacientes_processados = 0;
    time_t inicio_sistema = time(NULL);

    printf("========================================\n");
    printf("     SISTEMA HOSPITALAR INICIADO\n");
    printf("========================================\n\n");

    printf("====PACIENTES NA TABELA HASH====\n");
    imprimir_tabela(&th);

    printf("\n====PREENCHENDO FILA INICIAL====\n");
    preencherFila(&th, &fila);

    printf("\n--- Status Inicial do Sistema ---\n");
    printf("Fila de espera: %d pacientes\n", fila.tamanho);
    printf("Leitos ocupados: 0 pacientes\n");
    printf("Altas registradas: 0 pacientes\n");
    printf("Fluxo: Fila de Espera -> Leitos -> Registro de Altas\n");

    printf("\n========================================\n");
    printf("        INICIANDO ATENDIMENTO\n");
    printf("========================================\n");

    int ciclos = 0;

    while (!esta_vazio(&fila) || !esta_vazio_lista(&leitos))
    {
        printf("\n********** CICLO %d **********\n", ++ciclos);

        printf("Status atual: Fila=%d | Leitos=%d | Altas=%d\n", fila.tamanho, leitos.tamanho, pilha.topo + 1);

        // 1. Preencher a fila se não estiver cheia
        if (!esta_vazio(&fila) && !esta_cheio(&fila))
        {
            printf("\n1. ADMISSAO DE NOVOS PACIENTES:\n");
            int fila_antes = fila.tamanho;
            preencherFila(&th, &fila);
            int novos_pacientes = fila.tamanho - fila_antes;

            if (novos_pacientes > 0)
            {
                printf("-> %d novos pacientes foram admitidos na fila\n", novos_pacientes);
                printf("-> Estado atual da fila:\n");
                imprime(&fila);
            }
            else
            {
                printf("-> Nenhum paciente novo disponivel para admissao\n");
            }
        }
        else if (esta_cheio(&fila))
        {
            printf("\n1. FILA CHEIA - Priorizando atendimento dos pacientes atuais\n");
        }
        else if (esta_vazio(&fila))
        {
            printf("\n1. FILA VAZIA - Sem novos pacientes para admissao\n");
        }

        if (!esta_vazio(&fila))
        {
            printf("\n2. ATENDIMENTO MEDICO (Fila -> Leitos):\n");

            No *paciente = dequeParaLista(&fila);
            if (paciente != NULL)
            {
                total_atendimentos++;
                pacientes_processados++;

                printf("-> Paciente chamado para atendimento:\n");
                printf("   ID: %s", paciente->id);
                printf("   Nome: %s", paciente->nome);
                printf("   Prioridade: %d\n", paciente->prioridade);

                insereNaLista(&leitos, paciente);
                printf("-> Paciente internado com sucesso!\n");
                printf("-> Total de atendimentos realizados: %d\n", total_atendimentos);

                printf("-> Situacao atual dos leitos:\n");
                imprimir_lista(&leitos);
            }
        }
        else
        {
            printf("\n2. FILA VAZIA - Nenhum paciente aguardando atendimento\n");
        }

        // Aqui faz a alta aleatória dos leitos (pode ou não pode ter)
        if (!esta_vazio_lista(&leitos))
        {
            printf("\n3. PROCESSO DE ALTA HOSPITALAR (Leitos -> Registro):\n");

            if (rand() % 100 < 70)
            {
                No *paciente_alta = doLeitoParaPilha(&leitos);
                if (paciente_alta != NULL)
                {
                    total_altas++;

                    printf("-> Alta medica concedida:\n");
                    printf("   ID: %s", paciente_alta->id);
                    printf("   Nome: %s", paciente_alta->nome);
                    printf("   Status: Tratamento concluido\n");

                    push(&pilha, paciente_alta);
                    printf("-> Alta registrada no sistema!\n");
                    printf("-> Total de altas processadas: %d\n", total_altas);

                    printf("-> Situacao dos leitos apos alta:\n");
                    imprimir_lista(&leitos);

                    printf("-> Registro de altas atualizado:\n");
                    imprimir_pilha(&pilha);
                }
            }
            else
            {
                printf("-> Pacientes ainda em tratamento - nenhuma alta hoje :(\n");
            }
        }
        else
        {
            printf("\n3. LEITOS VAZIOS - Nenhum paciente para receber alta\n");
        }

        // Resumo do ciclo
        time_t tempo_atual = time(NULL);
        int tempo_execucao = (int)(tempo_atual - inicio_sistema);

        printf("\n--- Resumo do Ciclo %d ---\n", ciclos);
        printf("Fila de espera: %d pacientes\n", fila.tamanho);
        printf("Leitos ocupados: %d pacientes\n", leitos.tamanho);
        printf("Altas registradas: %d pacientes\n", pilha.topo + 1);
        printf("Total de atendimentos: %d\n", total_atendimentos);
        printf("Total de altas: %d\n", total_altas);
        printf("Tempo de execucao: %02d:%02d\n", tempo_execucao / 60, tempo_execucao % 60);

        // Condições de parada
        if (esta_vazio(&fila) && esta_vazio_lista(&leitos))
        {
            printf("\n*** TODOS OS PACIENTES FORAM ATENDIDOS COM SUCESSO! ***\n");
            break;
        }

        printf("\nAguardando proximo ciclo...\n");
        sleep(2);
    }

    // Relatório final
    time_t fim_sistema = time(NULL);
    int tempo_total = (int)(fim_sistema - inicio_sistema);

    printf("\n========================================\n");
    printf("           RELATORIO FINAL\n");
    printf("========================================\n");

    printf("\nEstatisticas Operacionais:\n");
    printf("- Ciclos executados: %d\n", ciclos);
    printf("- Tempo total de operacao: %02d:%02d\n", tempo_total / 60, tempo_total % 60);
    printf("- Pacientes atendidos: %d\n", total_atendimentos);
    printf("- Altas processadas: %d\n", total_altas);

    if (!esta_vazia(&pilha))
    {
        printf("\n========================================\n");
        printf("         HISTORICO DE ALTAS\n");
        printf("========================================\n");
        printf("Total de registros: %d altas processadas\n\n", pilha.topo + 1);
        imprimir_pilha(&pilha);
    }

    printf("\n========================================\n");
    printf("      SISTEMA FINALIZADO COM SUCESSO\n");
    printf("========================================\n");

    return 0;
}