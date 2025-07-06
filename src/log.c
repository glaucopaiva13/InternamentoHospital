#include "../include/log.h"

static FILE *log_fp = NULL; // Ponteiro para o arquivo de log

// Inicia o log: abre o arquivo em modo append ou write
int log_iniciar(const char *filename, int append)
{
    log_fp = fopen(filename, append ? "a" : "w");
    if (!log_fp) {
        perror("log_iniciar");
        return -1;
    }

    setvbuf(log_fp, NULL, _IOLBF, 0); // Buffer por linha
    return 0;
}

// Fecha o log se estiver aberto
void log_fechar(void)
{
    if (log_fp) {
        fclose(log_fp);
        log_fp = NULL;
    }
}

// Imprime no terminal e no arquivo de log (se estiver aberto)
void log_printf(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vprintf(fmt, ap); // Console
    va_end(ap);

    if (log_fp) {
        va_start(ap, fmt);
        vfprintf(log_fp, fmt, ap); // Arquivo
        fflush(log_fp);
        va_end(ap);
    }
}
