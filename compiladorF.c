
/* -------------------------------------------------------------------
 *            Aquivo: compilador.c
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 08/2007
 *      Atualizado em: [15/03/2012, 08h:22m]
 *
 * -------------------------------------------------------------------
 *
 * Funções auxiliares ao compilador
 *
 * ------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "tab_simb.h"
#include "pilha.h"
#include "trataerro.h"


/* -------------------------------------------------------------------
 *  variáveis globais
 * ------------------------------------------------------------------- */
#define ROTULO_TAM 7  /* Tamanho maximo do 'char' para o rotulo no MEPA  */





FILE* fp=NULL;
void geraCodigo (char* rot, char* comando) {

  if (fp == NULL) {
    fp = fopen ("MEPA", "w");
  }

  if ( rot == NULL ) {
    fprintf(fp, "     %s\n", comando); fflush(fp);
  } else {
    fprintf(fp, "%s: %s \n", rot, comando); fflush(fp);
  }
}


void empilhaAMEM(int n_vars, PilhaT *pilha_amem_dmem){
  int *temp_num;
  temp_num = malloc (sizeof (int));
    *temp_num = n_vars;
      empilha(pilha_amem_dmem, temp_num);
}

int geraRotulo(char **novo_rotulo, int *contador, PilhaT *pilha_rot) {
  char *rot;

  *novo_rotulo = malloc (sizeof (char [ROTULO_TAM]));
  if (*novo_rotulo == NULL) {
    trataErro(ERRO_ALOCACAO, "");
  }
  sprintf(*novo_rotulo, "R%02d", *contador);
  *contador = *contador + 1;
  
  empilha(pilha_rot, *novo_rotulo);

  return 0;
}



void geraCodigoARMZ(Simbolo *simb){
  char buffer[256];
  if (simb->passagem == VALOR) { 
    sprintf(buffer, "ARMZ %d,%d", simb->nivel_lexico, simb->deslocamento );
    geraCodigo (NULL, buffer); 
  } 
    else { 
      sprintf(buffer,"ARMI %d,%d", simb->nivel_lexico, simb->deslocamento);
      geraCodigo (NULL, buffer);
    }
}

int imprimeErro ( char* erro ) {
  fprintf (stderr, "Erro na linha %d - %s\n", nl, erro);
  exit(-1);
}














