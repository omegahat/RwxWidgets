#include "RwxHTML.h"

extern "C" {
  SEXP R_wxHtmlLinkInfo_GetHref(SEXP r_this);
  SEXP R_wxHtmlLinkInfo_GetTarget(SEXP r_this);
  SEXP R_wxHtmlLinkInfo_cast(SEXP r_obj);
}

SEXP 
R_wxHtlLinkInfo_cast(SEXP r_obj)
{
    DECLARE_RWX_REF(obj, wxObject);
    wxHtmlLinkInfo *info;
    info = wxDynamicCast(obj, wxHtmlLinkInfo);
    if(!info) {
        PROBLEM "failed to cast object to wxHtmlLinkInfo"
        ERROR;
    }
    return(R_make_wxWidget_Ref(info, "wxHtmlLinkInfo"));
}

SEXP
R_wxHtmlLinkInfo_GetHref(SEXP r_this)
{
  wxHtmlLinkInfo *This = GET_RWX_REF(r_this, wxHtmlLinkInfo);
  SEXP r_ans = wxStringToR(This->GetHref());
  return(r_ans);
}


SEXP
R_wxHtmlLinkInfo_GetTarget(SEXP r_this)
{
  wxHtmlLinkInfo *This = GET_RWX_REF(r_this, wxHtmlLinkInfo);
  SEXP r_ans = wxStringToR(This->GetTarget());
  return(r_ans);
}


