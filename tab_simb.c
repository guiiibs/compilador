#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "tab_simb.h"
#include "pilha.h"
#include "trataerro.h"


/* -------------------------------------------------------------------
 *  TABELA DE SIMBOLOS
 * ------------------------------------------------------------------- */
Tab_simb *iniciaTabelaSimbolo(Tab_simb *tab){
	int aux;
	if(tab != NULL){
		trataErro(ERRO_ALOCACAO, "");
	}
	else{
		tab = (Tab_simb *) malloc(sizeof(Tab_simb));
		tab->qtd_simbolos = 0;
		tab->bottom = tab->top = NULL;
	}
	//aux = imprimeTabSimbolos(tab);
	return tab;
}



Simbolo *procuraSimbolo(Tab_simb *tab, char *id, int nivel_l){
	int aux;
	Simbolo *simb;
	if (tab == NULL){
		trataErro(ERRO_TAB_NAO_ALOC, "ProcuraSimbolo");
	}
	else{
		simb = tab->top;
		while (simb != NULL){
			if (((strcmp(simb->id, id)) == 0) && (simb->nivel_lexico <= nivel_l)){
				break;			
			}
			simb = simb->ant;
		}
		//aux = imprimeTabSimbolos(tab);
		return simb;
	}
	//aux = imprimeTabSimbolos(tab);
	return NULL;
}

Simbolo *insereSimbolo(Tab_simb *tab, char *id, Categoria cat, int nivel_l){
	int aux;
	Simbolo *simb;	
	if (tab == NULL){
		trataErro(ERRO_TAB_NAO_ALOC, "InsereSimbolo");		//Criar tratamento de erro
	}
	else{
		simb = procuraSimbolo(tab, id, nivel_l);
		if (simb != NULL){		//Simbolo já declarado
			trataErro(WARN_IDENT_JA_DEC, id);
		}
		else{
			simb = malloc(sizeof(Simbolo));
			if (simb == NULL){
				trataErro(ERRO_ALOCACAO, "");
			}
			strcpy(simb->id, id);
			simb->nivel_lexico = nivel_l;      		
			simb->categoria = cat;
     		
		  tab->qtd_simbolos++;

			if (tab->qtd_simbolos == 1) {
        		tab->bottom = simb;
       			simb->ant = simb->prox = NULL;
      		}
      		else {
        		simb->ant  = tab->top;
        		simb->ant->prox  = simb;
        		simb->prox = NULL;
        		simb->tipo = T_UNSET;   //Atribui simbolo 
      		}
      		tab->top = simb;
		}
	}
	aux = imprimeTabSimbolos(tab);
	return simb;
}

int removeSimboloTop(Tab_simb *tab){
	Simbolo *simb;
  if (tab == NULL)
		trataErro(ERRO_TAB_NAO_ALOC, "");
	else{
      simb = tab->top;
      tab->top = tab->top->ant;
      tab->qtd_simbolos--;
      free(simb);
  }
  return 0;
}



int imprimeTabSimbolos(Tab_simb *tab) {
  Simbolo *simb;
  if (tab == NULL ) {
    trataErro(ERRO_TAB_NAO_ALOC, "");
  }
  else {
    fprintf(stderr," tab->qtd_simbolos = %d\n", tab->qtd_simbolos); // #DEBUG
    simb = tab->bottom;
    while (simb != NULL) {
      fprintf(stderr,"simbolo->id= %-5s  tipo= %d categoria= %d nivel_lexico,deslocamento=(%d,%d)\n", simb->id, simb->tipo, simb->categoria, simb->nivel_lexico, simb->deslocamento);
      simb = simb->prox;
    }
  }
  return 0;
}



int insereTipo(Tab_simb *tab, Tipo tipo) {
  Simbolo *simb;
  int i;
  if (tab == NULL ) {
    trataErro(ERRO_TAB_NAO_ALOC, "");  }
  else {
    i=0;
    simb = tab->top;
    while (simb->tipo == T_UNSET) {
      if (simb->categoria == VAR_S || simb->categoria == FUNC || simb->categoria == PF) {
        simb->tipo = tipo;
        i++;
      }
      else {
        break;
      }
      simb = simb->ant;
    }
    return i;
  }
  return -1;
}



