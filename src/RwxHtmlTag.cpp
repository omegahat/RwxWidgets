#include <wx/wx.h>
#include <wx/html/htmltag.h>
#include "RwxUtils.h"

extern "C" {
    SEXP R_wxHtmlTag_GetParent(SEXP r_tag);
    SEXP R_wxHtmlTag_GetFirstSibling(SEXP r_tag);
    SEXP R_wxHtmlTag_GetLastSibling(SEXP r_tag);
    SEXP R_wxHtmlTag_GetChildren(SEXP r_tag, SEXP all);
    SEXP R_wxHtmlTag_GetNextSibling(SEXP r_tag);
    SEXP R_wxHtmlTag_GetPreviousSibling(SEXP r_tag);

    SEXP R_wxHtmlTag_GetBeginPos(SEXP r_tag);
    SEXP R_wxHtmlTag_GetEndPos1(SEXP r_tag);
    SEXP R_wxHtmlTag_GetEndPos2(SEXP r_tag);

    SEXP R_wxHtmlTag_GetName(SEXP r_tag);
    SEXP R_wxHtmlTag_HasParam(SEXP r_tag, SEXP r_name);
    SEXP R_wxHtmlTag_GetParam(SEXP r_tag, SEXP r_name, SEXP r_with_commas);
    SEXP R_wxHtmlTag_GetAllParams(SEXP r_tag);
}

SEXP
R_wxHtmlTag_GetParent(SEXP r_tag)
{
  wxHtmlTag *tag = GET_RWX_REF(r_tag, wxHtmlTag);
  wxHtmlTag *parent = tag->GetParent();
  return(R_make_wxWidget_Ref(parent, "wxHtmlTag"));
}

SEXP
R_wxHtmlTag_GetFirstSibling(SEXP r_tag)
{
  wxHtmlTag *tag = GET_RWX_REF(r_tag, wxHtmlTag);
  wxHtmlTag *ans = tag->GetFirstSibling();
  return(R_make_wxWidget_Ref(ans, "wxHtmlTag"));
}

SEXP
R_wxHtmlTag_GetLastSibling(SEXP r_tag)
{
  wxHtmlTag *tag = GET_RWX_REF(r_tag, wxHtmlTag);
  wxHtmlTag *ans = tag->GetLastSibling();
  return(R_make_wxWidget_Ref(ans, "wxHtmlTag"));
}

SEXP
R_wxHtmlTag_GetNextSibling(SEXP r_tag)
{
  wxHtmlTag *tag = GET_RWX_REF(r_tag, wxHtmlTag);
  wxHtmlTag *ans = tag->GetNextSibling();
  return(R_make_wxWidget_Ref(ans, "wxHtmlTag"));
}

SEXP
R_wxHtmlTag_GetPreviousSibling(SEXP r_tag)
{
  wxHtmlTag *tag = GET_RWX_REF(r_tag, wxHtmlTag);
  wxHtmlTag *ans = tag->GetPreviousSibling();
  return(R_make_wxWidget_Ref(ans, "wxHtmlTag"));
}

SEXP
R_wxHtmlTag_GetChildren(SEXP r_tag, SEXP all)
{
  wxHtmlTag *tag = GET_RWX_REF(r_tag, wxHtmlTag);
  wxHtmlTag *ans = tag->GetChildren();
  SEXP r_ans, r_names;

  if(!ans)
      return(R_NilValue);

  if(LOGICAL(all)[0]) {
      int ctr = 0;
      wxHtmlTag *ptr = ans;
      while(ptr) {
          ctr++;
          ptr = ptr->GetNextSibling();
      }
      PROTECT(r_ans = NEW_LIST(ctr));
      PROTECT(r_names = NEW_CHARACTER(ctr));
      ctr = 0;
      ptr = ans;
      while(ptr) {
          // put names on these.
          SET_VECTOR_ELT(r_ans, ctr, R_make_wxWidget_Ref(ptr, "wxHtmlTag"));
          SET_STRING_ELT(r_names, ctr, STRING_ELT(wxStringToR(ptr->GetName()), 0));
          ctr++;
          ptr = ptr->GetNextSibling();
      }
      SET_NAMES(r_ans, r_names);
      SET_CLASS(r_ans, mkString("HTMLTagChildrenList"));
      UNPROTECT(2);
  } else
      r_ans = R_make_wxWidget_Ref(ans, "wxHtmlTag");
  return(r_ans);
}


SEXP
R_wxHtmlTag_GetName(SEXP r_tag)
{
  wxHtmlTag *tag = GET_RWX_REF(r_tag, wxHtmlTag);
  wxString name = tag->GetName();
  return(wxStringToR(name));
}

SEXP
R_wxHtmlTag_GetParam(SEXP r_tag, SEXP r_name, SEXP r_with_commas)
{
  wxHtmlTag *tag = GET_RWX_REF(r_tag, wxHtmlTag);
  wxString name = wxString(CHAR(STRING_ELT(r_name, 0)), wxConvUTF8);
  bool with_commas = LOGICAL(r_with_commas)[0];
  wxString ans;
  ans = tag->GetParam(name, with_commas);

  return(wxStringToR(ans));
}


SEXP
R_wxHtmlTag_HasParam(SEXP r_tag, SEXP r_name)
{
  wxHtmlTag *tag = GET_RWX_REF(r_tag, wxHtmlTag);
  wxString name = wxString(CHAR(STRING_ELT(r_name, 0)), wxConvUTF8);
  bool ans;
  ans = tag->HasParam(name);

  return(ScalarLogical(ans));
}


SEXP
R_wxHtmlTag_HasEnding(SEXP r_tag)
{
  wxHtmlTag *tag = GET_RWX_REF(r_tag, wxHtmlTag);
  bool ans;
  ans = tag->HasEnding();

  return(ScalarLogical(ans));
}


SEXP
R_wxHtmlTag_GetAllParams(SEXP r_tag)
{
  wxHtmlTag *tag = GET_RWX_REF(r_tag, wxHtmlTag);
  wxString ans;
  ans = tag->GetAllParams();

  return(wxStringToR(ans));
}

SEXP
R_wxHtmlTag_GetBeginPos(SEXP r_tag)
{
  wxHtmlTag *tag = GET_RWX_REF(r_tag, wxHtmlTag);
  int ans;
  ans = tag->GetBeginPos();

  return(ScalarInteger(ans));
}

SEXP
R_wxHtmlTag_GetEndPos1(SEXP r_tag)
{
  wxHtmlTag *tag = GET_RWX_REF(r_tag, wxHtmlTag);
  int ans;
  ans = tag->GetEndPos1();

  return(ScalarInteger(ans));
}

SEXP
R_wxHtmlTag_GetEndPos2(SEXP r_tag)
{
  wxHtmlTag *tag = GET_RWX_REF(r_tag, wxHtmlTag);
  int ans;
  ans = tag->GetEndPos2();

  return(ScalarInteger(ans));
}
