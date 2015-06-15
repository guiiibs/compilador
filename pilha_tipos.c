#include <stdio.h>
#include <stdlib.h>
#include "compilador.h"
#include "tab_simb.h"
#include "pilha.h"
#include "trataerro.h"
#include "pilha_tipos.h"

int empilhaTipo(PilhaT *pilha, Tipo novo_tipo) {
  Tipo *tipo_aux;

  tipo_aux = malloc (sizeof (Tipo));
  if (tipo_aux == NULL) {
    trataErro(ERRO_ALOCACAO, "");
  }
  *tipo_aux = novo_tipo;
  empilha(pilha, tipo_aux);

  return 0;
}

int comparaTipo(PilhaT *pilha, OperacaoT op, Tipo tipo_esperado) {
  Tipo tipo_esquerda, tipo_direita;
  
  int i;
  if (pilha == NULL ) {
    trataErro(ERRO_PILHA_N_EXISTE, "");
  }
  else {
    tipo_direita= *(Tipo *)desempilha(pilha);
    tipo_esquerda= *(Tipo *)desempilha(pilha);
    switch (op) {
      case CALC:
        empilhaTipo(pilha, tipo_direita);
        break;
      case COMPAR:
        empilhaTipo(pilha, T_BOOL);
        break;
      case ATRIB:
        empilhaTipo(pilha, tipo_esquerda);
        break;
      }
    if (tipo_esquerda == tipo_direita)
      return 1;
    else
      trataErro(ERRO_TIPO, "");
      return 0;
  } 
  return 0;
}
