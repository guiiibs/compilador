#define TAM_LISTA_PARAM 150

/* VAR_S = variavel simples
	 PROC = procedimento
	 ROT = rotulo
	 FUNC = funcao
	 PROG = nome do programa
	 PF = parametro formal
*/
typedef enum Categoria{
	VAR_S, PROC, ROT, FUNC, PROG, PF
}Categoria;


typedef enum Tipo{
	T_BOOL, T_INT, T_UNSET
}Tipo;


typedef enum Passagem {
  REF =1, VALOR=2
}Passagem;

typedef struct Parametro {
  Tipo tipo;
  Passagem passagem;
}Parametro;

typedef struct Simbolo{
	Categoria categoria;
	Tipo tipo;
	char id[TAM_TOKEN];
	int nivel_lexico;
	struct Simbolo *ant, *prox, *pai;
	 
	union {
    	Passagem passagem;
    	struct {
      	int qtd_parametros;
      	char *rotulo;
      	Parametro *lista_param;
      	};
    };

    union {
    	int deslocamento;
    	int end_retorno;
  	};

}Simbolo;


typedef struct Tab_simb{
	Simbolo *bottom, *top;
	int qtd_simbolos;

} Tab_simb;

Tab_simb *iniciaTabelaSimbolo(Tab_simb *);

Simbolo *procuraSimbolo(Tab_simb *, char *, int );

Simbolo *retornaSimbolo(Tab_simb *, char *, int );

Simbolo *insereSimbolo(Tab_simb *, char *, Categoria, int);

int removeSimboloTop(Tab_simb *);

int imprimeTabSimbolos(Tab_simb *);

int insereTipo(Tab_simb *, Tipo);

int removeFPSimbolos(Tab_simb *, Simbolo *);

int inserePassageParam(Tab_simb *, Passagem, int);

int setaDeslocamentoParam(Tab_simb *, int);

int insereParamLista(Simbolo  *, Tipo , Passagem , int );

