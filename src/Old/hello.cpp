#include <wx/wx.h>
#include <Rdefines.h>

extern "C" {

  SEXP Rwx_createFrame(SEXP title, SEXP coords);
  SEXP Rwx_Show(SEXP ref);
  SEXP Rwx_SetTopWindow(SEXP ref);

  SEXP Rwx_init(SEXP args);
}


SEXP 
Rwx_createFrame(SEXP title, SEXP coords)
{
 wxFrame *frame;
 wxPoint pos = wxPoint(INTEGER(coords)[0], INTEGER(coords)[1]);
 wxSize size = wxSize(INTEGER(coords)[2], INTEGER(coords)[3]);

 frame = new wxFrame(NULL, -1, CHAR(STRING_ELT(title, 0)), pos, size);

 return(R_make_wxWidget_Ref(frame, "wxFrame"));
}

SEXP
Rwx_SetTopWindow(SEXP ref)
{

  wxWindow *w;
  w = (wxWindow *) R_get_wxWidget_Ref(ref, NULL);
  SetTopWindow(w);

  return(R_NilValue);
}


SEXP
Rwx_Show(SEXP ref)
{

  wxWidget *w;
  w = R_get_wxWidget_Ref(ref, NULL);
  w->Show(TRUE);

  return(R_NilValue);
}
