




typedef enum Categoria{
	VAR_SIMP, PROC, ROT, FUNC
}Categoria;


typedef enum Tipo{
	T_BOOLEAN, T_INTEGER
}Tipo;


typedef struct Simbolo{
	Categoria categoria;
	Tipo tipo;
	char id[TAM_TOKEN];
	int nivel_lexico;
	int deslocamento;

}Simbolo;


typedef struct{
	Simbolo *ts_elemento;
	int top, bottom;

} Tab_simb;







