




typedef enum Categoria{
	VAR_SIMP, PROC, ROT
}Categoria;


typedef enum Tipo{
	T_BOOLEAN, T_INTEGER
}Tipo;


typedef struct Elemento{
	Categoria categoria;
	Tipo tipo;
	char id[TAM_TOKEN];
	int nivel_lexico;

}Elemento;


typedef struct{
	Elemento *ts_elemento;
	int top, bottom;

} Tab_simb;






