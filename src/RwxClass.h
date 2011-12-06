#include "Rdefines.h"
#include "Rinternals.h"

class R_wxClass 
{
  protected:
     SEXP invoke(SEXP fun, SEXP arg1, SEXP arg2, SEXP arg3);
     SEXP invoke(SEXP fun, SEXP arg1, SEXP arg2);
     SEXP invoke(SEXP fun, SEXP arg1);

};

