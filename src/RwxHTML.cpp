#include "RwxHTML.h"


extern "C" {
    SEXP R_wxHtmlWindow_new(SEXP r_parent, SEXP r_id, SEXP OnLinkClicked, SEXP r_pos, SEXP r_size, SEXP r_style, SEXP r_name);
    SEXP R_wxHtmlWindow_LoadPage(SEXP r_win, SEXP r_uri);
    SEXP R_wxHtmlWindow_AppendToPage(SEXP r_win, SEXP r_uri);
    SEXP R_wxHtmlWindow_SetPage(SEXP r_win, SEXP r_source);
    SEXP R_wxHtmlWindow_SetRelatedFrame(SEXP r_win, SEXP r_parent, SEXP r_title);
    SEXP R_wxHtmlWindow_GetParser(SEXP r_html);

    SEXP  R_wxHtmlWinParser_AddTagHandler(SEXP r_parser, SEXP r_handler);
    SEXP R_wxInitAllImageHandlers();
}


#include <wx/image.h>
SEXP
R_wxInitAllImageHandlers()
{
  wxInitAllImageHandlers();

  return(ScalarLogical(true));
}

SEXP
R_wxHtmlWindow_new(SEXP r_parent, SEXP r_id, SEXP OnLinkClicked, SEXP r_pos, SEXP r_size, SEXP r_style, SEXP r_name)
{
    wxWindow *parent = NULL;
    wxWindowID id;
    long style = (long) REAL(r_style)[0];
    const wxString name = R_to_wxString(r_name);
    wxPoint pos = wxDefaultPosition;
    wxSize size = wxDefaultSize;    

    if(LENGTH(r_size)) size = R_to_wxSize(r_size);
    if(LENGTH(r_pos)) pos = R_to_wxPoint(r_pos);


    if(r_parent != R_NilValue)
        parent = GET_RWX_REF(r_parent, wxWindow);

    wxHtmlWindow *ans;
    SEXP r_ans = R_NilValue;

    id = INTEGER(r_id)[0];

    if(Rf_length(OnLinkClicked)) {
        fprintf(stderr, "Create R_wxHtmlWindow\n");
        ans = new R_wxHtmlWindow(parent, id, OnLinkClicked, pos, size, style, name);
    } else
        ans = new wxHtmlWindow(parent, id, pos, size, style, name);

    r_ans = R_make_wxWidget_Ref(ans, "wxHtmlWindow");

    return(r_ans);
}


SEXP
R_wxHtmlWindow_LoadPage(SEXP r_win, SEXP r_uri)
{
    wxHtmlWindow *win = GET_RWX_REF(r_win, wxHtmlWindow);
    wxString str = wxString(CHAR(STRING_ELT(r_uri, 0)), wxConvUTF8);
    bool ans;
    SEXP r_ans;
    ans = win->LoadPage(str);
    r_ans = Rf_ScalarLogical(ans);
    return(r_ans);
}


SEXP
R_wxHtmlWindow_AppendToPage(SEXP r_win, SEXP r_source)
{
    wxHtmlWindow *win = GET_RWX_REF(r_win, wxHtmlWindow);
    wxString str = wxString(CHAR(STRING_ELT(r_source, 0)), wxConvUTF8);
    bool ans;
    SEXP r_ans;
    ans = win->AppendToPage(str);
    r_ans = Rf_ScalarLogical(ans);
    return(r_ans);
}



SEXP
R_wxHtmlWindow_SetPage(SEXP r_win, SEXP r_source)
{
    wxHtmlWindow *win = GET_RWX_REF(r_win, wxHtmlWindow);
    wxString str = wxString(CHAR(STRING_ELT(r_source, 0)), wxConvUTF8);
    bool ans;
    SEXP r_ans;

    ans = win->SetPage(str);
    r_ans = Rf_ScalarLogical(ans);

    return(r_ans);
}


SEXP
R_wxHtmlWindow_SetRelatedFrame(SEXP r_win, SEXP r_parent, SEXP r_source)
{
    wxHtmlWindow *html = GET_RWX_REF(r_win, wxHtmlWindow);
    wxFrame *parent = GET_RWX_REF(r_win, wxFrame);
    wxString str = wxString(CHAR(STRING_ELT(r_source, 0)), wxConvUTF8);

    html -> SetRelatedFrame(parent, str);

    return(R_NilValue);
}



void
R_wxHtmlWindow::OnLinkClicked(const wxHtmlLinkInfo &link)
{
    fprintf(stderr, "R_wxHtmlWindow::OnLinkClicked\n");
    if(!R_OnLinkClicked || Rf_length(R_OnLinkClicked) == 0) {
        wxHtmlWindow::OnLinkClicked(link);
        return;
    }

    SEXP r_this;
    SEXP r_info; 
    r_this = R_make_wxWidget_Ref(this, "RwxHtmlWindow");
    r_info = R_make_wxWidget_Ref(&link, "wxHtmlLinkInfo");
    invoke(R_OnLinkClicked, r_this, r_info);
}


SEXP
R_wxHtmlWindow_GetParser(SEXP r_html)
{
   wxHtmlWindow *html = GET_RWX_REF(r_html, wxHtmlWindow);
   wxHtmlWinParser *parser = html->GetParser();

   SEXP r_ans;
   r_ans = R_make_wxWidget_Ref(parser, "wxHtmlWinParser");

   return(r_ans);
}


SEXP 
R_wxHtmlWinParser_AddTagHandler(SEXP r_parser, SEXP r_handler)
{
    wxHtmlWinTagHandler *handler;
    handler = GET_RWX_REF(r_handler, wxHtmlWinTagHandler);
    wxHtmlWinParser *parser = GET_RWX_REF(r_parser, wxHtmlWinParser);
    parser->AddTagHandler(handler);

    return(R_NilValue);
}
