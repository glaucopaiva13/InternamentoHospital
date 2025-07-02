#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../include/tabela.h"
#include "../include/filaEspera.h"

int main(){
    srand(time(NULL));
    
    // Inicializa a tabela hash e carrega dados
    tabela_hash th;
    Deque fila;
    inicializar_tabela(&th);
    ler_csv(&th); 
    // Inicializa fila de espera em deque
    inicia_deque(&fila);
    
    printf("====PACIENTES NA TABELA HASH====\n");
    imprimir_tabela(&th);
    
    return 0;
}