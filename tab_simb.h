

/* VAR_S = variavel simples
	 PROC = procedimento
	 ROT = rotulo
	 FUNC = funcao
	 PROG = nome do programa
*/
typedef enum Categoria{
	VAR_S, PROC, ROT, FUNC, PROG
}Categoria;


typedef enum Tipo{
	T_BOOL, T_INT, T_UNSET
}Tipo;




typedef struct Simbolo{
	Categoria categoria;
	Tipo tipo;
	char id[TAM_TOKEN];
	int nivel_lexico;
	int deslocamento;
	struct Simbolo *ant, *prox, *pai;

}Simbolo;


typedef struct Tab_simb{
	Simbolo *bottom, *top;
	int qtd_simbolos;

} Tab_simb;

//TRATAMENTO DE ERRO

typedef enum ErroT {

  /* Retorno 0 -> Nao ha erro (UNIX default) */
  SEM_ERRO=0,

  /* Erros Sintaticos */
  ERRO_SINTATICO=40, ERRO_SINT_IDENT_NAO_ENC=41, ERRO_TIPO=42,

  /* Alocacao mal sucedida */
  ERRO_ALOCACAO, ERRO_TAB_NAO_ALOC,

  /* Identificadores */
  ERRO_IDENT_JA_DEC, ERRO_SIMB_NAO_ENC,

  /* Lista de Parametros */
  ERRO_LISTA_PARAM_NAO_ALOC, ERRO_PARAM_NAO_ENC, ERRO_MAX_PARAM,
  
  /* PILHA */
  ERRO_PILHA_N_EXISTE, ERRO_PILHA_VAZIA, ERRO_PILHA_TAM_EXCED,

  /* WARNING */  
  WARN_IDENT_JA_DEC,

} ErroT;

int trataErro(ErroT, char*);

Tab_simb *iniciaTabelaSimbolo(Tab_simb *);

Simbolo *procuraSimbolo(Tab_simb *, char *, int);

Simbolo *insereSimbolo(Tab_simb *, char *, Categoria, int);

int removeSimboloTop(Tab_simb *);

int imprimeTabSimbolos(Tab_simb *);

