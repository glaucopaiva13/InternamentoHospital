#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tabela.h"

int main(){
    // Por enquanto sem muito aqui, tem que fazer os ciclos aqui quando todas as funções estiverem prontas.
    tabela_hash th;
    inicializar_tabela(&th);
    ler_csv(&th); 
    imprimir_tabela(&th);
}