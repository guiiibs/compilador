#include <stdio.h>
#include <stdlib.h>





int cria_tab_simb(Tab_simb *tab){
	if (tab == NULL){
		return -1;	
	}
	else {
		pilha->top = 0;
		return 0;	
	}		
}

Simbolo *insereSimbolo(Tab_simb *tab, char *id, Categoria cat, int nivel_l){
	Simbolo *simbolo;	
	if (tab == NULL){
		return -1;		//Criar tratamento de erro
	}
	else{
		simbolo = procuraSimbolo(tab, id, nivel_l);
		if (simbolo != NULL){		//Simbolo já declarado
			return -1;
		}
		else{
			simbolo = malloc(sizeof(Simbolo));
			if (simbolo == NULL){
				return -1;
			}
			 
		}
	}
