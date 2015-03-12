
%{
#include <stdio.h>
%}

%token IDENT MAIS MENOS OR ASTERISCO DIV ABRE_PARENTESES FECHA_PARENTESES
%token AND IDENT_B

%%
expressao  : expr | logic1
;

expr       : expr MAIS termo {printf ("+"); } |
             expr MENOS termo {printf ("-"); } |
             termo
;

termo      : termo ASTERISCO fator  {printf ("*"); }| 
             termo DIV fator  {printf ("/"); }|
             fator
;

fator      : IDENT {printf ("A"); }
;

logic1	   : logic1 AND logic2 {printf (" and"); }|
			 logic1 OR logic2 {printf (" or"); }|
			 logic2
;

logic2     : IDENT_B {printf ("B"); }
;

%%

main (int argc, char** argv) {
   yyparse();
   printf("\n");
}

