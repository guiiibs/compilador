
// Testar se funciona corretamente o empilhamento de parâmetros
// passados por valor ou por referência.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "tab_simb.h"


char buffer[256]; //Usada no gera_código

int numVars, nivel_lexico, deslocamento, totalVars;

Simbolo *simb;
Tab_simb *tab_s;


%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO

%token MAIS MENOS MULT ABRE_COLCHETES FECHA_COLCHETES LABEL
%token TYPE ARRAY OF GOTO IF THEN ELSE WHILE DO OR
%token DIV AND NOT
%token IGUAL DIF MENOR_IGUAL MAIOR_IGUAL MENOR MAIOR
%token INTEGER BOOLEAN
%token NUMERO




%%
//------------PROGRAM---------------------------------------------
programa    :{ 
             	geraCodigo (NULL, "INPP");
			 	nivel_lexico = deslocamento = 0;
			 	tab_s = iniciaTabelaSimbolo(tab_s);
             }
             PROGRAM IDENT { simb = insereSimbolo(tab_s, token, PROG, 0);}
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO 
             {
			    sprintf ( buffer, "DMEM %d", totalVars);
			    geraCodigo(NULL, buffer);
                geraCodigo (NULL, "PARA");
				//aux = imprimeTabSimbolos(tab_s);
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
parte_declara_vars: var
;

var         : VAR { deslocamento= 0; totalVars = 0; }declara_vars
            |
;

declara_vars: declara_vars { numVars=0; } declara_var
            | { numVars=0; }declara_var
;

declara_var : lista_id_var DOIS_PONTOS tipo
			 {
			 	sprintf ( buffer, "AMEM %d", numVars);
				totalVars += numVars;
				geraCodigo(NULL, buffer);
				
			 }
              PONTO_E_VIRGULA
;

tipo        : INTEGER
            | BOOLEAN
;

lista_id_var: lista_id_var VIRGULA IDENT  
			{ numVars++; 
			  simb = insereSimbolo(tab_s, token, VAR_S, nivel_lexico);
			  simb->deslocamento = deslocamento++; } /* insere ultima var na tabela de simbolos */
            | IDENT
            { numVars++;
			  simb = insereSimbolo(tab_s, token, VAR_S, nivel_lexico);
			  simb->deslocamento = deslocamento++; } /* insere vars na tabela de simbolos */
;

lista_idents: lista_idents VIRGULA IDENT  
            | IDENT
;
//---------------------------------------------------------------

//--------------COMANDO COMPOSTO---------------------------------

comando_composto: T_BEGIN comandos T_END
; 

comandos: comandos PONTO_E_VIRGULA comando
		| comando
;

comando:  NUMERO DOIS_PONTOS comando_sem_rotulo
	  	| comando_sem_rotulo
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
expressao:		expressao_simples MAIOR expressao_simples
				| expressao_simples MENOR expressao_simples
				| expressao_simples MAIOR_IGUAL expressao_simples
				| expressao_simples MENOR_IGUAL expressao_simples
				| expressao_simples IGUAL expressao_simples
				| expressao_simples DIF expressao_simples
				| expressao_simples
;
expressao_simples:	expressao_simples MAIS termo
					| expressao_simples MENOS termo
					| expressao_simples OR termo
					| termo

;

termo:			termo MULT fator
				| termo DIV fator
				| termo AND fator
				| fator
;

fator:			IDENT | ABRE_PARENTESES expressao_simples FECHA_PARENTESES
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

