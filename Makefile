CC = gcc
CCFLAG = -Wall -Wextra -std=c11 -g
INCLUDE = -Iinclude
FILESCC = src/main.c src/tabela.c src/filaEspera.c
FILESH = include/tabela.h include/filaEspera.h
TARGET = tabela

all: $(TARGET)

$(TARGET): $(FILESCC) $(FILESH)
	$(CC) $(CCFLAG) $(INCLUDE) $(FILESCC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)