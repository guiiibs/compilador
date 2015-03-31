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


Simbolo *procuraSimbolo(Tab_simb *tab, char *id){
	Simbolo *simb;
	if (tab == NULL){
		return -1;
	}
	else{
		sim = tab->top;
		while (simb != NULL){
			if ((strcmp(simb->id, id)) == 0){
				break;			
			}
		}
		simb = simb->ant;
	}
	return NULL;
}

Simbolo *insereSimbolo(Tab_simb *tab, char *id, Categoria cat, int nivel_l){
	Simbolo *simb;	
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
			strcpy(simbolo->id, id);
			simbolo->nivel_lexico = nivel_l;      		
			simbolo->categoria = cat;
     		
		    tab->qtd_simbolos++;

			if (tab->num_simbolos == 1) {
        		tab->bottom = simbolo;
       			simbolo->ant = simbolo->prox = NULL;
      		}
      		else {
        		simbolo->ant  = tab->top;
        		simbolo->ant->prox  = simbolo;
        		simbolo->prox = NULL;
        		simbolo->tipo = UNSET;
      		}
      		tab->top = simbolo;
		}
	}
	return simbolo;
}
