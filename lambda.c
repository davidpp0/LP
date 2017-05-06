#include "lambda.h"
#include <string.h>

//Ficheiro que serve para percorrer a arvore 

char *alfabeto = "abcdefghijlmnopqrstuvwxyz";
char charsUsados[20] = "";
char charsAlterar[5] = "";
int indice = 0;
int indice2 =0;



// FUNCAO PARA VERIFICAR SE O CHAR SE ENCONTRA NO ARRAY
int search(char *a){
	for(int i =0; i < 20; i++){
		if (charsUsados[i]==*a){
			return -1;
		}
	}
	return 1;
}

//FUNCAO PRINCIPAL OU MAIN
void root(Terms *root){
	printf("<- ");	
	printTerms(root);
	printf("\n");
	goTerms(root);
	printTerms(root);
}

//FUNCOES DE IMPRIMIR ARVORE----------------------------
void printTerms( Terms *root){
	if (root->type == term_terms){
		printSTerm(root->sterm);

		printTerms(root->terms);

	}else if(root->type == term_){
		printSTerm(root->sterm);
	}
}

void printSTerm(STerm *root){
	if (root->type == abs_){
		printAbs(root->abs);	
	}else if(root->type == app_){
		printApp(root->app);
	}else if(root->type == par_terms){
		printf("(");
		printTerms(root->terms);
		printf(")");
	}
}


void printApp(App *root){
	if (root->type == letter_){
		if (search(root->letter) ==1){	
			strcpy(&charsUsados[indice++],root->letter);
		}
		printf("%s", root->letter);
	}else if(root->type == letter_terms){
		if (search(root->letter) ==1){	
			strcpy(&charsUsados[indice++],root->letter);
		}
		printf("%s", root->letter);		
		printTerms(root->terms);
	}
}

void printAbs(Abs *root){
	if (search(root->letter) ==1){	
		strcpy(&charsUsados[indice++],root->letter);
	}
	printf("!%s.", root->letter);
	if (root->terms != NULL){
		printTerms(root->terms);
	}

}
// FIM DE FUNCOES DE IMPRIMIR-----------------------------

// FUNCOES DE PERCORRER E ALTERAR ARVORE-----------------------

void goTerms( Terms *root){
	if (root->type == term_terms){
		goSTerm(root->sterm);

		goTerms(root->terms);

	}else if(root->type == term_){
		goSTerm(root->sterm);
	}
}

void goSTerm(STerm *root){
	if (root->type == abs_){
		goAbs(root->abs);	
	}else if(root->type == app_){
		goApp(root->app);
	}else if(root->type == par_terms){
		goTerms(root->terms);
	}
}


void goApp(App *root){
	if (root->type == letter_){
		if (search(root->letter) ==1){	
			strcpy(&charsUsados[indice++],root->letter);
		}
	}else if(root->type == letter_terms){
		if (search(root->letter) ==1){	
			strcpy(&charsUsados[indice++],root->letter);
		}		
		goTerms(root->terms);
	}
}

void goAbs(Abs *root){
	if (search(root->letter) ==1){	
		strcpy(&charsUsados[indice++],root->letter);
	}

	if (root->terms != NULL){
		goTerms(root->terms);
	}

}


//FALTA ALTERAR PARA COMECAR A COLOCAR CHARS NO ARRAY DE USADOS 
//RETIRAR OS CHARS NO FIM DA FUNCAO 
