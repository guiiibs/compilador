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



Simbolo *procuraSimbolo(Tab_simb *tab, char *id, int nivel_lexico) {
  Simbolo *simb;
  simb = retornaSimbolo(tab, id, nivel_lexico);

  if ( simb == NULL ) {
    trataErro(ERRO_SINT_IDENT_NAO_ENC, id);
  }
  return simb;
}

Simbolo *retornaSimbolo(Tab_simb *tab, char *id, int nivel_lexico) {
  Simbolo *simb;
  if (tab == NULL ) {
    trataErro(ERRO_TAB_NAO_ALOC, "");
   }
  else {
    simb=tab->top;
    while (simb != NULL) {
      if ( (strcmp(simb->id, id) == 0)  )// && (simb->nivel_lexico <= nivel_lexico))
        break;
      simb = simb->ant;
    }
    return simb;
  }
  return NULL;
}

Simbolo *insereSimbolo(Tab_simb *tab, char *id, Categoria cat, int nivel_l){
	int aux;
	Simbolo *simb;	
	if (tab == NULL){
		trataErro(ERRO_TAB_NAO_ALOC, "InsereSimbolo");		//Criar tratamento de erro
	}
	else{
		simb = retornaSimbolo(tab, id, nivel_l);
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

      if (cat == FUNC || cat == PROC){
        simb->lista_param = malloc (sizeof (Parametro) * TAM_LISTA_PARAM);
      }

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

int removeSimbolo(Tab_simb *tab, Simbolo *simb) {
  if (tab == NULL ) {
    trataErro(ERRO_TAB_NAO_ALOC, "");  }
  else {
    if ( simb == NULL ) {
      trataErro(ERRO_SIMB_NAO_ENC, "");
    }
    else {
      if (simb == tab->bottom) {
        tab->bottom = simb->prox;
      }
      else
        simb->ant->prox = simb->prox;
      if (simb == tab->top) {
        // debug_print("[ultimo1]simb->id = %s\n", simb->id);
        tab->top = simb->ant;
      }
      else
        simb->prox->ant = simb->ant;

      tab->qtd_simbolos--;
      // debug_print("[rm]simb->id = %s\n", simb->id);
      free(simb);
    }
  }
  return 0;
}

int removeFPSimbolos(Tab_simb *tab, Simbolo *pai) {
  Simbolo *simb;
  int nivel_lexico;
  int num_var_simples;

  if (tab == NULL ) {
    trataErro(ERRO_TAB_NAO_ALOC, "");  }
  else {
    simb = pai;
    if ( simb == NULL ) {
      trataErro(ERRO_SIMB_NAO_ENC, "");
    }
    else {
      nivel_lexico = simb->nivel_lexico;
      num_var_simples = 0;
      while ( (simb=simb->prox) != NULL) {
        num_var_simples++;
        removeSimbolo(tab, simb);
      }
    }
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

int inserePassagemParam(Tab_simb *tab, Passagem passagem, int num_vars) {
  Simbolo *simb;
  int i;
  if (tab == NULL ) {
    trataErro(ERRO_TAB_NAO_ALOC, "");
  }
  else {
    simb = tab->top;
    for (i = 0; i < num_vars; i++) {
      simb->passagem = passagem;
      simb = simb->ant;
    }
    return i;
  }
  return -1;
}

int setaDeslocamentoParam(Tab_simb *tab, int num_parametros) {
  Simbolo *simb;
  int i;
  if (tab == NULL ) {
    trataErro(ERRO_TAB_NAO_ALOC, "");  }
  else {
    simb = tab->top;
    for (i = num_parametros; i >= 0; i--) {
      simb->deslocamento = i - (4 + num_parametros);
      simb = simb->ant;
    }
    return i;
  }
  return -1;
}

int insereParamLista(Simbolo  *simb, Tipo tipo, Passagem passagem, int n_params) {
  int i;
  if (simb == NULL ) {
    trataErro(ERRO_PARAM_NAO_ENC, "");
  }
  else {
    if (simb->qtd_parametros >= TAM_LISTA_PARAM ) {
      trataErro(ERRO_MAX_PARAM, "");
    }
    else {
      if (simb->lista_param == NULL ) {
        trataErro(ERRO_LISTA_PARAM_NAO_ALOC, "");
      }
      else {
        for (i=0; i < n_params; i++) { // #TODO inverter a ordem?
          // debug_print("[for] simb->id = %s, passagem = %d, soma = %d\n", simb->id, passagem, (simb->qtd_parametros - n_params + i));
          simb->lista_param[simb->qtd_parametros - n_params + i].tipo = tipo;
          simb->lista_param[simb->qtd_parametros - n_params + i].passagem = passagem;
          // simb->prox->tipo = tipo;
        }
      }
    }
  }
  return 0;
}