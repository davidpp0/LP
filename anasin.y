%{
#include <stdio.h>


int yylex(void);              //main do lexer
void yyerror(const char *);   //funcao que retorna erros 
%}

//Mostra erros caso ache
%error-verbose    

//identifica estruturas de dados
%union{
	char *letter;
}           

     
%token LAMBDA
%token PONTO
%token PARE
%token PARD
%token <letter> LETTER


//REGRAS DE SINTAXE
%%

program: terms  										
                                               //Ao criar a árvore insere no topo da pilha. Chama a funcao criada no tree.c


terms : term terms
	  | term
	  ;


term: abs
	| app   
	| PARE term PARD  
	 																				
	;

abs: LAMBDA LETTER PONTO terms ;

app : LETTER
	| LETTER app 
	;					
		

%%

void yyerror(const char *msg) {
	fprintf(stderr, "error: %s\n", msg);        //da print dos erros
}

int main() {
	return yyparse();
}