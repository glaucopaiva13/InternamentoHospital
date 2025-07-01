CCFLAG = -Wall -Wextra -std=c11 -g
FILES = src/main.c src/tabela.c include/tabela.h

all: tabela

tabela: $(FILES)
	gcc $(CCFLAG) -Iinclude src/main.c src/tabela.c -o tabela

run: tabela
	./tabela

clean:
	rm -f tabela