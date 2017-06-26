#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum termsType {
	term_terms,
	term_	
}terms_type;

typedef enum sTermType{
	abs_,
	app_,
	par_terms
}sTerm_type;

typedef enum appType
{
	letter_,
	letter_terms
}appType;

typedef struct Terms Terms;
typedef struct STerm STerm;
typedef struct App App;
typedef struct Abs Abs;

struct Terms
{
	terms_type type;
	Terms *terms;
	STerm *sterm;
};

struct STerm
{
	sTerm_type type;
	Abs *abs;
	App *app;
	Terms *terms;
};

struct App
{
	appType type;
	Terms *terms;
	char *letter;

};

struct Abs
{
	char *letter;
	Terms *terms;
};

Terms *newTerm(terms_type type, Terms *terms, STerm *sterm);
STerm *newSTerm(sTerm_type type, Abs *abs, App *app, Terms *terms);
App *newApp(appType type, Terms *terms, char *letter);
Abs *newAbs(char *letter, Terms *terms);
