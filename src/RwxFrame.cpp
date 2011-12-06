#include <wx/wx.h>
#include "RwxUtils.h"
#undef length


extern "C" {
SEXP R_RwxFrame_new(SEXP r_title, SEXP r_pos, SEXP r_size,
                    SEXP r_id,
                    SEXP OnQuit);
SEXP R_wxWindow_Show(SEXP r_frame, SEXP r_show);

SEXP
R_wxFrame_CreateStatusBar(SEXP r_frame,
                           SEXP r_number,
                           SEXP r_style,
                           SEXP r_winid,
                           SEXP r_name);
SEXP R_wxFrame_SetStatusText(SEXP r_frame, SEXP r_text, SEXP r_number);
}



extern "C" 
SEXP
R_wxFrame_new(SEXP r_parent, SEXP r_id, SEXP r_title, SEXP r_pos, SEXP r_size, 
              SEXP r_style, SEXP r_name)
{
    DECLARE_RWX_REF(parent, wxWindow);
    wxWindowID id  = (wxWindowID) INTEGER(r_id)[0];
    wxPoint pos = wxDefaultPosition;
    wxSize size = wxDefaultSize;    
    long style = (long) REAL(r_style)[0];
    const wxString title = R_to_wxString(r_title);
    const wxString name = R_to_wxString(r_name);

    if(LENGTH(r_size))
        size = R_to_wxSize(r_size);
    if(LENGTH(r_pos))
        pos = R_to_wxPoint(r_pos);

    wxFrame *ans = new wxFrame(parent, id, title, pos, size, style, name);
    return(R_make_wxWidget_Ref(ans, "wxFrame"));

}


SEXP
R_RwxFrame_new(SEXP r_title, SEXP r_pos, SEXP r_size,
               SEXP r_id,
               SEXP OnQuit)
{

 wxWindowID id = (wxWindowID) INTEGER(r_id)[0];
 wxPoint point;
 wxSize size;
 long style = wxDEFAULT_FRAME_STYLE;
 wxFrame *frame;

 if(LENGTH(r_size))
     size = R_to_wxSize(r_size);
 if(LENGTH(r_pos))
     point = R_to_wxPoint(r_pos);

 frame = new wxFrame(NULL, id, wxString(CHAR(STRING_ELT(r_title, 0)), wxConvUTF8),
                      point, size, style /*, name */);

 return(R_make_wxWidget_Ref(frame, "wxFrame"));
}

SEXP
R_wxWindow_Show(SEXP r_frame, SEXP r_show)
{
   wxWindow *frame = (wxWindow *) R_get_wxWidget_Ref(r_frame, "wxWindow");
   bool show = LOGICAL(r_show)[0];
   SEXP r_ans = R_NilValue;

   frame->Show(show);
 
   return(r_ans);
}

SEXP
R_wxFrame_CreateStatusBar( SEXP r_frame,
                           SEXP r_number,
                           SEXP r_style,
                           SEXP r_winid,
                           SEXP r_name)
{
   wxFrame *frame = (wxFrame *) R_get_wxWidget_Ref(r_frame, NULL);
   wxStatusBar* ans;
   SEXP r_ans;

   ans = frame->CreateStatusBar();
   r_ans = R_make_wxWidget_Ref(ans, "wxStatusBar");

   return(r_ans);
}


SEXP
R_wxFrame_SetStatusText(SEXP r_frame, SEXP r_text, SEXP r_number)
{
   wxFrame *frame = (wxFrame *) R_get_wxWidget_Ref(r_frame, NULL);
   wxString text = wxString(CHAR(STRING_ELT(r_text, 0)), wxConvUTF8);
   int number = 0;
   SEXP r_ans = R_NilValue;

   frame->SetStatusText(text, number);

   return(r_ans);
}

extern "C"
SEXP
R_wxFrame_SetMenuBar(SEXP r_frame, SEXP r_menuBar)
{
    DECLARE_RWX_REF(frame, wxFrame);
    DECLARE_RWX_REF(menuBar, wxMenuBar);
    frame->SetMenuBar(menuBar);
    return(R_NilValue);
}

extern "C"
SEXP
R_wxFrame_GetMenuBar(SEXP r_frame)
{
    DECLARE_RWX_REF(frame, wxFrame);
    wxMenuBar *ans;
    ans = frame->GetMenuBar();
    return(R_make_wxWidget_Ref(ans, "wxMenuBar"));
}

extern "C"
SEXP
R_wxFrame_GetToolBar(SEXP r_frame)
{
    DECLARE_RWX_REF(frame, wxFrame);
    wxToolBar *ans;
    ans = frame->GetToolBar();
    return(R_make_wxWidget_Ref(ans, "wxToolBar"));
}

extern "C"
SEXP
R_wxFrame_CreateToolBar(SEXP r_frame, SEXP r_style, SEXP r_id, SEXP r_name)
{
    DECLARE_RWX_REF(frame, wxFrame);
    long style = (long) REAL(r_style)[0];
    wxWindowID id  = (wxWindowID) INTEGER(r_id)[0];
    const wxString name = R_to_wxString(r_name);
    wxToolBar *ans;
    ans = frame->CreateToolBar(style, id, name);
    return(R_make_wxWidget_Ref(ans, "wxToolBar"));
}



/* For the app
SEXP
R_RwxFrame_SetTopWindow(SEXP r_frame)
{
   wxFrame *frame = (wxFrame *) R_get_wxWidget_Ref(r_frame, NULL);
   frame->SetTopWindow(frame);
}
*/
