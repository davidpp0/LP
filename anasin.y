%{
#include <stdio.h>
#include "lambda.c"

int yylex(void);              //main do lexer
void yyerror(const char *);   //funcao que retorna erros 
%}

//Mostra erros caso ache
%error-verbose 
%expect 3   

//identifica estruturas de dados
%union{
	char *letter;
	struct Terms *terms;
	struct STerm *sterm;
	struct App *app;
	struct Abs *abs;
}           

     
%token LAMBDA
%token PONTO
%token PARE
%token PARD
%token <letter> LETTER
%type <terms> terms
%type <sterm> term
%type <app> app
%type <abs> abs

%left LETTER
%right LAMBDA
%nonassoc PONTO PARE PARD0

//REGRAS DE SINTAXE
%%

program: terms  			{root($1);};
  
                             //Ao criar a árvore insere no topo da pilha. Chama a funcao criada no tree.c


terms : term terms 			{$$ = newTerm(term_terms, $2, $1);}
	  | term 				{$$ = newTerm(term_, NULL, $1);}
	  ;


term: abs      				{$$ = newSTerm(abs_, $1, NULL, NULL);};
	| app     				{$$ = newSTerm(app_, NULL, $1, NULL);};
	| PARE terms PARD    	{$$ = newSTerm(par_terms, NULL, NULL, $2);}
	 																				
	;

abs: LAMBDA LETTER PONTO terms  {$$ = newAbs($2,$4);};  

app : LETTER        		{$$ = newApp(letter_, NULL, $1);}
	| LETTER terms 			{$$ = newApp(letter_terms, $2, $1);}	
	;					
		

%%

void yyerror(const char *msg) {
	fprintf(stderr, "error: %s\n", msg);        //da print dos erros
}

int main() {
	return yyparse();
}