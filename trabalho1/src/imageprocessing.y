%{
#include <stdio.h>
#include "imageprocessing.h"
#include <FreeImage.h>

void yyerror(char *c);
int yylex(void);

%}
%union {
  char    strval[50];
  int     ival;
  float   fval;
}
%token <strval> STRING
%token <ival> VAR ASPA
%token <fval> NUM
%left SOMA

%%

PROGRAMA:
        PROGRAMA EXPRESSAO '\n'
        |
        ;

EXPRESSAO:
    | STRING '=' STRING {
        printf("Copiando %s para %s\n", $3, $1);
        imagem I = abrir_imagem($3);
        printf("Li imagem %d por %d\n", I.width, I.height);
        salvar_imagem($1, &I);
	printf("Imagem salva.\n");
        liberar_imagem(&I);
                          }
    | STRING '=' STRING '*' NUM {
        printf("Copiando %s para %s\n", $3, $1);
        imagem I = abrir_imagem($3);
        printf("Li imagem %d por %d\n", I.width, I.height);
	brilho(&I, 0, $5);
	printf("Dando brilho na imagem\n");
        salvar_imagem($1, &I);
	printf("Imagem salva.\n");
        liberar_imagem(&I);
                          }
    | STRING '=' STRING '/' NUM {
        printf("Copiando %s para %s\n", $3, $1);
        imagem I = abrir_imagem($3);
        printf("Li imagem %d por %d\n", I.width, I.height);
	brilho(&I, 1, $5);
	printf("Dando brilho na imagem.\n");
        salvar_imagem($1, &I);
	printf("Imagem salva.\n");
        liberar_imagem(&I);
                          }
    | '[' STRING ']' {
        imagem I = abrir_imagem($2);
        printf("Li imagem %d por %d\n", I.width, I.height);
	valor_maximo(&I);
        liberar_imagem(&I);
			  }
    ;

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main() {
  FreeImage_Initialise(0);
  yyparse();
  return 0;

}
