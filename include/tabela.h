#ifndef PROJETO_H
#define PROJETO_H

#define TAMANHO 50

typedef struct No{
    char id[50];
    char nome[50];
    int idade;
    char sexo;
    char cpf[12];
    int prioridade;
    int atendido;
    int em_fila;
    struct No *proximo;
} No;

typedef struct tabela_hash{
    No *tabela[TAMANHO];
}tabela_hash;

void inicializar_tabela(tabela_hash *tabela);
int eh_digito(char c);
int funcao_hash(char *chave);
void inserir(tabela_hash *th, char *id, char *nome, int idade, char sexo, char *cpf, int prioridade, int atendido);
void ler_csv(tabela_hash *th);
void imprimir_tabela(tabela_hash *th);
No* buscar_paciente(tabela_hash *th, char *id);

#endif