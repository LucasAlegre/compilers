#	ETAPA 1 - Compiladores - 2019/1 Turma A - Prof. Marcelo Johann
#	Alunos:
#		Guilherme Haetinger e Lucas Alegre 

etapa1: lex.yy.o main.o hash.o
	gcc -o etapa1 lex.yy.o main.o hash.o

main.o: main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l
	
clean:
	rm -f *.o lex.yy.c lex.yy.h etapa1
