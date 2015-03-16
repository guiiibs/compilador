
// Testar se funciona corretamente o empilhamento de parâmetros
// passados por valor ou por referência.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"

int num_vars;
char buffer[50];

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO
%token LABEL TYPE ARRAY GOTO IF THEN ELSE WHILE DO
%token OR AND DIV NOT

%%

programa    :{ 
             geraCodigo (NULL, "INPP"); 
             }
             PROGRAM IDENT 
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO {
             geraCodigo (NULL, "PARA"); 
             }
;

bloco       : 
              parte_declara_vars
              {
              }

              comando_composto 
              ;



//Regra 8
parte_declara_vars:  var 
;


var         : VAR {num_vars = 0;} declara_vars 
			  {
			   sprintf(buffer, "DMEM %d", num_vars);
			   geraCodigo(NULL, buffer);
			  }
            |
;

declara_vars: declara_vars declara_var 
            | declara_var 
;

//Regra 9
declara_var : { } 
              lista_id_var DOIS_PONTOS 
              tipo 
              {
			   sprintf(buffer, "AMEM %d", num_vars);
			   geraCodigo(NULL, buffer);
			   num_vars = 1;
              }
              PONTO_E_VIRGULA
;

tipo        : IDENT
;

//Regra 10
lista_id_var: lista_id_var VIRGULA IDENT 
              { /* insere última vars na tabela de símbolos */ }
            | IDENT { /* insere vars na tabela de símbolos */}
;

lista_idents: lista_idents VIRGULA IDENT
			  {
			   num_vars++;
			  }
            | IDENT
			  {
			   num_vars++;
			  }
;


comando_composto: T_BEGIN comandos T_END 

comandos:    
;


%%

main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de Símbolos
 * ------------------------------------------------------------------- */

   yyin=fp;
   yyparse();

   return 0;
}

