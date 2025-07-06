#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>

// Declarações das funções
int  log_iniciar(const char *filename, int append);
void log_fechar(void);
void log_printf(const char *fmt, ...);


#endif
