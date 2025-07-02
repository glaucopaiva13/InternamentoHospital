#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tabela.h"
#include "../include/filaEspera.h"

int main(){
    // Inicializa a tabela hash e carrega dados
    tabela_hash th;
    inicializar_tabela(&th);
    ler_csv(&th); 
    imprimir_tabela(&th);


    return 0;
}