
// Testar se funciona corretamente o empilhamento de parâmetros
// passados por valor ou por referência.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "compilador.h"
#include "tab_simb.h"
#include "pilha.h"
#include "pilha_tipos.h"
#include "trataerro.h"





int numVars, nivel_lexico, deslocamento, totalVars, aux_tipo, cont_rotulo;

char *rotulo_mepa, *rotulo_mepa_aux;
char buffer[256]; //Usada no gera_código

Simbolo *simb, *simb_aux;
Tab_simb *tab_s;
PilhaT pilha_tipos, pilha_amem_dmem, pilha_rotulos;


%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO

%token MAIS MENOS MULT ABRE_COLCHETES FECHA_COLCHETES LABEL
%token TYPE ARRAY OF GOTO IF THEN ELSE WHILE DO OR
%token DIV AND NOT
%token IGUAL DIF MENOR_IGUAL MAIOR_IGUAL MENOR MAIOR
%token INTEGER BOOLEAN TRUE FALSE
%token NUMERO
%token READ WRITE
%token PROCEDURE FUNCTION



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
bloco       : rotulos parte_declara_vars  { empilhaAMEM(deslocamento, &pilha_amem_dmem);
                                            geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos);
                                            sprintf(buffer, "DSVS %s", rotulo_mepa);
                                            geraCodigo(NULL, buffer); }
              procs_funcs                 { geraCodigo (desempilha(&pilha_rotulos), "NADA"); }
              comando_composto
;

rotulos     : LABEL lista_nums PONTO_E_VIRGULA
            |
;
lista_nums  : NUMERO VIRGULA lista_nums
            | NUMERO
;
//----------------------------------------------------------------

//-------------DECLARAÇÃO DE VARIÁVEIS----------------------------
parte_declara_vars: var
;

var         : VAR         { deslocamento=0; }
              declara_vars
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

tipo        : INTEGER { aux_tipo = insereTipo(tab_s, T_INT);}
            | BOOLEAN { aux_tipo = insereTipo(tab_s, T_BOOL);}
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

lista_idents: lista_idents VIRGULA IDENT  			//Usado na lista de param do progrom
            | IDENT
;
//---------------------------------------------------------------

//-------------PROCEDIMENTOS E FUNÇÕES----------------------------
procs_funcs : PROCEDURE IDENT 				{ geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos);
											  sprintf(buffer, "ENPR %d", ++nivel_lexico);
											  geraCodigo(desempilha(&pilha_rotulos), buffer);
											  simb = insereSimbolo(tab_s, token, PROC, nivel_lexico);
											  simb->rotulo = rotulo_mepa;
											  /*empilha(&pilha_simbs, simb);*/
											  simb->qtd_parametros = numVars = 0;
											}
              params_proc_func PONTO_E_VIRGULA bloco_proc_func
            | FUNCTION IDENT 				{ geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos);
											  sprintf(buffer, "ENPR %d", ++nivel_lexico);
											  geraCodigo(desempilha(&pilha_rotulos), buffer);
											  simb = insereSimbolo(tab_s, token, FUNC, nivel_lexico);
											  simb->rotulo = rotulo_mepa;
											  /*empilha(&pilha_simbs, simb);*/
											  simb->qtd_parametros = numVars = 0;
											}
              params_proc_func
              DOIS_PONTOS
              tipo PONTO_E_VIRGULA bloco_proc_func
            | 
;

bloco_proc_func: rotulos parte_declara_vars 
              procs_funcs                      
              comando_composto PONTO_E_VIRGULA
              procs_funcs
;

params_proc_func: ABRE_PARENTESES
              lista_dec_param
              FECHA_PARENTESES
            |
;

lista_dec_param : lista_dec_param PONTO_E_VIRGULA
              { numVars=0; } parametros_dec
            | { numVars=0; } parametros_dec
            |
;

parametros_dec: VAR lista_id_par DOIS_PONTOS tipo 
            | lista_id_par DOIS_PONTOS tipo       
;
lista_id_par: lista_id_par VIRGULA IDENT
            | ident_ou_func                       
;
//---------------------------------------------------------------

//--------------COMANDO COMPOSTO---------------------------------

comando_composto: T_BEGIN comandos_ T_END
;
comandos_   : comandos
            |
;

comandos: comandos PONTO_E_VIRGULA comando
		| comando
;

comando:  NUMERO DOIS_PONTOS comando_sem_rotulo
		| comando_composto
	  	| comando_sem_rotulo
;



comando_sem_rotulo:	atrib_proc
            	| comando_condicional
           		| comando_repetitivo
            	| READ ABRE_PARENTESES lista_param_leit FECHA_PARENTESES
            	| WRITE ABRE_PARENTESES lista_param_impr FECHA_PARENTESES
            	| GOTO NUMERO
;
//---------------------------------------------------------------

//----------------READ E WRITE-------------------------------------
lista_param_leit: lista_param_leit VIRGULA IDENT  { geraCodigo (NULL, "LEIT"); simb = procuraSimbolo(tab_s, token, nivel_lexico); 
													geraCodigoARMZ(simb);

												  }
            | IDENT                               { geraCodigo (NULL, "LEIT"); simb = procuraSimbolo(tab_s, token, nivel_lexico); 
													geraCodigoARMZ(simb);
    											   }
;

lista_param_impr: lista_param_impr VIRGULA IDENT { simb = procuraSimbolo(tab_s, token, nivel_lexico);
												   /*geraCodigoARMZ(simb);*/
												 } 
            | IDENT                              { simb = procuraSimbolo(tab_s, token, nivel_lexico);
												   /*geraCodigoARMZ(simb);*/
												 } 
;
//---------------------------------------------------------------

//----------------IF------------------------------------------
comando_condicional:	if_simples
						|if_simples ELSE
;

if_simples:			IF
					expressao
					THEN
					comando
;
//---------------------------------------------------------------

//----------------WHILE---------------------------------------
comando_repetitivo:	WHILE
					expressao
					DO comando

;
//---------------------------------------------------------------

//----------------ATRIBUIÇÃO---------------------------------------
atrib_proc:		IDENT 		{ simb_aux = procuraSimbolo(tab_s, token, nivel_lexico); 
							  empilhaTipo(&pilha_tipos, simb_aux->tipo); /*proc_atual=simb_aux;*/ 
							}
				exec_ou_atrib
;

exec_ou_atrib: 	ATRIBUICAO expressao 			{ comparaTipo(&pilha_tipos, ATRIB, T_INT);
												  geraCodigoARMZ(simb_aux);
												}
				| exec_proc

;

exec_proc   : ABRE_PARENTESES  lista_de_parametros FECHA_PARENTESES 
            | ABRE_PARENTESES FECHA_PARENTESES
            |
;

lista_de_parametros: lista_de_parametros VIRGULA  expressao 
            | expressao
;

//----------------EXPRESSÃO---------------------------------------
expressao:		expressao_simples MAIOR expressao_simples			{ comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "CMMA"); }
				| expressao_simples MENOR expressao_simples			{ comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "CMME"); }
				| expressao_simples MAIOR_IGUAL expressao_simples	{ comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "CMAG"); }
				| expressao_simples MENOR_IGUAL expressao_simples	{ comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "CMEG"); }
				| expressao_simples IGUAL expressao_simples			{ comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "CMIG"); }
				| expressao_simples DIF expressao_simples			{ comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "CMDG"); }
				| expressao_simples
;
expressao_simples:	expressao_simples MAIS termo					{ comparaTipo(&pilha_tipos, CALC, T_INT); geraCodigo(NULL, "SOMA"); }
					| expressao_simples MENOS termo					{ comparaTipo(&pilha_tipos, CALC, T_INT); geraCodigo(NULL, "SUBT"); }
					| expressao_simples OR termo					{ comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "DISJ"); }
					| termo

;

termo:			termo MULT fator			{ comparaTipo(&pilha_tipos, CALC, T_INT); geraCodigo(NULL, "MULT"); }
				| termo DIV fator			{ comparaTipo(&pilha_tipos, CALC, T_INT); geraCodigo(NULL, "DIVI"); }
				| termo AND fator			{ comparaTipo(&pilha_tipos, COMPAR, T_BOOL); geraCodigo(NULL, "CONJ"); }
				| fator
;

fator:			ident_ou_func
				| ABRE_PARENTESES expressao_simples FECHA_PARENTESES
				| NUMERO					{ sprintf(buffer, "CRCT %d", atoi(token));
											  geraCodigo(NULL, buffer);
											  empilhaTipo(&pilha_tipos, T_INT);
											}
				| TRUE						{ geraCodigo (NULL, "CRCT 1"); empilhaTipo(&pilha_tipos, T_BOOL); }
				| FALSE						{ geraCodigo (NULL, "CRCT 0"); empilhaTipo(&pilha_tipos, T_BOOL); }
;


ident_ou_func  : IDENT   					{ simb = procuraSimbolo(tab_s, token, nivel_lexico); }
//----------------------------------------------------------------


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
 inicializaPilha(&pilha_tipos);

   yyin=fp;
   yyparse();

   return 0;
}

