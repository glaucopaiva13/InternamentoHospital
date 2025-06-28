all: tabela

tabela: main.o tabela.o
	gcc -Wall -Wextra -std=c11 main.o tabela.o -o tabela

main.o: main.c
	gcc -c main.c

tabela.o: tabela.c
	gcc -c tabela.c

run: tabela
	./tabela
