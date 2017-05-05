#include "tree.h"


Terms *newTerm(terms_type type, Terms *terms, STerm *sterm){
	Terms *t = malloc(sizeof(struct Terms));
	t->type = type;
	t->terms = terms;
	t->sterm = sterm;
	return t;
}


STerm *newSTerm(sTerm_type type, Abs *abs, App *app, STerm *sterm){
	STerm *t = malloc(sizeof(struct STerm));
	t->type = type;
	t->abs = abs;
	t->app = app;
	t->sterm = sterm;
	return t;
}

App *newApp(appType type, Terms *terms, char *letter){
	App *t = malloc(sizeof(struct App));
	t->type = type;
	t->terms = terms;
	t->letter = strdup(letter);
	return t;
}

Abs *newAbs(char *letter, Terms *terms){
	Abs *t = malloc(sizeof(struct Abs));
	t->letter = strdup(letter);
	t->terms = terms; 
	return t; 
}

