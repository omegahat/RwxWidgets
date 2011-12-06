#include "RwxUtils.h"

SEXP 
R_vector_to_long_int_array(SEXP vals)
{

    
}

typedef void * (*allocFun)(long, int);

bool *
R_integer_to_bool_array(SEXP src, allocFun f)
{
    bool *ans;
    int i, n;

    if(f == NULL)
	f = R_alloc;
    
    n = GET_LENGTH(src);
    ans = allocFun(n, sizeof(bool));
    for(i = 0 ; i < n ; i++)
	ans[i] = INTEGER(src)[i];
    return(ans);
}
