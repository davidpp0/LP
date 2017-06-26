#include <stdio.h>
#include <string.h>
#include "tree.c"

int search(char *a);
void root(Terms *root);
void prinTree( Terms *root);
void printTerms( Terms *root);
void printSTerm(STerm *root);
void printApp(App *root);
void printAbs(Abs *root);

void goTerms( Terms *root, char *charsAlterar, int index, char *charSubstituicao);
void goSTerm(STerm *root, char *charsAlterar, int index, char *charSubstituicao);
void goApp(App *root, char *charsAlterar, int index, char *charSubstituicao);
void goAbs(Abs *root, char *charsAlterar, int index, char *charSubstituicao);

void goToTerms( Terms *root);
void goToSTerm(STerm *root);
void goToApp(App *root);
void goToAbs(Abs *root);


Terms *CopyTerms( Terms *root);
STerm *CopySTerm(STerm *root);
App *CopyApp(App *root);
Abs *CopyAbs(Abs *root);