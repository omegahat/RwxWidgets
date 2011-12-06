#ifndef RWXUTILS_H
#define RWXUTILS_H


#include <wx/string.h>
#include <wx/arrstr.h>
#include <wx/dynarray.h>

#include <Rinternals.h>
#include <Rdefines.h>

extern "C" {


 SEXP R_wxWindow_GetId(SEXP r_win);
};

SEXP R_make_wxWidget_Ref(const wxObject *ref, const char *typeName, bool dynamicClass = false); // for wxObjects
SEXP R_make_wx_Ref(void *ref, const char *typeName); // for non wxObject objects

void * R_get_wxWidget_Ref(SEXP ref, const char *typeName, bool nullOk = false);

SEXP wxStringToR(const wxString &);
SEXP wxStringArrayToR(const wxArrayString &ans);
SEXP wxArrayIntToR(const wxArrayInt &ans);

wxArrayString RcharacterToArrayString(SEXP r_items);

SEXP Rwx_getClassNames(wxClassInfo *info, bool recursive);

#define GET_RWX_REF(obj, type)  (type *) R_get_wxWidget_Ref(obj, #type)
#define DECLARE_RWX_REF(obj, type)  type * obj = (type *) R_get_wxWidget_Ref(r_##obj, #type);
#define DECLARE_RWX_REF_NULL_OK(obj, type)  type * obj = (type *) R_get_wxWidget_Ref(r_##obj, #type, true);


#define R_to_wxString(r_value)  wxString(CHAR(STRING_ELT((r_value), 0)), wxConvUTF8)

extern FILE *LOG;
#define WRITE_TO_LOG(fmt, args...) \
    { if(!LOG)  \
        LOG = fopen("wx.log", "w"); \
     fprintf(LOG, fmt, ##args); \
      fflush(LOG); \
    }

#include <wx/event.h>

SEXP createDynamicRwxReference(wxEvent *ev, const char *tagName = "wxCommandEvent");


wxRect R_to_wxRect(const SEXP r_obj);
wxPoint R_to_wxPoint(const SEXP r_obj);
wxSize R_to_wxSize(const SEXP r_obj);
wxString R_as_wxString(const SEXP r_obj);

int RtowxArrayString(SEXP r_choices, wxArrayString &choices);

#endif
