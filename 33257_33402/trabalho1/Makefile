CC = gcc-6 -Wall -g
YACC = bison -d -v
LEX = flex


lambda : anasin.tab.c lex.yy.c
	$(CC) $^ -o $@ -lfl

anasin.tab.c : anasin.y
	$(YACC) $^

lex.yy.c : analex.lex
	$(LEX) $^

run : lambda
	@echo '[teste.in]'
	@./lambda < exemplo1.in
	

clean :
	@$(RM) lambda
	@$(RM) anasin.tab.c anasin.tab.h
	@$(RM) lex.yy.c
	@$(RM) lambda.output
