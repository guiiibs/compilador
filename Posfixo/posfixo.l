%{
#include "posfixo.tab.h"
%}

%%

[\n\t ]  

\+    { return MAIS; }
\-    { return MENOS; }
\*    { return ASTERISCO;  }
\/    { return DIV;  }
a     { return IDENT;   }
b	  { return IDENT_B; }
and   { return AND; }
or	  { return OR;  }


%%

