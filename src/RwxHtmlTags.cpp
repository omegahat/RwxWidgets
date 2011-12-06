#include "RwxHtmlTags.h"


extern "C" {
    SEXP R_RwxHtmlWinTagHandler_new(SEXP r_tags, SEXP r_handler);
    SEXP R_RwxHtmlWinTagHandler_ParseInner(SEXP r_This, SEXP r_tag);
}

SEXP 
R_RwxHtmlWinTagHandler_new(SEXP r_tags, SEXP r_handler)
{

  RwxHtmlWinTagHandler *h = new RwxHtmlWinTagHandler(CHAR(STRING_ELT(r_tags, 0)), r_handler);
  SEXP r_ans;
  r_ans = R_make_wxWidget_Ref(h,  "RwxHtmlWinTagHandler");
  return(r_ans);
}


bool
RwxHtmlWinTagHandler::HandleTag(const wxHtmlTag & varib)
{

    SEXP r_this, r_info, r_parser;
    PROTECT(r_this = R_make_wxWidget_Ref(this, "RwxHtmlWinTagHandler"));
    PROTECT(r_info = R_make_wxWidget_Ref( &varib, "wxHtmlTag"));
    PROTECT(r_parser = R_make_wxWidget_Ref(m_WParser, "wxHtmlParser"));

    SEXP r_ans;
    bool ans = true;

    r_ans = invoke(handler, r_this, r_info, r_parser);

    UNPROTECT(3);

    if(r_ans == NULL) {
        ans = false;
    } else if(TYPEOF(r_ans) == LGLSXP) {
        ans = LOGICAL(r_ans)[0];
    }
    else if(IS_S4_OBJECT(r_ans)) {
         /* insert the widget for the user. */
        if(Rf_inherits(r_ans, "wxWindow")) {
            wxWindow *w = (wxWindow *) R_get_wxWidget_Ref(r_ans, "wxWindow");
            wxHtmlWidgetCell *cell = new wxHtmlWidgetCell(w);

            wxHtmlContainerCell *container = m_WParser->GetContainer();
            container->InsertCell(cell);
        }
    } 


    return(ans);
}


SEXP
R_RwxHtmlWinTagHandler_ParseInner(SEXP r_This, SEXP r_tag)
{
    DECLARE_RWX_REF(This, RwxHtmlWinTagHandler);

    const DECLARE_RWX_REF(tag, wxHtmlTag);
    This->RParseInner(*tag);

    return(R_NilValue);
}
