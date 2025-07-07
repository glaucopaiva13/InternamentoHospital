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
#include "../include/log.h"

int main()
{
    srand(time(NULL));

    // Inicializa o sistema de log
    if (log_iniciar("processamento.log", 0) != 0) {
        printf("Erro ao inicializar sistema de log!\n");
        return 1;
    }

    // Adiciona timestamp inicial
    time_t agora = time(NULL);
    log_printf("=== LOG INICIADO EM %s", ctime(&agora));

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

    log_printf("========================================\n");
    log_printf("     SISTEMA HOSPITALAR INICIADO\n");
    log_printf("========================================\n\n");

    log_printf("====PACIENTES NA TABELA HASH====\n");
    imprimir_tabela(&th);

    log_printf("\n====PREENCHENDO FILA INICIAL====\n");
    preencherFila(&th, &fila);

    log_printf("\n--- Status Inicial do Sistema ---\n");
    log_printf("Fila de espera: %d pacientes\n", fila.tamanho);
    log_printf("Leitos ocupados: 0 pacientes\n");
    log_printf("Altas registradas: 0 pacientes\n");
    log_printf("Fluxo: Fila de Espera -> Leitos -> Registro de Altas\n");

    log_printf("\n========================================\n");
    log_printf("        INICIANDO ATENDIMENTO\n");
    log_printf("========================================\n");

    int ciclos = 0;

    while (!esta_vazio(&fila) || !esta_vazio_lista(&leitos))
    {
        log_printf("\n********** CICLO %d **********\n", ++ciclos);

        log_printf("Status atual: Fila=%d | Leitos=%d | Altas=%d\n", fila.tamanho, leitos.tamanho, pilha.topo + 1);

        // 1. Preencher a fila se não estiver cheia
        if (!esta_vazio(&fila) && !esta_cheio(&fila))
        {
            log_printf("\n1. ADMISSAO DE NOVOS PACIENTES:\n");
            int fila_antes = fila.tamanho;
            preencherFila(&th, &fila);
            int novos_pacientes = fila.tamanho - fila_antes;

            if (novos_pacientes > 0)
            {
                log_printf("-> %d novos pacientes foram admitidos na fila\n", novos_pacientes);
                log_printf("-> Estado atual da fila:\n");
                imprime(&fila);
            }
            else
            {
                log_printf("-> Nenhum paciente novo disponivel para admissao\n");
            }
        }
        else if (esta_cheio(&fila))
        {
            log_printf("\n1. FILA CHEIA - Priorizando atendimento dos pacientes atuais\n");
        }
        else if (esta_vazio(&fila))
        {
            log_printf("\n1. FILA VAZIA - Sem novos pacientes para admissao\n");
        }

        if (!esta_vazio(&fila))
        {
            log_printf("\n2. ATENDIMENTO MEDICO (Fila -> Leitos):\n");

            // Verifica se há espaço nos leitos antes de tentar inserir
            if (esta_cheio_lista(&leitos)) {
                log_printf("-> LEITOS LOTADOS - Capacidade maxima de 10 leitos atingida!\n");
                log_printf("-> Aguardando alta de pacientes para liberar leitos...\n");
            } else {
                No *paciente = dequeParaLista(&fila);
                if (paciente != NULL)
                {
                    total_atendimentos++;
                    pacientes_processados++;

                    log_printf("-> Paciente chamado para atendimento:\n");
                    log_printf("   ID: %s\n", paciente->id);
                    log_printf("   Nome: %s\n", paciente->nome);
                    log_printf("   Prioridade: %d\n", paciente->prioridade);

                    insereNaLista(&leitos, paciente);
                    log_printf("-> Paciente internado com sucesso!\n");
                    log_printf("-> Total de atendimentos realizados: %d\n", total_atendimentos);

                    log_printf("-> Situacao atual dos leitos:\n");
                    imprimir_lista(&leitos);
                }
            }
        }
        else
        {
            log_printf("\n2. FILA VAZIA - Nenhum paciente aguardando atendimento\n");
        }

        // Aqui faz a alta aleatória dos leitos (pode ou não pode ter)
        if (!esta_vazio_lista(&leitos))
        {
            log_printf("\n3. PROCESSO DE ALTA HOSPITALAR (Leitos -> Registro):\n");

            if (rand() % 100 < 70)
            {
                No *paciente_alta = doLeitoParaPilha(&leitos);
                if (paciente_alta != NULL)
                {
                    total_altas++;

                    log_printf("-> Alta medica concedida:\n");
                    log_printf("   ID: %s", paciente_alta->id);
                    log_printf("   Nome: %s", paciente_alta->nome);
                    log_printf("   Status: Tratamento concluido\n");

                    push(&pilha, paciente_alta);
                    log_printf("-> Alta registrada no sistema!\n");
                    log_printf("-> Total de altas processadas: %d\n", total_altas);

                    log_printf("-> Situacao dos leitos apos alta:\n");
                    imprimir_lista(&leitos);

                    log_printf("-> Registro de altas atualizado:\n");
                    imprimir_pilha(&pilha);
                }
            }
            else
            {
                log_printf("-> Pacientes ainda em tratamento - nenhuma alta hoje :(\n");
            }
        }
        else
        {
            log_printf("\n3. LEITOS VAZIOS - Nenhum paciente para receber alta\n");
        }

        // Resumo do ciclo
        time_t tempo_atual = time(NULL);
        int tempo_execucao = (int)(tempo_atual - inicio_sistema);

        log_printf("\n--- Resumo do Ciclo %d ---\n", ciclos);
        log_printf("Fila de espera: %d pacientes\n", fila.tamanho);
        log_printf("Leitos ocupados: %d pacientes\n", leitos.tamanho);
        log_printf("Altas registradas: %d pacientes\n", pilha.topo + 1);
        log_printf("Total de atendimentos: %d\n", total_atendimentos);
        log_printf("Total de altas: %d\n", total_altas);
        log_printf("Tempo de execucao: %02d:%02d\n", tempo_execucao / 60, tempo_execucao % 60);

        // Condições de parada
        if (esta_vazio(&fila) && esta_vazio_lista(&leitos))
        {
            log_printf("\n*** TODOS OS PACIENTES FORAM ATENDIDOS COM SUCESSO! ***\n");
            break;
        }

        log_printf("\nAguardando proximo ciclo...\n");
        sleep(2);
    }

    // Relatório final
    time_t fim_sistema = time(NULL);
    int tempo_total = (int)(fim_sistema - inicio_sistema);

    log_printf("\n========================================\n");
    log_printf("           RELATORIO FINAL\n");
    log_printf("========================================\n");

    log_printf("\nEstatisticas Operacionais:\n");
    log_printf("- Ciclos executados: %d\n", ciclos);
    log_printf("- Tempo total de operacao: %02d:%02d\n", tempo_total / 60, tempo_total % 60);
    log_printf("- Pacientes atendidos: %d\n", total_atendimentos);
    log_printf("- Altas processadas: %d\n", total_altas);

    if (!esta_vazia(&pilha))
    {
        log_printf("\n========================================\n");
        log_printf("         HISTORICO DE ALTAS\n");
        log_printf("========================================\n");
        log_printf("Total de registros: %d altas processadas\n\n", pilha.topo + 1);
        imprimir_pilha(&pilha);
    }

    log_printf("\n========================================\n");
    log_printf("      SISTEMA FINALIZADO COM SUCESSO\n");
    log_printf("========================================\n");

    // Timestamp final e fecha o log
    time_t fim_log = time(NULL);
    log_printf("\n=== LOG FINALIZADO EM %s", ctime(&fim_log));
    
    log_fechar();
    printf("\nLog detalhado salvo em: processamento.log\n");

    return 0;
}