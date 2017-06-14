#include "lambda.h"
#include <string.h>

//Ficheiro que serve para percorrer a arvore 

const char *alfabeto = "abcdefghijlmnopqrstuvwxyz";
char charsUsados[26] = "";
int indice = 0;
char singleChar[1]= "";
STerm *newSterm = NULL;

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
//	printf("<-");	
//	printTerms(root);
	printf("\n");	
	goToTerms(root);
	printf("->");
	printTerms(root);
	printf("\n");
	/*
	goTerms(root, charsAlterar, index, charSubstituicao);
	printf("->");
	printTerms(root);
	printf("\n");
	*/
}

//FUNCOES DE IMPRIMIR ARVORE----------------------------
void printTerms( Terms *root){
	if (root->type == term_terms){
		if (root->sterm != NULL){
			printSTerm(root->sterm);
		}
		if (root->terms != NULL){
			printTerms(root->terms);
		}
	}else if(root->type == term_){
		if (root->sterm != NULL){
			printSTerm(root->sterm);
		}
	}
}

void printSTerm(STerm *root){
	if (root->type == abs_){
		if(root->abs != NULL){
			printAbs(root->abs);	
		}
	}else if(root->type == app_){
		if(root->app!= NULL){
			printApp(root->app);
		}
	}else if(root->type == par_terms){
		if (root->terms!=NULL){
			printf("(");
			printTerms(root->terms);
			printf(")");
		}
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
		if(root->terms!=NULL){
			printTerms(root->terms);
		}
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
		// CASO ACHE O CHAR DA APP NA LISTA DE SUBSTITUICAO, SUBSTITUI
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




///                 MODULO2                                        ////////////////////

void goToTerms( Terms *root){
	if (root->type == term_terms){
		printf("term_terms\n");
		
		if(strcmp("",singleChar)!=0 && newSterm != NULL && (root->sterm->type == app_)){
			root->sterm = newSterm;
			root->type = newSterm->type;
			return;
		///RESET DAS VARS DE SUBSTITUICAO
		}
		//VERIFICA SE O ARRAY TEM ALGUM CHAR P SUBSTITUIR
		//VERIFICA SE O PRIMEIRO TERMO TEM PARENTISES
		//VERIFICA SE ESSE TERMO TEM UMA ABS DENTRO
		//OBJ: GUARDAR A LETRA DA PRIM ABS A SUBSTITUIR
		if(strcmp("",singleChar) == 0 && root->sterm-> type == par_terms && root->sterm->terms->sterm-> type == abs_){
				strcpy(&singleChar[0],root->sterm->terms->sterm->abs->letter);
		}

		if(strcmp("",singleChar) != 0 && newSterm == NULL){
			newSterm = CopySTerm(root->terms->sterm);
			printSTerm(newSterm);
		}
		if (root->sterm!=NULL){
			goToSTerm(root->sterm);
		}
		if(root->terms!=NULL){
			goToTerms(root->terms);
		}
		
	else if(root->type == term_){
		printf("term_\n");
	 	if (root->sterm!=NULL){
			goToSTerm(root->sterm);
		}
	}
	
	}

}

void goToSTerm(STerm *root){
	if (root->type == abs_){
		printf("abs_\n");
		if(root->abs!=NULL){	
			goToAbs(root->abs);
		}	
	}else if(root->type == app_){
		printf("app_\n");
		if(root->app != NULL){	
			goToApp(root->app);
		}
	}else if(root->type == par_terms){
		printf("par_terms\n");
		printf("(\n");
		if(root->terms!=NULL){	
			goToTerms(root->terms);
		}
		printf(")\n");
	}

}


void goToApp(App *root){
	if (root->type == letter_){
		printf("letter_\n");
	}else if(root->type == letter_terms){
		printf("letter_terms\n");
		if (root->terms!=NULL){	
			goToTerms(root->terms);
		}
	}
}

void goToAbs(Abs *root){
	
	if (root->terms != NULL){
		goToTerms(root->terms);
	}

}



Terms *CopyTerms( Terms *root){
	Terms *s = malloc(sizeof(Terms));
	if (root->type == term_terms){
		s->type = term_terms;
		if (root->sterm != NULL){
			s->sterm = CopySTerm(root->sterm);
		}
		if (root->terms != NULL){
			s->terms = CopyTerms(root->terms);
		}
	}else if(root->type == term_){
		s->type = term_;
		if (root->sterm != NULL){
			s->sterm = CopySTerm(root->sterm);
		}
	}
	return s;
}


STerm *CopySTerm(STerm *root){
	STerm *s = malloc(sizeof(STerm));
	if (root->type == abs_){
		if(root->abs != NULL){
			s->type = abs_;
			s->abs = CopyAbs(root->abs);	
		
		}
	}else if(root->type == app_){
		if(root->app!= NULL){
			s->type = app_;
			s->app = CopyApp(root->app);
		
		}
	}else if(root->type == par_terms){
		if (root->terms!=NULL){
			s->type = par_terms;
			s->terms = CopyTerms(root->terms);		
		}
	}
	return s;
}

App *CopyApp(App *root){
	App *s = malloc(sizeof(App));
	if (root->type == letter_){
		s->type= letter_;
		s->letter = root->letter;
	}else if(root->type == letter_terms){
		s->type = letter_terms;
		s->letter= root->letter;
				
		if(root->terms!=NULL){
			s->terms = CopyTerms(root->terms);
		}
	}
	return s;
}

Abs *CopyAbs(Abs *root){
	Abs *s = malloc(sizeof(Abs));
	s->letter = root->letter;
	if (root->terms != NULL){
		s->terms = CopyTerms(root->terms);
	}
	return s;
}


