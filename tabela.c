#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"

void inicializar_tabela(tabela_hash *tabela) {
    for(int i = 0; i < TAMANHO; i++){
        tabela->tabela[i] = NULL;
    }
}

int eh_digito(char c) {
    return c >= '0' && c <= '9';
}

int hash(char *chave) {
    while (*chave && !eh_digito(*chave)) {
        chave++;
    }
    int valor = atoi(chave);
    return valor % TAMANHO;
}

void inserir(tabela_hash *th, char *id, char *nome, int idade, char sexo, char *cpf, int prioridade, int atendido) {
    int indice = hash(id);
    No *novo = malloc(sizeof(No));

    strcpy(novo->id, id);
    strcpy(novo->nome, nome);
    novo->idade = idade;
    novo->sexo = sexo;
    strcpy(novo->cpf, cpf);
    novo->prioridade = prioridade;
    novo->atendido = atendido;
    novo->proximo = th->tabela[indice];
    th->tabela[indice] = novo;
}


void ler_csv(tabela_hash *th) {
    FILE *arquivo = fopen("pacientes.csv", "r");

    char linha[500];
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {

        linha[strcspn(linha, "\n")] = '\0';

        char *id = strtok(linha, ";");
        char *nome = strtok(NULL, ";");
        char *idade_str = strtok(NULL, ";");
        char *sexo_str = strtok(NULL, ";");
        char *cpf = strtok(NULL, ";");
        char *prioridade_str = strtok(NULL, ";");
        char *atendido_str = strtok(NULL, ";");
        int idade = atoi(idade_str);
        char sexo = sexo_str[0];
        int prioridade = atoi(prioridade_str);
        int atendido = atoi(atendido_str);
        inserir(th, id, nome, idade, sexo, cpf, prioridade, atendido);
    }

    fclose(arquivo);
}

void imprimir_tabela(tabela_hash *th) {
    for (int i = 0; i < TAMANHO; i++) {
        printf("Índice %d:\n", i);
        No *atual = th->tabela[i];

        while (atual != NULL) {
            printf("ID: %s\n", atual->id);
            printf("Nome: %s\n", atual->nome);
            printf("Idade: %d\n", atual->idade);
            printf("Sexo: %c\n", atual->sexo);
            printf("CPF: %s\n", atual->cpf);
            printf("Prioridade: %d\n", atual->prioridade);
            printf("Atendido: %d\n", atual->atendido);
            printf("---\n");

            atual = atual->proximo;
        }
    }
}