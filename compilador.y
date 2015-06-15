
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





int numVars, nivel_lexico, deslocamento, totalVars, indice_param, cont_rotulo, teste = 0;

char *rotulo_mepa, *rotulo_mepa_aux;
char buffer[256]; //Usada no gera_código

Simbolo *simb, *simb_aux, *proc_atual;
Tab_simb *tab_s;
PilhaT pilha_tipos, pilha_amem_dmem, pilha_rotulos, pilha_simbolos;
bool chamada_de_proc;
Tipo aux_tipo;

#define geraCodigoCRxx(instrucao, simbolo) \
  sprintf(buffer, "%s %d, %d", instrucao, simbolo->nivel_lexico, simbolo->deslocamento); \
  geraCodigo(NULL, buffer );

#define geraCodigoCV(simbolo) \
  if (chamada_de_proc) { teste++;\
    if (proc_atual != NULL) { \
      if ((proc_atual->lista_param[indice_param].passagem == REF) && (simbolo->passagem == VALOR)) { geraCodigoCRxx("CREN", simbolo); } \
      else { geraCodigoCRxx("CRVL", simbolo); } }\
    else { geraCodigoCRxx("CRVL", simbolo); } } \
  else if (simbolo->passagem == VALOR) { \
  	sprintf(buffer, "CRVL %d, %d", simbolo->nivel_lexico, simbolo->deslocamento); \
  	geraCodigo(NULL, buffer); } \
    else { geraCodigoCRxx("CRVI", simbolo); }
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

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


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
             {	numVars = *(int *)desempilha(&pilha_amem_dmem);
    			if (numVars) {
					sprintf ( buffer, "DMEM %d", totalVars);
					geraCodigo(NULL, buffer);
				}
                geraCodigo (NULL, "PARA");
				//aux = imprimeTabSimbolos(tab_s);
             }
;
//----------------------------------------------------------------

//-------------BLOCO----------------------------------------------
bloco       : rotulos parte_declara_vars  { empilhaVars(deslocamento, &pilha_amem_dmem);
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
				inserePassagemParam(tab_s, VALOR, numVars);
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
/*Gera o rotulo, empilha, faz ENPR*/		  geraCodigo(desempilha(&pilha_rotulos), buffer);
/*Desempilha, atribui o rot pro simb*/		  simb = insereSimbolo(tab_s, token, PROC, nivel_lexico);
											  simb->rotulo = rotulo_mepa;
											  empilha(&pilha_simbolos, simb);
											  simb->qtd_parametros = numVars = 0;
											}
              params_proc_func PONTO_E_VIRGULA bloco_proc_func
            | FUNCTION IDENT 				{ geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos);
											  sprintf(buffer, "ENPR %d", ++nivel_lexico);
											  geraCodigo(desempilha(&pilha_rotulos), buffer);
											  simb = insereSimbolo(tab_s, token, FUNC, nivel_lexico);
											  simb->rotulo = rotulo_mepa;
											  empilha(&pilha_simbolos, simb);
											  simb->qtd_parametros = numVars = 0;
											}
              params_proc_func
              DOIS_PONTOS
              tipo PONTO_E_VIRGULA bloco_proc_func
            | 
;

bloco_proc_func: rotulos parte_declara_vars     { empilhaVars(deslocamento); geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos);
                                                  sprintf(buffer, "DSVS %s", rotulo_mepa);
                                                  geraCodigo(NULL, buffer); }
              procs_funcs                       { geraCodigo(desempilha(&pilha_rotulos), "NADA"); }
              comando_composto PONTO_E_VIRGULA  { numVars = *(int *)desempilha(&pilha_amem_dmem);
              									  if (numVars){
              									  	sprintf(buffer,"DMEM %d", numVars );
              									  	geraCodigo(NULL, buffer);
              									  }
              									  simb = desempilha(&pilha_simbolos); removeFPSimbolos(tab_s, simb);	
              									  sprintf(buffer, "RTPR %d, %d", nivel_lexico--, simb->qtd_parametros);
                                                  geraCodigo(NULL, buffer ); 
                                                }
              procs_funcs
;

params_proc_func: ABRE_PARENTESES
              lista_dec_param		{ setaDeslocamentoParam(tab_s, simb->qtd_parametros); 
              						  simb->end_retorno = -4 - simb->qtd_parametros; }
              FECHA_PARENTESES
            |
;

lista_dec_param : lista_dec_param PONTO_E_VIRGULA
              { numVars=0; } parametros_dec
            | { numVars=0; } parametros_dec
            |
;

parametros_dec: VAR lista_id_par DOIS_PONTOS tipo { inserePassagemParam(tab_s, REF, numVars); 		//Define passagem de parametro na ts 
													insereParamLista(simb, aux_tipo, REF, numVars);}	//insere lista de param no simb
            | lista_id_par DOIS_PONTOS tipo       { inserePassagemParam(tab_s, VALOR, numVars); 
													insereParamLista(simb, aux_tipo, VALOR, numVars);}
;
lista_id_par: lista_id_par VIRGULA IDENT 		  { simb->qtd_parametros++; numVars++; 
													simb_aux = insereSimbolo(tab_s, token, PF, nivel_lexico); simb_aux->pai = simb;}
            | ident_ou_func                       { simb->qtd_parametros++; numVars++; 
													simb_aux = insereSimbolo(tab_s, token, PF, nivel_lexico); simb_aux->pai = simb;}
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
												   geraCodigoCV(simb);
												   geraCodigo (NULL, "IMPR");
        										 } 
            | IDENT                              { simb = procuraSimbolo(tab_s, token, nivel_lexico);
												   geraCodigoCV(simb);
												   geraCodigo (NULL, "IMPR");
        										 } 
;
//---------------------------------------------------------------

//----------------IF------------------------------------------
comando_condicional:	if_simples %prec LOWER_THAN_ELSE  { geraCodigo (desempilha(&pilha_rotulos), "NADA"); }
            			| if_simples ELSE { rotulo_mepa=desempilha(&pilha_rotulos);
                                sprintf(buffer, "DSVS %s", rotulo_mepa_aux);
                                geraCodigo(NULL, buffer);
                                geraCodigo(rotulo_mepa, "NADA"); }
              			comando { geraCodigo(desempilha(&pilha_rotulos), "NADA"); }
;

if_simples:				IF  { geraRotulo(&rotulo_mepa_aux, &cont_rotulo, &pilha_rotulos);
                  			  geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos); }
      					expressao { sprintf(buffer, "DSVF %s", rotulo_mepa);
      								geraCodigo(NULL, buffer); }
      					THEN comando
//---------------------------------------------------------------

//----------------WHILE---------------------------------------
comando_repetitivo:		WHILE       { geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos);
                            		  geraCodigo (rotulo_mepa, "NADA"); }
              			expressao   { geraRotulo(&rotulo_mepa, &cont_rotulo, &pilha_rotulos);
              						  sprintf(buffer, "DSVF %s", rotulo_mepa);
                            		  geraCodigo(NULL, buffer); }
              			DO comando  { rotulo_mepa_aux=desempilha(&pilha_rotulos);
                            		  rotulo_mepa=desempilha(&pilha_rotulos);
                            		  sprintf(buffer, "DSVS %s", rotulo_mepa);
                            		  geraCodigo(NULL, buffer);
                            		  geraCodigo (rotulo_mepa_aux, "NADA"); }

;
//---------------------------------------------------------------

//----------------ATRIBUIÇÃO---------------------------------------
atrib_proc:		IDENT 		{ simb_aux = procuraSimbolo(tab_s, token, nivel_lexico); 
							  empilhaTipo(&pilha_tipos, simb_aux->tipo); proc_atual=simb_aux; 
							}
				exec_ou_atrib
;

exec_ou_atrib: 	ATRIBUICAO expressao 			{ comparaTipo(&pilha_tipos, ATRIB, T_INT);
												  geraCodigoARMZ(simb_aux);
												}
				| exec_proc						{ sprintf(buffer, "CHPR %s, %d", simb_aux->rotulo, nivel_lexico);
												  geraCodigo(NULL, buffer); } 

;

exec_proc   : ABRE_PARENTESES  { chamada_de_proc = true; indice_param=0; }
				lista_de_parametros FECHA_PARENTESES { chamada_de_proc = false; }
            | ABRE_PARENTESES FECHA_PARENTESES
            |
;

lista_de_parametros: lista_de_parametros VIRGULA { chamada_de_proc = true; ++indice_param; } expressao 
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


ident_ou_func  : IDENT   					{ simb = procuraSimbolo(tab_s, token, nivel_lexico); 
											  geraCodigoCV(simb); empilhaTipo(&pilha_tipos, simb->tipo);
}		
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
  inicializaPilha(&pilha_rotulos);
  inicializaPilha(&pilha_tipos);
  inicializaPilha(&pilha_simbolos);

   yyin=fp;
   yyparse();

   return 0;
}

