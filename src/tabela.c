#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tabela.h"

// Inicializa tabela
void inicializar_tabela(tabela_hash *tabela) {
    for(int i = 0; i < TAMANHO; i++){
        tabela->tabela[i] = NULL;
    }
}

// Função para verificar se um caracter é digito, ela é usada na função hash
int eh_digito(char c) {
    return c >= '0' && c <= '9';
}

// Função hash que recebe uma chave (id) e retorna um indice no tabela
int funcao_hash(char *chave) {
    while (*chave && !eh_digito(*chave)) {
        chave++;
    }
    int valor = atoi(chave);
    return valor % TAMANHO;
}

// Função para inserir elementos na tabela hash
void inserir(tabela_hash *th, char *id, char *nome, int idade, char sexo, char *cpf, int prioridade, int atendido) {
    int indice = funcao_hash(id);
    No *novo = malloc(sizeof(No));

    strcpy(novo->id, id);
    strcpy(novo->nome, nome);
    novo->idade = idade;
    novo->sexo = sexo;
    strcpy(novo->cpf, cpf);
    novo->prioridade = prioridade;
    novo->atendido = atendido;
    novo->em_fila = 0;
    novo->proximo = th->tabela[indice];
    th->tabela[indice] = novo;
}


// Lê dados do arquivo CSV e insere na tabela hash
void ler_csv(tabela_hash *th) {
    FILE *arquivo = fopen("pacientes.csv", "r");

    char linha[500];
    fgets(linha, sizeof(linha), arquivo); // Lê e descarta o cabeçalho

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0'; // Remove o '\n' do final

        // Separa os campos usando ';' como delimitador
        char *id = strtok(linha, ";");
        char *nome = strtok(NULL, ";");
        char *idade_str = strtok(NULL, ";");
        char *sexo_str = strtok(NULL, ";");
        char *cpf = strtok(NULL, ";");
        char *prioridade_str = strtok(NULL, ";");
        char *atendido_str = strtok(NULL, ";");

        // Converte strings numéricas
        int idade = atoi(idade_str);
        char sexo = sexo_str[0];
        int prioridade = atoi(prioridade_str);
        int atendido = atoi(atendido_str);

        // Insere o paciente na tabela hash
        inserir(th, id, nome, idade, sexo, cpf, prioridade, atendido);
    }

    fclose(arquivo);
}

// Imprime todos os pacientes da tabela hash
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

// Busca um paciente pelo ID na tabela hash
No* buscar_paciente(tabela_hash *th, char *id) {
    int indice = funcao_hash(id);           // Calcula o índice
    No *atual = th->tabela[indice];         // Acessa a lista encadeada

    while (atual != NULL) {
        if (strcmp(atual->id, id) == 0) {
            return atual; // Encontrado
        }
        atual = atual->proximo;
    }

    return NULL; // Não encontrado
}