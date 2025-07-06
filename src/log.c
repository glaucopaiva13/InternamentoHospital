#include "../include/log.h"

static FILE *log_fp = NULL;

int log_iniciar(const char *filename, int append)
{
    log_fp = fopen(filename, append ? "a" : "w");
    if (!log_fp) {
        perror("log_iniciar");
        return -1;
    }

    setvbuf(log_fp, NULL, _IOLBF, 0);
    return 0;
}

void log_fechar(void)
{
    if (log_fp) {
        fclose(log_fp);
        log_fp = NULL;
    }
}

void log_printf(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);

    if (log_fp) {
        va_start(ap, fmt);
        vfprintf(log_fp, fmt, ap);
        fflush(log_fp);
        va_end(ap);
    }
}
