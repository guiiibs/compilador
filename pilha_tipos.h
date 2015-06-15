typedef enum OperacaoT {
  CALC, COMPAR, ATRIB,
} OperacaoT;

// int geraRotulo(char **, int *, PilhaT *);

int empilhaTipo(PilhaT *, Tipo);

int comparaTipo(PilhaT *, OperacaoT, Tipo);
