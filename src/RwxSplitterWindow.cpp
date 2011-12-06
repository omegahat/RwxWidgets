#include <wx/wx.h>
#include <wx/splitter.h>

#include "RwxUtils.h"

extern "C" {
    SEXP R_wxSplitterWindow_new(SEXP r_parent, SEXP r_id, SEXP r_pos, SEXP r_size, SEXP r_style, SEXP r_name);
    SEXP R_wxSplitterWindow_SplitHorizontally(SEXP r_This, SEXP r_window1, SEXP r_windo2, SEXP r_sashPosition);
    SEXP R_wxSplitterWindow_SplitVertically(SEXP r_This, SEXP r_window1, SEXP r_windo2, SEXP r_sashPosition);
}

SEXP 
R_wxSplitterWindow_new(SEXP r_parent, SEXP r_id, SEXP r_pos, SEXP r_size, SEXP r_style, SEXP r_name)
{
    DECLARE_RWX_REF(parent, wxWindow);
    int id = INTEGER(r_id)[0];
    wxPoint pos = wxDefaultPosition;
    wxSize size = wxDefaultSize;
    long style = (long) REAL(r_style)[0];
    wxString name = R_to_wxString(r_name);
    wxSplitterWindow *ans;

    ans = new wxSplitterWindow(parent, id, pos, size, style, name);

    return(R_make_wxWidget_Ref(ans, "wxSplitterWindow"));
}

SEXP 
R_wxSplitterWindow_SplitHorizontally(SEXP r_This, SEXP r_window1, SEXP r_window2, SEXP r_sashPosition)
{
    DECLARE_RWX_REF(This, wxSplitterWindow);
    DECLARE_RWX_REF(window1, wxWindow);
    DECLARE_RWX_REF(window2, wxWindow);
    int sashPosition = INTEGER(r_sashPosition)[0];
    bool ans;
    ans = This->SplitHorizontally(window1, window2, sashPosition);
    return(ScalarLogical(ans));
}


SEXP 
R_wxSplitterWindow_SplitVertically(SEXP r_This, SEXP r_window1, SEXP r_window2, SEXP r_sashPosition)
{
    DECLARE_RWX_REF(This, wxSplitterWindow);
    DECLARE_RWX_REF(window1, wxWindow);
    DECLARE_RWX_REF(window2, wxWindow);
    int sashPosition = INTEGER(r_sashPosition)[0];
    bool ans;
    ans = This->SplitVertically(window1, window2, sashPosition);
    return(ScalarLogical(ans));
}


extern "C"
SEXP
wxSplitterWindow_SetSashPosition(SEXP r_sash, SEXP r_position, SEXP r_redraw)
{

    DECLARE_RWX_REF(sash, wxSplitterWindow);
    int position = asInteger(r_position);
    bool redraw = asLogical(r_redraw);;

    sash->SetSashPosition(position, redraw);
    return(R_NilValue);
}

