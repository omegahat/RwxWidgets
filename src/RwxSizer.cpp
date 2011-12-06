#include <wx/sizer.h>
#include <wx/gbsizer.h>
#include "RwxUtils.h"
#include "RwxConverters.h"

extern "C" {
  SEXP R_wxGridSizer_new(SEXP r_rows, SEXP r_cols, SEXP r_vgap, SEXP r_hgap);
  SEXP R_wxFlexGridSizer_new(SEXP r_rows, SEXP r_cols, SEXP r_vgap, SEXP r_hgap);
  SEXP R_wxGridBagSizer_new(SEXP r_vgap, SEXP r_hgap);

  SEXP R_wxSizer_Fit(SEXP r_window, SEXP r_target);
  SEXP R_wxSizer_Add(SEXP r_sizer, SEXP r_window, SEXP r_flags);

  SEXP R_wxSizer_Add_wxSizer_wxSizerFlags(SEXP r_sizer, SEXP r_window, SEXP r_flags);
  SEXP R_wxSizer_Add_wxWindow_wxSizerFlags(SEXP r_sizer, SEXP r_window, SEXP r_flags);
  SEXP R_wxSizer_Add(SEXP r_sizer, SEXP r_window, SEXP r_flags);
  SEXP R_wxSizer_Add_wxSizer_int_int_int(SEXP r_This, SEXP r_sizer,  SEXP r_proportion, SEXP r_flag, SEXP r_border);
  SEXP R_wxSizer_Add_int_int_int_int_int(SEXP r_This, SEXP r_width, SEXP r_height, SEXP r_proportion, SEXP r_flag, SEXP r_border);

  SEXP R_wxSizer_SetSizeHints(SEXP r_window, SEXP r_parent);
  SEXP R_wxSizer_AddStretchSpacer(SEXP r_window, SEXP r_prop);
  SEXP R_wxSizer_AddSpacer(SEXP r_window, SEXP r_prop);
}


SEXP
R_wxSizer_SetSizeHints(SEXP r_sizer, SEXP r_window)
{
  DECLARE_RWX_REF(sizer, wxSizer);
  DECLARE_RWX_REF(window, wxWindow);

  sizer->SetSizeHints(window);

  return(R_NilValue);
}





SEXP
R_wxGridSizer_new(SEXP r_rows, SEXP r_cols, SEXP r_vgap, SEXP r_hgap)
{
  wxGridSizer *sizer;
  int hgap;
  int vgap;
  SEXP r_ans;
  int rows, cols;

  hgap = INTEGER(r_hgap)[0];
  vgap = INTEGER(r_vgap)[0];

  cols = INTEGER(r_cols)[0];
  

  if(Rf_length(r_cols) == 0)
    sizer = new wxGridSizer(cols, vgap, hgap);
  else {
    rows = INTEGER(r_rows)[0];
    sizer = new wxGridSizer(rows, cols, vgap, hgap);
  }

  r_ans = R_make_wxWidget_Ref(sizer, "wxGridSizer");
  return(r_ans);
}


SEXP
R_wxFlexGridSizer_new(SEXP r_rows, SEXP r_cols, SEXP r_vgap, SEXP r_hgap)
{
  wxFlexGridSizer *sizer;
  int hgap;
  int vgap;
  SEXP r_ans;
  int rows, cols;

  hgap = INTEGER(r_hgap)[0];
  vgap = INTEGER(r_vgap)[0];

  cols = INTEGER(r_cols)[0];
  

  if(Rf_length(r_cols) == 0)
    sizer = new wxFlexGridSizer(cols, vgap, hgap);
  else {
    rows = INTEGER(r_rows)[0];
    sizer = new wxFlexGridSizer(rows, cols, vgap, hgap);
  }

  r_ans = R_make_wxWidget_Ref(sizer, "wxFlexGridSizer");
  return(r_ans);
}

extern "C"
SEXP
R_wxFlexGridSizer_AddGrowableRow(SEXP r_sizer, SEXP r_idx, SEXP r_proportion)
{
    DECLARE_RWX_REF(sizer, wxFlexGridSizer);
    size_t idx = (size_t) REAL(r_idx)[0];
    int proportion = asInteger(r_proportion);

    sizer->AddGrowableRow(idx, proportion);
    return(R_NilValue);
}

extern "C"
SEXP
R_wxFlexGridSizer_AddGrowableCol(SEXP r_sizer, SEXP r_idx, SEXP r_proportion)
{
    DECLARE_RWX_REF(sizer, wxFlexGridSizer);
    size_t idx = (size_t) REAL(r_idx)[0];
    int proportion = asInteger(r_proportion);

    sizer->AddGrowableCol(idx, proportion);
    return(R_NilValue);
}


SEXP
R_wxGridBagSizer_new(SEXP r_vgap, SEXP r_hgap)
{
  wxGridBagSizer *sizer;
  int hgap;
  int vgap;
  SEXP r_ans;

  hgap = INTEGER(r_hgap)[0];
  vgap = INTEGER(r_vgap)[0];

  sizer = new wxGridBagSizer(vgap, hgap);
  r_ans = R_make_wxWidget_Ref(sizer, "wxGridBagSizer");
  return(r_ans);
}



SEXP
R_wxSizer_Add(SEXP r_sizer, SEXP r_window, SEXP r_flags)
{
  wxSizer *sizer;
  wxWindow *window;
  int flags = wxALL | wxEXPAND;

  sizer = (wxSizer *) R_get_wxWidget_Ref(r_sizer, "wxSizer");
  window = (wxWindow *) R_get_wxWidget_Ref(r_window, "wxWindow");
  flags = asInteger(r_flags);

  sizer->Add(window, 1, flags);

  return(R_NilValue);
}

SEXP
R_wxSizer_Add_wxWindow_wxSizerFlags(SEXP r_sizer, SEXP r_window, SEXP r_flags)
{
  wxSizer *sizer;
  wxWindow *window;
  int flags = wxALL | wxEXPAND;

  sizer = (wxSizer *) R_get_wxWidget_Ref(r_sizer, "wxSizer");
  window = (wxWindow *) R_get_wxWidget_Ref(r_window, "wxWindow");
  flags = asInteger(r_flags);

  sizer->Add(window, 1, flags);

  return(R_NilValue);
}



SEXP
R_wxSizer_Add_wxSizer_wxSizerFlags(SEXP r_sizer, SEXP r_window, SEXP r_flags)
{
  wxSizer *sizer;
  wxSizer *window;
  int flags = wxALL | wxEXPAND;

  sizer = (wxSizer *) R_get_wxWidget_Ref(r_sizer, "wxSizer");
  window = (wxSizer *) R_get_wxWidget_Ref(r_window, "wxWindow");
  flags = asInteger(r_flags);

  sizer->Add(window, 1, flags);

  return(R_NilValue);
}


SEXP
R_wxSizer_Add_wxSizer_int_int_int(SEXP r_This, SEXP r_sizer,  SEXP r_proportion, SEXP r_flag, SEXP r_border)
{
    DECLARE_RWX_REF(This, wxSizer);
    DECLARE_RWX_REF(sizer, wxSizer);
    wxSizerItem *ans;
    SEXP r_ans = R_NilValue;
    int proportion, flag, border;

    flag = INTEGER(r_flag)[0];
    proportion = INTEGER(r_proportion)[0];
    border = INTEGER(r_border)[0];

    ans = This->Add(sizer, proportion, flag, border);

    r_ans = R_make_wxWidget_Ref(ans, "wxSizerItem");    

    return(r_ans);
}

SEXP
R_wxSizer_Add_int_int_int_int_int(SEXP r_This, SEXP r_width, SEXP r_height, SEXP r_proportion, SEXP r_flag, SEXP r_border)
{
    DECLARE_RWX_REF(This, wxSizer);
    SEXP r_ans = R_NilValue;
    wxSizerItem *ans;
    int width, height, proportion, flag, border;

    width = INTEGER(r_width)[0];
    height = INTEGER(r_height)[0];
    flag = INTEGER(r_flag)[0];
    proportion = INTEGER(r_proportion)[0];
    border = INTEGER(r_border)[0];

    ans = This->Add(width, height, proportion, flag, border);

    r_ans = R_make_wxWidget_Ref(ans, "wxSizerItem");    

    return(r_ans);
}



SEXP
R_wxSizer_Fit(SEXP r_window, SEXP r_target)
{
    wxSizer *sizer = GET_RWX_REF(r_window, wxSizer);
    wxWindow *target = (wxWindow *) R_get_wxWidget_Ref(r_target, "wxWindow");
    wxSize ans;
    SEXP r_ans;

    ans = sizer->Fit(target);
    r_ans = convert_wxSize_to_R(ans);
 
    return(r_ans);
}



SEXP 
R_wxSizer_AddStretchSpacer(SEXP r_window, SEXP r_prop)
{
    wxSizer *sizer = GET_RWX_REF(r_window, wxSizer);
    wxSizerItem *ans;
    SEXP r_ans;
    ans = sizer->AddStretchSpacer(INTEGER(r_prop)[0]);
    r_ans = R_make_wxWidget_Ref(ans, "wxSizerItem");
    return(r_ans);
}


SEXP 
R_wxSizer_AddSpacer(SEXP r_window, SEXP r_prop)
{
    wxSizer *sizer = GET_RWX_REF(r_window, wxSizer);
    wxSizerItem *ans;
    SEXP r_ans;
    ans = sizer->AddSpacer(INTEGER(r_prop)[0]);
    r_ans = R_make_wxWidget_Ref(ans, "wxSizerItem");
    return(r_ans);
}


extern "C"
SEXP
R_wxSizer_SetMinSize_int_int(SEXP r_sizer, SEXP r_x, SEXP r_y)
{

    DECLARE_RWX_REF(sizer, wxSizer);
    int x = INTEGER(r_x)[0];
    int y = INTEGER(r_y)[0];
    sizer->SetMinSize(x, y);
    return(R_NilValue);
}



extern "C"
SEXP
R_wxSizer_Show_wxWindow_bool_bool(SEXP r_sizer, SEXP r_window, SEXP r_show, SEXP r_recursive)
{

    DECLARE_RWX_REF(sizer, wxSizer);
    DECLARE_RWX_REF(window, wxWindow);
    bool show = LOGICAL(r_show)[0];
    bool recursive = LOGICAL(r_recursive)[0];

    bool ans = sizer->Show(window, show, recursive);
    return(ScalarLogical(ans));
}


extern "C"
SEXP
R_wxSizer_Show_wxSizer_bool_bool(SEXP r_This, SEXP r_sizer, SEXP r_show, SEXP r_recursive)
{
    DECLARE_RWX_REF(This, wxSizer);
    DECLARE_RWX_REF(sizer, wxSizer);
    bool show = LOGICAL(r_show)[0];
    bool recursive = LOGICAL(r_recursive)[0];

    bool ans = This->Show(sizer, show, recursive);

    return(ScalarLogical(ans));
}

extern "C"
SEXP
R_wxSizer_Show_size_t_bool(SEXP r_This, SEXP r_index, SEXP r_show)
{
    DECLARE_RWX_REF(This, wxSizer);
    size_t index = (size_t) REAL(r_index)[0];
    bool show = LOGICAL(r_show)[0];

    bool ans = This->Show(index, show);

    return(ScalarLogical(ans));
}


extern "C"
SEXP
R_wxSizer_Layout(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxSizer);
    
    This->Layout();

    return(R_NilValue);
}

extern "C"
SEXP
R_wxSizer_GetChildren(SEXP r_This)
{
    DECLARE_RWX_REF(This, wxSizer);

    wxSizerItemList ans = This->GetChildren();
    int n = ans.GetCount();
    SEXP r_ans;
    PROTECT(r_ans = NEW_LIST(n));
    for(int i = 0; i < n; i++) {
        wxSizerItem *tmp = ans.Item(i)->GetData();
        SET_VECTOR_ELT(r_ans, i, R_make_wxWidget_Ref(tmp, "wxSizerItem"));
    }
    UNPROTECT(1);
    return(r_ans);
}


extern "C"
SEXP
R_wxSizer_GetContainingWindow(SEXP r_This)
{
#if wxMINOR_VERSION > 6
    DECLARE_RWX_REF(This, wxSizer);
    wxWindow *ans = NULL;
    ans = This->GetContainingWindow();

    return(R_make_wxWidget_Ref(ans, "wxWindow"));
#else
    PROBLEM  "not supported in this version of wxWidgets"
        ERROR;
    return(R_NilValue);
#endif
}


extern "C"
SEXP
R_wxSizer_Remove_wxSizer(SEXP r_This, SEXP r_sizer)
{
    DECLARE_RWX_REF(This, wxSizer);
    DECLARE_RWX_REF(sizer, wxSizer);
    
    bool ans = This->Remove(sizer);

    return(ScalarLogical(ans));
}


extern "C"
SEXP
R_wxSizer_Remove_wxWindow(SEXP r_This, SEXP r_window)
{
    DECLARE_RWX_REF(This, wxSizer);
    DECLARE_RWX_REF(window, wxWindow);
    
    bool ans = This->Remove(window);

    return(ScalarLogical(ans));
}


extern "C"
SEXP 
R_wxSizer_Insert_size_t_wxWindow_wxSizerFlags(SEXP r_sizer, SEXP r_index, SEXP r_window, SEXP r_flags)
{
    DECLARE_RWX_REF(sizer, wxSizer);

    DECLARE_RWX_REF(window, wxWindow);
    size_t index = (size_t) REAL(r_index)[0];
    wxSizerFlags flags = (wxSizerFlags) INTEGER(r_flags)[0];

    wxSizerItem *ans;

    ans = sizer->Insert(index, window, flags);

    return(R_make_wxWidget_Ref(ans, "wxSizerItem"));
}

extern "C"
SEXP 
R_wxSizer_Insert_size_t_wxWindow_int_int_int(SEXP r_sizer, SEXP r_index, SEXP r_window, 
                                             SEXP r_proportion, SEXP r_flag, SEXP r_border)
{
    DECLARE_RWX_REF(sizer, wxSizer);
    DECLARE_RWX_REF(window, wxWindow);
    size_t index = (size_t) REAL(r_index)[0];
    int flag = INTEGER(r_flag)[0];
    int proportion = INTEGER(r_proportion)[0];
    int border = INTEGER(r_border)[0];
    wxSizerItem *ans;

    ans = sizer->Insert(index, window, proportion, flag, border);

    return(R_make_wxWidget_Ref(ans, "wxSizerItem"));
}

extern "C"
SEXP 
R_wxSizer_Insert_size_t_wxSizer_wxSizerFlags(SEXP r_sizer, SEXP r_index, SEXP r_item, SEXP r_flags)
{
    DECLARE_RWX_REF(sizer, wxSizer);

    DECLARE_RWX_REF(item, wxSizer);
    size_t index = (size_t) REAL(r_index)[0];
    wxSizerFlags flags = (wxSizerFlags) INTEGER(r_flags)[0];

    wxSizerItem *ans;

    ans = sizer->Insert(index, item, flags);

    return(R_make_wxWidget_Ref(ans, "wxSizerItem"));
}


extern "C"
SEXP 
R_wxSizer_Insert_size_t_wxSizer_int_int_int(SEXP r_sizer, SEXP r_index, SEXP r_item, 
                                             SEXP r_proportion, SEXP r_flag, SEXP r_border)
{
    DECLARE_RWX_REF(sizer, wxSizer);
    DECLARE_RWX_REF(item, wxSizer);
    size_t index = (size_t) REAL(r_index)[0];
    int flag = INTEGER(r_flag)[0];
    int proportion = INTEGER(r_proportion)[0];
    int border = INTEGER(r_border)[0];
    wxSizerItem *ans;

    ans = sizer->Insert(index, item, proportion, flag, border);

    return(R_make_wxWidget_Ref(ans, "wxSizerItem"));
}

extern "C"
SEXP 
R_wxSizer_Insert_size_t_int_int_int_int_int(SEXP r_sizer, SEXP r_index, SEXP r_width, SEXP r_height, 
                                             SEXP r_proportion, SEXP r_flag, SEXP r_border)
{
    DECLARE_RWX_REF(sizer, wxSizer);
    size_t index = (size_t) REAL(r_index)[0];
    int width = INTEGER(r_width)[0];
    int height = INTEGER(r_width)[0];
    int flag = INTEGER(r_flag)[0];
    int proportion = INTEGER(r_proportion)[0];
    int border = INTEGER(r_border)[0];
    wxSizerItem *ans;

    ans = sizer->Insert(index, width, height, proportion, flag, border);

    return(R_make_wxWidget_Ref(ans, "wxSizerItem"));
}





extern "C"
SEXP
R_wxGridBagSizer_Add_wxWindow_wxGBPosition_wxGBSpan_int_int_wxObject(
    SEXP r_sizer, SEXP r_window, SEXP r_pos, SEXP r_span, SEXP r_flag, SEXP r_border)
{
    DECLARE_RWX_REF(sizer, wxGridBagSizer);
    DECLARE_RWX_REF(window, wxWindow);
    DECLARE_RWX_REF(pos, wxGBPosition);
    const wxGBSpan *span = &wxDefaultSpan;

    int flag = asInteger(r_flag);
    int border = asInteger(r_border);

    if(GET_LENGTH(r_span))
        span = (wxGBSpan *) R_get_wxWidget_Ref(r_span, "wxGBSpan");
    wxSizerItem *ans = sizer->Add(window, *pos, *span, flag, border);

    return(R_make_wxWidget_Ref(ans, "wxSizerItem"));
}


extern "C"
SEXP
R_wxGridBagSizer_Add_wxSizer_wxGBPosition_wxGBSpan_int_int_wxObject(
    SEXP r_sizer, SEXP r_window, SEXP r_pos, SEXP r_span, SEXP r_flag, SEXP r_border)
{
    DECLARE_RWX_REF(sizer, wxGridBagSizer);
    DECLARE_RWX_REF(window, wxSizer);
    DECLARE_RWX_REF(pos, wxGBPosition);
    const wxGBSpan *span = &wxDefaultSpan;

    int flag = asInteger(r_flag);
    int border = asInteger(r_border);

    if(GET_LENGTH(r_span))
        span = (wxGBSpan *) R_get_wxWidget_Ref(r_span, "wxGBSpan");
    wxSizerItem *ans = sizer->Add(window, *pos, *span, flag, border);

    return(R_make_wxWidget_Ref(ans, "wxSizerItem"));
}

extern "C"
SEXP
R_wxGridBagSizer_Add_int_int_wxGBPosition_wxGBSpan_int_int_wxObject(
    SEXP r_sizer, SEXP r_width, SEXP r_height, SEXP r_pos, SEXP r_span, SEXP r_flag, SEXP r_border)
{
    DECLARE_RWX_REF(sizer, wxGridBagSizer);
    int width = asInteger(r_width);
    int height = asInteger(r_height);    
    DECLARE_RWX_REF(pos, wxGBPosition);
    const wxGBSpan *span = &wxDefaultSpan;

    int flag = asInteger(r_flag);
    int border = asInteger(r_border);

    if(GET_LENGTH(r_span))
        span = (wxGBSpan *) R_get_wxWidget_Ref(r_span, "wxGBSpan");
    wxSizerItem *ans = sizer->Add(width, height, *pos, *span, flag, border);

    return(R_make_wxWidget_Ref(ans, "wxSizerItem"));
}

