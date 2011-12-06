#include <wx/html/winpars.h>
#include "RwxUtils.h"

extern "C" {
  SEXP R_wxHtmlParser_GetContainer(SEXP parser);
  SEXP R_wxHtmlParser_GetWindow(SEXP r_parser);

  SEXP R_wxHtmlParser_GetSource(SEXP r_parser);

  SEXP R_wxHtmlParser_GetCharHeight(SEXP r_parser);
  SEXP R_wxHtmlParser_GetCharWidth(SEXP r_parser);

  SEXP R_wxHtmlParser_PushTagHandler(SEXP r_parser, SEXP r_handler, SEXP r_tags);
  SEXP R_wxHtmlParser_PopTagHandler(SEXP r_parser);
} 


SEXP 
R_wxHtmlParser_PushTagHandler(SEXP r_parser, SEXP r_handler, SEXP r_tags)
{
    DECLARE_RWX_REF(parser, wxHtmlParser);
    DECLARE_RWX_REF(handler, wxHtmlTagHandler);
    wxString tags = R_to_wxString(r_tags);
    parser->PushTagHandler(handler, tags);
    return(R_NilValue);
}

SEXP 
R_wxHtmlParser_PopTagHandler(SEXP r_parser)
{
    DECLARE_RWX_REF(parser, wxHtmlParser);
    parser->PopTagHandler();
    return(R_NilValue);
}



SEXP
R_wxHtmlParser_GetContainer(SEXP r_parser)
{
  wxHtmlWinParser *parser = GET_RWX_REF(r_parser, wxHtmlWinParser);
  wxHtmlContainerCell *cell = parser->GetContainer();

  return(R_make_wxWidget_Ref(cell, "wxHtmlContainerCell"));
}


#include <wx/html/htmlwin.h>
SEXP
R_wxHtmlParser_GetWindow(SEXP r_parser)
{
  wxHtmlWinParser *parser = GET_RWX_REF(r_parser, wxHtmlWinParser);
  wxHtmlWindow *ans = parser->GetWindow();

  return(R_make_wxWidget_Ref(ans, "wxHtmlWindow"));
}

SEXP 
R_wxHtmlParser_GetCharHeight(SEXP r_parser)
{
    DECLARE_RWX_REF(parser, wxHtmlWinParser);
    return(ScalarInteger(parser->GetCharHeight()));
}

SEXP 
R_wxHtmlParser_GetCharWidth(SEXP r_parser)
{
    DECLARE_RWX_REF(parser, wxHtmlWinParser);
    return(ScalarInteger(parser->GetCharWidth()));
}

SEXP 
R_wxHtmlParser_GetSource(SEXP r_parser)
{
    DECLARE_RWX_REF(parser, wxHtmlWinParser);
    wxString *ptr;
    ptr = parser->GetSource();

    return(R_make_wx_Ref(ptr, "wxString"));
}


extern "C"
SEXP
R_wxHtmlParser_GetDC(SEXP r_parser)
{
    DECLARE_RWX_REF(parser, wxHtmlWinParser);
    wxDC *dc;
    dc = parser->GetDC();
    
    return(R_make_wx_Ref(dc, "wxDC"));
}


extern "C"
SEXP
R_wxHtmlWordCell_new(SEXP r_txt, SEXP r_dc)
{
    wxString txt = R_to_wxString(r_txt);
    DECLARE_RWX_REF(dc, wxDC);
    wxHtmlWordCell *ans;
    
    ans = new wxHtmlWordCell(txt, *dc);
    
    return(R_make_wx_Ref(ans, "wxHtmlWordCell"));
}





#if 0
// this is a protected method.
extern "C"
SEXP 
R_wxHtmlParser_AddText(SEXP r_parser, SEXP r_txt)
{
    DECLARE_RWX_REF(parser, wxHtmlWinParser);
    wxChar *txt;
    size_t n = strlen(CHAR(STRING_ELT(r_txt, 0))) + 1;
    txt = (wxChar *) R_alloc(n, sizeof(wxChar));
        
    wxMBConv::FromWChar(txt, n, CHAR(STRING_ELT(r_txt, 0)), wxNO_LEN);

    parser->AddText(txt);
    return(R_NilValue);
}
#endif
