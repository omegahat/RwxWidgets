#ifndef RWXUTILS_H
#define RWXUTILS_H


#include "RConverters.h"

#include "Rinternals.h"
#include "Rdefines.h"

#undef GetOption

wchar_t *to_wchar_t_from_R(SEXP);
SEXP wchar_t_ptr_to_R(const wchar_t *);

wxChar *RtowxChar(SEXP);
SEXP wxCharToR(const wxChar *);

SEXP R_copy_wxString_to_R(const wxString *str);

SEXP R_vector_to_long_int_array(SEXP vals);

bool *R_integer_to_bool_array(SEXP);

#endif
