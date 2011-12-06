#include <wx/window.h>
#include <wx/sizer.h>
#include "RwxUtils.h"

extern "C" {
    SEXP R_wxWindow_SetAutoLayout(SEXP r_window, SEXP r_val);
    SEXP R_wxWindow_Fit(SEXP r_grid);
    SEXP R_wxWindow_GetId(SEXP r_window);
    SEXP R_wxWindow_GetSize(SEXP r_window);
    SEXP R_wxWindow_SetSize_int_int(SEXP r_window, SEXP r_width, SEXP r_height);
    SEXP R_wxWindow_SetSize_int_int_int_int_int(SEXP r_window, SEXP r_x, SEXP r_y, SEXP r_width, SEXP r_height, SEXP r_flags);
    SEXP R_wxWindow_SetSizerAndFit(SEXP r_window, SEXP r_sizer, SEXP r_deleteOld);
    SEXP R_wxWindow_SetSizer(SEXP r_window, SEXP r_sizer, SEXP r_deleteOld);
    SEXP R_wxWindow_SetFont(SEXP r_window, SEXP r_font);
    SEXP R_wxWindow_SetToolTip(SEXP r_window, SEXP r_text);
    SEXP R_wxWindow_FindWindow(SEXP r_window, SEXP r_id);
    SEXP R_wxWindow_FindWindowByName(SEXP r_name, SEXP r_parent);
    SEXP R_wxWindow_FindWindowByLabel(SEXP r_label, SEXP r_parent);
    SEXP R_wxWindow_FindWindowById(SEXP r_id, SEXP r_parent);

    SEXP R_wxWindow_GetChildren(SEXP r_window);
    SEXP R_wxWindow_Destroy(SEXP r_window);

    SEXP R_wxWindow_SetBackgroundColour(SEXP r_window, SEXP r_color);
    SEXP R_wxWindow_Refresh(SEXP r_window, SEXP r_eraseBackground, SEXP r_rect);
}

SEXP 
R_wxWindow_GetChildren(SEXP r_window)
{
    DECLARE_RWX_REF(window, wxWindow);
    wxWindowList ans;
    ans = window->GetChildren();

    SEXP r_ans;
    int n = ans.GetCount();

    PROTECT(r_ans = NEW_LIST(n));
    for(int i = 0; i < n ; i++) {
        wxWindow *el = ans.Item(i)->GetData();
        SET_VECTOR_ELT(r_ans, i, R_make_wxWidget_Ref(el, "wxWindow", true));
    }
    UNPROTECT(1);
    return(r_ans);
}

SEXP
R_wxWindow_SetSize_int_int(SEXP r_window, SEXP r_width, SEXP r_height)
{
  DECLARE_RWX_REF(window, wxWindow);
  int width, height;
  SEXP r_ans = R_NilValue;

  width = INTEGER(r_width)[0];
  height = INTEGER(r_height)[0];
  window->SetSize(width, height);

  return(r_ans);
}


extern "C"
SEXP 
R_wxWindow_Raise(SEXP r_window)
{
  DECLARE_RWX_REF(window, wxWindow);
  window->Raise();
  return(R_NilValue);
}

SEXP 
R_wxWindow_GetId(SEXP r_window)
{
  DECLARE_RWX_REF(window, wxWindow);
  int ans;
  ans = window->GetId();
  return(ScalarInteger(ans));
}


SEXP 
R_wxWindow_GetSize(SEXP r_window)
{
  DECLARE_RWX_REF(window, wxWindow);
  SEXP r_ans;
  int w, h;
  
  window->GetSize(&w, &h);
  r_ans = NEW_INTEGER(2);
  INTEGER(r_ans)[0] = w;
  INTEGER(r_ans)[1] = h;
  return(r_ans);
}


extern "C"
SEXP 
R_wxWindow_GetSizer(SEXP r_window)
{
  DECLARE_RWX_REF(window, wxWindow);
  SEXP r_ans;
  
  wxSizer *ans = window->GetSizer();
  return(R_make_wxWidget_Ref(ans, "wxSizer", true)); //XXX dynamic class
}


SEXP
R_wxWindow_SetSize_int_int_int_int_int(SEXP r_window, SEXP r_x, SEXP r_y, SEXP r_width, SEXP r_height, SEXP r_flags)
{
  DECLARE_RWX_REF(window, wxWindow);
  int width, height, x, y;
  int flags = wxSIZE_AUTO;

  SEXP r_ans = R_NilValue;

  x = INTEGER(r_x)[0];
  y = INTEGER(r_y)[0];
  width = INTEGER(r_width)[0];
  height = INTEGER(r_height)[0];
  if(GET_LENGTH(r_flags))
      flags = INTEGER(r_flags)[0];

  window->SetSize(x, y, width, height, flags);

  return(r_ans);
}


SEXP 
R_wxWindow_SetAutoLayout(SEXP r_window, SEXP r_val)
{
    bool val = LOGICAL(r_val)[0];
    wxWindow *window = GET_RWX_REF(r_window, wxWindow);
    window->SetAutoLayout(val);
    return(R_NilValue);
}

SEXP 
R_wxWindow_SetSizer(SEXP r_window, SEXP r_sizer, SEXP r_deleteOld)
{
    DECLARE_RWX_REF(window, wxWindow);
    DECLARE_RWX_REF(sizer, wxSizer);
    bool deleteOld = LOGICAL(r_deleteOld)[0];
    window->SetSizer(sizer, deleteOld);
    return(R_NilValue);
}

SEXP 
R_wxWindow_SetSizerAndFit(SEXP r_window, SEXP r_sizer, SEXP r_deleteOld)
{
    DECLARE_RWX_REF(window, wxWindow);
    DECLARE_RWX_REF(sizer, wxSizer);
    bool deleteOld = LOGICAL(r_deleteOld)[0];
    window->SetSizerAndFit(sizer, deleteOld);
    return(R_NilValue);
}



SEXP
R_wxWindow_Fit(SEXP r_window)
{
 wxWindow *window = (wxWindow *) R_get_wxWidget_Ref(r_window, "wxWindow");
 window->Fit();

 return(R_NilValue);
}

SEXP
R_wxWindow_SetFont(SEXP r_window, SEXP r_font)
{
 DECLARE_RWX_REF(window, wxWindow);
 DECLARE_RWX_REF(font, wxFont);

 window->SetFont(*font);

 return(R_NilValue);
}


SEXP 
R_wxWindow_SetToolTip_wxString(SEXP r_window, SEXP r_text)
{
 wxWindow *window = (wxWindow *) R_get_wxWidget_Ref(r_window, "wxWindow");
 wxString value = wxString(CHAR(STRING_ELT(r_text, 0)), wxConvUTF8);
 window->SetToolTip(value);
 
 return(R_NilValue);
}

SEXP
R_wxWindow_Destroy(SEXP r_window)
{
    wxWindow *window = (wxWindow *) R_get_wxWidget_Ref(r_window, "wxWindow");

    window->Destroy();
    return(R_NilValue);
}


SEXP
R_wxWindow_FindWindow(SEXP r_window, SEXP r_id)
{
    wxWindow *window = (wxWindow *) R_get_wxWidget_Ref(r_window, "wxWindow");
    long id = (long) REAL(r_id)[0];
    wxWindow *ans;
    SEXP r_ans;

    ans = window->FindWindow(id);

    r_ans = R_make_wxWidget_Ref(ans, "wxWindow");/* Dynamically determine the class of this. */

    return(r_ans);
}



SEXP
R_wxWindow_FindWindowByName(SEXP r_name, SEXP r_parent)
{
    wxString name;
    wxWindow *parent = NULL;
    wxWindow *ans;
    SEXP r_ans;

    name = R_to_wxString(r_name);
    ans = wxWindow::FindWindowByName(name, parent);

    r_ans = R_make_wxWidget_Ref(ans, "wxWindow");/* Dynamically determine the class of this. */

    return(r_ans);
}


SEXP
R_wxWindow_FindWindowByLabel(SEXP r_label, SEXP r_parent)
{
    wxString label;
    wxWindow *parent = NULL;
    wxWindow *ans;
    SEXP r_ans;

    label = R_to_wxString(r_label);
    ans = wxWindow::FindWindowByLabel(label, parent);

    r_ans = R_make_wxWidget_Ref(ans, "wxWindow");/* Dynamically determine the class of this. */

    return(r_ans);
}

SEXP
R_wxWindow_FindWindowById(SEXP r_id, SEXP r_parent)
{
    long id;
    wxWindow *parent = NULL;
    wxWindow *ans;
    SEXP r_ans;
//XXX need to check length is > 0
    id = (long) asReal(r_id);
    ans = wxWindow::FindWindowById(id, parent);

    r_ans = R_make_wxWidget_Ref(ans, "wxWindow");/* Dynamically determine the class of this. */

    return(r_ans);
}


extern "C"
SEXP
R_wxWindow_Reparent(SEXP r_window, SEXP r_parent)
{
    DECLARE_RWX_REF(window, wxWindow);
    DECLARE_RWX_REF(parent, wxWindow);
    bool ans;
    ans = window->Reparent(parent);
    return(ScalarLogical(ans));
}



#if wxUSE_DRAG_AND_DROP
extern "C"
SEXP
R_wxWindow_SetDropTarget(SEXP r_window, SEXP r_drop)
{
    DECLARE_RWX_REF(window, wxWindow);
    /*    DECLARE_RWX_REF(drop, wxDropTarget); */
    wxDropTarget *drop;
    drop = (wxDropTarget*) R_get_wxWidget_Ref(r_drop, NULL); /*XXX fixme - want the type. */
    
    window->SetDropTarget(drop);
    return(R_NilValue);
}
#endif


extern "C"
SEXP 
R_wxWindow_SetBackgroundColour(SEXP r_window, SEXP r_colour)
{
    DECLARE_RWX_REF(window, wxWindow);
    const wxColour *colour = wxRED;
    if(GET_LENGTH(r_colour))
        colour = (const wxColour *) R_get_wxWidget_Ref(r_colour, "wxColour");

    bool ans = window->SetBackgroundColour(*colour);

    return(ScalarLogical(ans));
}
 
SEXP 
R_wxWindow_Refresh(SEXP r_window, SEXP r_eraseBackground, SEXP r_rect)
{
    DECLARE_RWX_REF(window, wxWindow);
    bool eraseBackground = LOGICAL(r_eraseBackground)[0];
    wxRect *rect = NULL;

    window->Refresh(eraseBackground);

    return(R_NilValue);
}



extern "C"
SEXP
R_wxWindow_PopupMenu_wxMenu_int_int(SEXP r_window, SEXP r_menu, SEXP r_x, SEXP r_y)
{
    DECLARE_RWX_REF(window, wxWindow);
    DECLARE_RWX_REF(menu, wxMenu);
    int x = INTEGER(r_x)[0];
    int y = INTEGER(r_y)[0];

    bool ans = window->PopupMenu(menu, x, y);
    return(ScalarLogical(ans));
}


extern "C"
SEXP
R_wxWindow_Enable(SEXP r_window, SEXP r_enable)
{
    DECLARE_RWX_REF(window, wxWindow);
    bool enable = asLogical(r_enable);

    bool ans = window->Enable(enable);
    return(ScalarLogical(ans));
}
