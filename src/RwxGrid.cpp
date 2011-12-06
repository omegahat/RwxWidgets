#include <wx/grid.h>
#include <Rinternals.h>

#include "RwxUtils.h"

extern "C" {
    SEXP R_wxGrid_new(SEXP r_frame,
             SEXP r_id,
             SEXP r_position,
             SEXP r_size,
             SEXP r_style, 
             SEXP r_name);
    SEXP R_wxGrid_CreateGrid(SEXP r_grid, SEXP r_numRows, SEXP r_numCols);
    SEXP R_wxGrid_GetNumberRows(SEXP r_grid);
    SEXP R_wxGrid_GetNumberCols(SEXP r_grid);
    SEXP R_wxGrid_SetRowLabelValue(SEXP r_grid, SEXP r_row, SEXP r_value);
    SEXP R_wxGrid_SetColLabelValue(SEXP r_grid, SEXP r_col, SEXP r_value);
    SEXP R_wxGrid_SetCellValue(SEXP r_grid, SEXP r_row, SEXP r_col, SEXP r_value);
    SEXP R_wxGrid_SetCellTextColour(SEXP r_grid, SEXP r_row, SEXP r_col, SEXP r_colour);
    SEXP R_wxGrid_SetRowlLabelSize(SEXP r_grid, SEXP r_size);
    SEXP R_wxGrid_SetColLabelSize(SEXP r_grid, SEXP r_size);
    SEXP R_wxGrid_SetColLabelAlignment(SEXP r_grid, SEXP r_horiz, SEXP r_vert);
    SEXP R_wxGrid_SetRowLabelAlignment(SEXP r_grid, SEXP r_horiz, SEXP r_vert);

    SEXP R_wxGrid_AppendRows(SEXP r_grid, SEXP r_cols);
    SEXP R_wxGrid_AppendCols(SEXP r_grid, SEXP r_cols);
}


SEXP
R_wxGrid_new(SEXP r_frame,
             SEXP r_id,
             SEXP r_position,
             SEXP r_size,
             SEXP r_style, 
             SEXP r_name)
{
  wxWindow *frame;
  wxWindowID id  = wxID_ANY;
  wxGrid *grid;
  wxPoint pos = wxPoint(INTEGER(r_position)[0], INTEGER(r_position)[1]);
  wxSize size = R_to_wxSize(r_size);

  frame = (wxWindow *) R_get_wxWidget_Ref(r_frame, "wxWindow");
  grid = new wxGrid(frame, id, pos, size);


  return(R_make_wxWidget_Ref(grid, "wxGrid"));
}

SEXP
R_wxGrid_CreateGrid(SEXP r_grid, SEXP r_numRows, SEXP r_numCols)
{
 wxGrid *grid = (wxGrid *) R_get_wxWidget_Ref(r_grid, "wxWindow");
 bool status;
 status = grid->CreateGrid(INTEGER(r_numRows)[0], INTEGER(r_numCols)[0]);

 return(Rf_ScalarLogical(status));
}


SEXP
R_wxGrid_GetNumberRows(SEXP r_grid)
{
 wxGrid *grid = (wxGrid *) R_get_wxWidget_Ref(r_grid, "wxWindow");
 return(Rf_ScalarInteger(grid->GetNumberRows()));
}

SEXP
R_wxGrid_GetNumberCols(SEXP r_grid)
{
 wxGrid *grid = (wxGrid *) R_get_wxWidget_Ref(r_grid, "wxWindow");
 return(Rf_ScalarInteger(grid->GetNumberCols()));
}

/*
SEXP
R_wxGridTable_IsEmptyCell(SEXP r_grid, SEXP r_row, SEXP r_col)
{
 wxGrid *grid = (wxGrid *) R_get_wxWidget_Ref(r_grid, "wxWindow");
 int row;
 int col;
 bool ans;
 SEXP r_ans;
 
 row = INTEGER(r_row)[0];
 col = INTEGER(r_col)[0];

 ans = grid->IsEmptyCell(row, col)
 r_ans = Rf_ScalarLogical(ans);

 return(r_ans);
}
*/



SEXP
R_wxGrid_SetRowLabelValue(SEXP r_grid, SEXP r_row, SEXP r_value)
{
 wxGrid *grid = (wxGrid *) R_get_wxWidget_Ref(r_grid, "wxWindow");
 int row = INTEGER(r_row)[0];
 wxString value = wxString(CHAR(STRING_ELT(r_value, 0)), wxConvUTF8);
 
 grid->SetRowLabelValue(row, value);

 return(R_NilValue);
}


SEXP
R_wxGrid_SetColLabelValue(SEXP r_grid, SEXP r_col, SEXP r_value)
{
 wxGrid *grid = (wxGrid *) R_get_wxWidget_Ref(r_grid, "wxWindow");
 int col = INTEGER(r_col)[0];
 wxString value = wxString(CHAR(STRING_ELT(r_value, 0)), wxConvUTF8);
 
 grid->SetColLabelValue(col, value);

 return(R_NilValue);
}

SEXP
R_wxGrid_SetRowLabelAlignment(SEXP r_grid, SEXP r_horiz, SEXP r_vert)
{
 wxGrid *grid = (wxGrid *) R_get_wxWidget_Ref(r_grid, "wxWindow");
 int horiz = INTEGER(r_horiz)[0];
 int vert = INTEGER(r_vert)[0];
 
 grid->SetRowLabelAlignment(horiz, vert);

 return(R_NilValue);
}


SEXP
R_wxGrid_SetColLabelAlignment(SEXP r_grid, SEXP r_horiz, SEXP r_vert)
{
 wxGrid *grid = (wxGrid *) R_get_wxWidget_Ref(r_grid, "wxWindow");
 int horiz = INTEGER(r_horiz)[0];
 int vert = INTEGER(r_vert)[0];
 
 grid->SetColLabelAlignment(horiz, vert);

 return(R_NilValue);
}



SEXP
R_wxGrid_SetRowLabelSize(SEXP r_grid, SEXP r_size)
{
 wxGrid *grid = (wxGrid *) R_get_wxWidget_Ref(r_grid, "wxWindow");
 int size = INTEGER(r_size)[0];
 
 grid->SetRowLabelSize(size);

 return(R_NilValue);
}

SEXP
R_wxGrid_SetColLabelSize(SEXP r_grid, SEXP r_size)
{
 wxGrid *grid = (wxGrid *) R_get_wxWidget_Ref(r_grid, "wxWindow");
 int size = INTEGER(r_size)[0];
 
 grid->SetRowLabelSize(size);

 return(R_NilValue);
}




SEXP
R_wxGrid_SetCellValue(SEXP r_grid, SEXP r_row, SEXP r_col, SEXP r_value)
{
 wxGrid *grid = (wxGrid *) R_get_wxWidget_Ref(r_grid, "wxWindow");
 int row;
 int col;
 wxString s;

 row = INTEGER(r_row)[0];
 col = INTEGER(r_col)[0]; 
 s = wxString(CHAR(STRING_ELT(r_value, 0)), wxConvUTF8);

 grid->SetCellValue(row, col, s);

 return(R_NilValue);
}


SEXP
R_wxGrid_SetCellTextColour(SEXP r_grid, SEXP r_row, SEXP r_col, SEXP r_colour)
{
  wxGrid *grid = (wxGrid *) R_get_wxWidget_Ref(r_grid, "wxWindow");
  int row;
  int col;
  wxString s;
  wxColor *color;

  row = INTEGER(r_row)[0];
  col = INTEGER(r_col)[0];

  grid->SetCellTextColour(row, col, *color);

  return(R_NilValue);
}

SEXP
R_wxGrid_AutoSize(SEXP r_grid)
{
  wxGrid *grid = GET_RWX_REF(r_grid, wxGrid);

  grid->AutoSize();

  return(R_NilValue);
}


SEXP
R_wxGrid_AppendRows(SEXP r_grid, SEXP r_rows)
{
  wxGrid *grid = GET_RWX_REF(r_grid, wxGrid);
  int rows  = INTEGER(r_rows)[0];
  bool ans;
  SEXP r_ans;

  ans = grid->AppendRows(rows);
  r_ans = ScalarLogical(ans);
  return(r_ans);
}


SEXP
R_wxGrid_AppendCols(SEXP r_grid, SEXP r_cols)
{
  wxGrid *grid = GET_RWX_REF(r_grid, wxGrid);
  int cols  = INTEGER(r_cols)[0];
  bool ans;
  SEXP r_ans;

  ans = grid->AppendCols(cols);
  r_ans = ScalarLogical(ans);

  return(r_ans);
}



