#include <wx/wx.h>
#include "RwxUtils.h"
#include "Rdefines.h"

extern "C" {
    SEXP R_wxObject_new(SEXP r_className);
    SEXP R_getClassNames(SEXP r_obj, SEXP r_recursive);
}

SEXP
R_wxObject_new(SEXP r_className)
{
  /* Use RTTI. */
  wxString className = wxString(CHAR(STRING_ELT(r_className, 0)), wxConvUTF8);
  wxObject *ans;
  SEXP r_ans;

  ans = wxCreateDynamicObject(className);
  if(!ans) {
      PROBLEM "Cannot dynamically create an instance of wxWidgets class %s",
           CHAR(STRING_ELT(r_className, 0))
      ERROR;
  }
    
  r_ans = R_make_wxWidget_Ref(ans,  CHAR(STRING_ELT(r_className, 0)));
  return(r_ans);
}


SEXP
R_isWxWidget(SEXP obj)
{
    return(R_NilValue); 
}


SEXP
Rwx_getClassNames(wxClassInfo *info, bool recursive)
{
   SEXP el; 
   const wxChar *ptr;
   SEXP ans;

   if(!recursive) {
       PROTECT(ans = NEW_CHARACTER(3));
       ptr = info->GetClassName();
        /* See http://www.wxwidgets.org/manuals/2.6.3/wx_mbconvclasses.html#convertingstrings */
  //     const char* els = (const char*) wxString(ptr).mb_str(); /*wxConvCurrent->cWX2MB(ptr); */
       //XXX unnecessary to create STRING, just want CHAR()
       SEXP tmp = wxStringToR(ptr);
       SET_STRING_ELT(ans, 0, STRING_ELT(tmp, 0)); /* mkChar(els)); */
       ptr = info->GetBaseClassName1();
       if(ptr) {
           tmp = wxStringToR(ptr);
          SET_STRING_ELT(ans, 1, STRING_ELT(tmp, 0)); /* mkChar(els)); */
       }
       ptr = info->GetBaseClassName2();
       if(ptr) {
           tmp = wxStringToR(ptr);
          SET_STRING_ELT(ans, 2, STRING_ELT(tmp, 0)); /* mkChar(els)); */
       }
       UNPROTECT(1);
       return(ans);
   } else {
      PROBLEM  "Unhandled recursive case"
          ERROR;
   }
/*

   PROTECT(ans = NEW_CHARACTER(20));

   ptr = info->GetClassName();
   if(ptr) {
       el = mkChar(ptr);
       SET_STRING_ELT(ans, *i++, el);
   }

*/ 
   return(R_NilValue);
}
SEXP
R_getClassNames(SEXP r_obj, SEXP r_recursive)
{
   wxObject *obj;
   bool recursive = LOGICAL(r_recursive)[0];   
   wxClassInfo *info;

   if(TYPEOF(r_obj) == STRSXP) {
     info = wxClassInfo::FindClass(wxString(CHAR(STRING_ELT(r_obj, 0)), wxConvUTF8));
   } else {
     obj  = (wxObject *)  GET_RWX_REF(r_obj, wxObject);
     info = obj->GetClassInfo();
   }

   if(!info) 
       return(NEW_CHARACTER(0));

   return(Rwx_getClassNames(info, recursive));
}
