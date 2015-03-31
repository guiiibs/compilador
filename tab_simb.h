
typedef enum Categoria{
	VAR_SIMP, PROC, ROT, FUNC
}Categoria;


typedef enum Tipo{
	BOOLEAN, INTEGER, UNSET
}Tipo;


typedef struct Simbolo{
	Categoria categoria;
	Tipo tipo;
	char id[TAM_TOKEN];
	int nivel_lexico;
	int deslocamento;
	struct SimboloT *ant, *prox, *pai;

}Simbolo;


typedef struct Tab_simb{
	Simbolo *bottom, *top;
	int qtd_simbolos;

} Tab_simb;







