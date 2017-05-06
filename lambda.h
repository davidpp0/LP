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

void goTerms( Terms *root);
void goSTerm(STerm *root);
void goApp(App *root);
void goAbs(Abs *root);