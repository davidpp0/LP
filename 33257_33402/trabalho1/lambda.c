#include "lambda.h"
#include <string.h>

//Ficheiro que serve para percorrer a arvore 

const char *alfabeto = "abcdefghijlmnopqrstuvwxyz";
char charsUsados[26] = "";
int indice = 0;

void printArray(char *array){
	for(int i=0; i<10; i++){
		printf("%c ", array[i]);
	}
	printf("\n");
}

int findCharList(char a, char *list, int indexSize){
	for(int i=indexSize; i>=0; i--){
		if (list[i]==a){
			return i;
		}
	}
	return -1;
}

//FUNCAO QUE GERA LETRAS
char geraLetra(){
	while (1){
		char alfabeto = "abcdefghijlmnopqrstuvwxyz"[random()%26];
		for(int i=0; i<26; i++){
			if (alfabeto == charsUsados[i]){
				break;
			}
			if (i==25){
				strcpy(&charsUsados[indice++], &alfabeto); 
				return alfabeto;
			}
		}

	}
	strcpy(&charsUsados[indice++], &alfabeto); 
	return alfabeto;
}


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
	char charsAlterar[10] ="";
	char charSubstituicao[10] ="";
	int index =0;
	printf("<-");	
	printTerms(root);
	printf("\n");
	goTerms(root, charsAlterar, index, charSubstituicao);
	printf("->");
	printTerms(root);
	printf("\n");
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
		printf("%c", root->letter[0]);
	}else if(root->type == letter_terms){
		if (search(root->letter) ==1){	
			strcpy(&charsUsados[indice++],root->letter);
		}
		printf("%c", root->letter[0]);		
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

void goTerms( Terms *root, char *charsAlterar, int index, char *charSubstituicao){
	
	if (root->type == term_terms){
		goSTerm(root->sterm, charsAlterar, index, charSubstituicao);

		goTerms(root->terms, charsAlterar, index, charSubstituicao);

	}else if(root->type == term_){
		goSTerm(root->sterm, charsAlterar, index, charSubstituicao);
	}
}

void goSTerm(STerm *root,char *charsAlterar, int index, char *charSubstituicao){
	
	if (root->type == abs_){
		goAbs(root->abs, charsAlterar, index, charSubstituicao);	
	}else if(root->type == app_){
		goApp(root->app, charsAlterar, index, charSubstituicao);
	}else if(root->type == par_terms){
		goTerms(root->terms, charsAlterar, index, charSubstituicao);
	}
}


void goApp(App *root, char *charsAlterar, int index, char *charSubstituicao){
		int x =0;
		x = findCharList(*root->letter, charsAlterar, 10);
		// CASO ACHE O CHAR DA APP NA LISTA DE SUBSTITUIÇÂO, SUBSTITUI
		if(x!=-1){
			char c = charSubstituicao[x];
			strcpy(root->letter, &c);
		
			}if(root->type == letter_terms){
			goTerms(root->terms, charsAlterar, index, charSubstituicao);
		}
}


void goAbs(Abs *root, char *charsAlterar, int index, char *charSubstituicao){
	
	if (search(root->letter) ==1){	
		strcpy(&charsUsados[indice++],root->letter);
	}
	//ADICIONAR LETRA AO ARERAY DE CHARS 
	char c = geraLetra();
	strcpy(&charsAlterar[index],root->letter);
	strcpy(&charSubstituicao[index++], &c);
	strcpy(root->letter, &c);
	//COPIAR PARA ARVORE A NOVA LETRA
//	strcpy(root->letter, &geraLetra());
	if (root->terms != NULL){
		goTerms(root->terms, charsAlterar, index, charSubstituicao);
		//REMOVER CHAR DO ARRAY
		char c = ' ';
		index--;
		strcpy(&charsAlterar[index], &c);
		strcpy(&charSubstituicao[index--], &c);
	}	

}
