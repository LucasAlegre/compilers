#	ETAPA 5 - Compiladores - 2019/1 Turma A - Prof. Marcelo Johann
#	Alunos:
#		Guilherme Haetinger e Lucas Alegre 

etapa5: y.tab.o lex.yy.o hash.o astree.o semantic.o tac.o main.o
	gcc -o etapa5 y.tab.o lex.yy.o hash.o astree.o semantic.o tac.o main.o

main.o: main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

astree.o: astree.c
	gcc -c astree.c

semantic.o: semantic.c
	gcc -c semantic.c

tac.o: tac.c
	gcc -c tac.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

y.tab.c: parser.y
	yacc -d -v parser.y

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l

clean:
	rm -f *.o etapa5 lex.yy.c lex.yy.h y.tab.c y.tab.h y.output
