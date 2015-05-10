#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "tab_simb.h"




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
	//aux = imprimeTabSimbolos(tab);
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
  Simbolo *simbolo;
  int total_simbolos = 0;
  if (tab == NULL ) {
    trataErro(ERRO_TAB_NAO_ALOC, "");
  }
  else {
    fprintf(stderr," tab->qtd_simbolos = %d\n", tab->qtd_simbolos); // #DEBUG
    simbolo = tab->bottom;
    while (simbolo != NULL) {
      fprintf(stderr,"simbolo->id= %-5s  tipo(cod)= %d categoria= %d nivel_lexico,deslocamento=(%d,%d)\n", simbolo->id, simbolo->tipo, simbolo->categoria, simbolo->nivel_lexico, simbolo->deslocamento);
      total_simbolos++;
      simbolo = simbolo->prox;
    }
  }
  fprintf(stderr," Total de simbolos = %d\n", total_simbolos); // #DEBUG
  return 0;
}

/* -------------------------------------------------------------------
 *  TIPOS
 * ------------------------------------------------------------------- */

int verificaTipo(Tipo type){
  Tipo a, b;
  a = desempilhaTipo();
  b = desempilhaTipo();

  if (a == b && type == a)
    return 1;
  if (strcmp(a,b->tipo) == 0 && strcmp(tipo, a->tipo) == 0)
    retorno = 1;
  else
    retorno = 0;

  empilhaTipo(a->tipo);
  free(a);
  free(b);
  return retorno;
}


/* -------------------------------------------------------------------
 *  TRATAMENTO DE ERROS
 * ------------------------------------------------------------------- */

 int trataErro(ErroT cod_erro, char *str) {
  switch (cod_erro) {
  case SEM_ERRO:
    break;

    /* Erros Sintaticos */
  case ERRO_SINT_IDENT_NAO_ENC:
    fprintf(stderr, "ERRO: *** Erro sintatico!\n => O identificador '%s' nao foi encontrado.\n", str);
    exit(cod_erro);
  case ERRO_IDENT_JA_DEC:
    fprintf(stderr, "ERRO: *** Erro sintatico!\n => O identificador '%s' jah foi declarado anteriormente.\n", str);
    exit(cod_erro);
  case ERRO_TIPO:
    fprintf(stderr, "ERRO: *** Erro sintatico!\n => Tipos incompatíveis!\n");
    exit(cod_erro);

  case ERRO_TAB_NAO_ALOC:
    fprintf(stderr, "ERRO: *** Tabela de simbolos dinamica nao foi alocada na funcao '%s'!\n", str);	
    exit(cod_erro);
  case ERRO_SIMB_NAO_ENC:
    fprintf(stderr, "ERRO: *** Impossivel remover!\n => O simbolo %s nao foi encontrado.\n", str);
    exit(cod_erro);

    /* Lista de Parametros */
  case ERRO_LISTA_PARAM_NAO_ALOC:
    fprintf(stderr, "ERRO: *** A Lista Parametros nao foi alocada!\n");
    exit(cod_erro);
  case ERRO_PARAM_NAO_ENC:
    fprintf(stderr, "ERRO: *** O Parametro nao foi encontrado, impossivel inserir na Lista de Parametros!\n");
    exit(cod_erro);
  case ERRO_MAX_PARAM:
    //fprintf(stderr, "ERRO: ***\n => O numero de Parametros (%d) passou do limite interno.\n", TAM_LISTA_PARAM);
    exit(cod_erro);

    /* PILHA */
  case ERRO_PILHA_N_EXISTE:
    fprintf(stderr, "ERRO: *** Impossivel desempilhar, a Pilha nao existe!\n");
    exit(cod_erro);
  case ERRO_PILHA_VAZIA:
    fprintf(stderr, "ERRO: *** Impossivel desempilhar, a Pilha está vazia!\n");
    exit(cod_erro);
  case ERRO_PILHA_TAM_EXCED:
    //fprintf(stderr, "ERRO: *** Tamanho da pilha (%d elementos) excedido!\n", PILHA_TAM);
    exit(cod_erro);

  case ERRO_ALOCACAO:
    fprintf(stderr, "ERRO: *** Nao foi possivel alocar espaco na memoria!\n");
    exit(cod_erro);

    /* WARNING */  
  case WARN_IDENT_JA_DEC:
    fprintf(stderr, "Warning:\n => O identificador '%s' jah foi declarado anteriormente.\n", str);
    break;

  default:
    fprintf(stderr, "ERRO: *** Erro desconhecido!\n");
    exit(cod_erro);
  }
  return 0;
}