#include <wx/html/htmlcell.h>

#include "RwxUtils.h"

extern "C" {
  SEXP R_wxHtmlContainerCell_InsertCell(SEXP r_this, SEXP r_cell);
}

SEXP
R_wxHtmlContainerCell_InsertCell(SEXP r_this, SEXP r_cell)
{
  wxHtmlContainerCell *This = GET_RWX_REF(r_this, wxHtmlContainerCell);
  wxHtmlCell *cell = GET_RWX_REF(r_cell, wxHtmlCell);

  This->InsertCell(cell);

  return(R_NilValue);
}


