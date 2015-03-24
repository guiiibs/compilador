
// Testar se funciona corretamente o empilhamento de parâmetros
// passados por valor ou por referência.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"

int numVars;
char buffer[256];


%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO

%token MAIS MENOS MULT ABRE_COLCHETES FECHA_COLCHETES LABEL
%token TYPE ARRAY OF GOTO IF THEN ELSE WHILE DO OR
%token DIV AND NOT
%token IGUAL DIFERENTE MENOR_IGUAL MAIOR_IGUAL MENOR MAIOR
%token INTEGER BOOLEAN




%%
//------------PROGRAM---------------------------------------------
programa    :{ 
             geraCodigo (NULL, "INPP");
             }
             PROGRAM IDENT 
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO 
             {
			    sprintf ( buffer, "DMEM %d", numVars);
			    geraCodigo(NULL, buffer);
                geraCodigo (NULL, "PARA");
             }
;
//----------------------------------------------------------------

//-------------BLOCO----------------------------------------------
bloco       : 
              parte_declara_vars
              { 
              }

              comando_composto 
;
//----------------------------------------------------------------

//-------------DECLARAÇÃO DE VARIÁVEIS----------------------------
parte_declara_vars: parte_declara_vars PONTO_E_VIRGULA declara_vars
 			| 		VAR {numVars = 0;} declara_vars 
                    { 
                      sprintf ( buffer, "AMEM %d", numVars);
                      geraCodigo(NULL, buffer);
                    }
;

declara_vars: declara_vars declara_var 
            | declara_var 
;

declara_var : { }
              lista_id_var DOIS_PONTOS 
              tipo 
              { /* AMEM */

	          }
              PONTO_E_VIRGULA
;

tipo        : 	  INTEGER
				| BOOLEAN	
;

lista_id_var: lista_id_var VIRGULA IDENT 
              { /* insere última vars na tabela de símbolos */
				numVars++;
			 }
            | IDENT 
			  { /* insere vars na tabela de símbolos */
				numVars++;		
			 }
;

lista_idents: lista_idents VIRGULA IDENT  
            | IDENT
;
//---------------------------------------------------------------

//--------------COMANDO COMPOSTO---------------------------------

comando_composto: T_BEGIN comandos T_END
; 

comandos:		comandos PONTO_E_VIRGULA comando
				| comando
;

comando:		numeros DOIS_PONTOS comando_sem_rotulo
				| comando_sem_rotulo
;

numeros:		numero
				|
;

comando_sem_rotulo:	atribuicao
					| chamada_procedimento
					| desvio
					| comando_composto
					| comando_condicional
					| comando_repetitivo
;

//----------------ATRIBUIÇÃO--------------------------------------
atribuicao:		variavel ATRIBUICAO expressao
;

variavel:
;
//----------------------------------------------------------------

//----------------EXPRESSÃO---------------------------------------
expressao:		expressao_simples relacao expressao_simples
				| expressao_simples
;
expressao_simples:	expressao_simples MAIS termo
					| expressao_simples OR termo
					| termo

;

termo:			termo MULT fator
				| termo AND fator
				| fator
;

fator:			IDENT | ABRE_PARENTESES expressao_simples FECHA_PARENTESES
;

relacao:		IGUAL | DIFERENTE | MENOR_IGUAL | MAIOR_IGUAL | MENOR | MAIOR
;
//----------------------------------------------------------------

comando_repetitivo:		WHILE expressao DO comando_sem_rotulo
;

chamada_procedimento:
;

desvio:
;

comando_condicional:
;

numero:
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

