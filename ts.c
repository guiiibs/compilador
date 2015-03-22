#include <stdio.h>
#include <stdlib.h>

#define BOOLEAN 0
#define INTEGER 1
#define MAX_TAM 32

typedef struct{
	int tipo;
	char identificador[MAX_TAM];
} Entrada_ts;


typedef struct{
	Entrada_ts *ts_elemento;
	int top;

} Tab_simb;




int main (int argc, char** argv) {


	return 0;
}
