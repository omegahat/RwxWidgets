#include <wx/window.h> /* Must go here as defines macros R wants to define. */
#include <iostream>

#include "RwxUtils.h"
#include "Rdefines.h"

FILE *LOG = NULL;


extern "C" {
    SEXP R_wxWidgets_getScreenDimensions(SEXP asMM);
    SEXP R_wxWidgets_IsKindOf(SEXP r_src);
    SEXP R_isMouseUp();
};

SEXP
R_make_wxWidget_Ref(const wxObject *ref, const char *typeName, bool dynamicClass)
{
 SEXP ans, klass;

 if(!ref) {
   PROBLEM "Attempting to create a reference to a NULL value for type %s", typeName
   WARN;
   return(R_NilValue);
 }

 if(dynamicClass) {
     wxClassInfo *info = ref->GetClassInfo();
     const wxChar *name = info->GetClassName();
     klass = MAKE_CLASS(CHAR(STRING_ELT(wxStringToR(name), 0))); //XXXXX don't need to do all this.
 } else {
     klass = MAKE_CLASS((char *)typeName);
 }

 PROTECT(klass);
 PROTECT(ans = NEW(klass));
 ans = SET_SLOT(ans, Rf_install("ref"), R_MakeExternalPtr((void *) ref, Rf_install(typeName), R_NilValue));

 UNPROTECT(2);
 return(ans);
}

SEXP
R_make_wx_Ref(void *ref, const char *typeName)
{
 SEXP ans, klass;

 if(!ref) {
   PROBLEM "Attempting to create a reference to a NULL value for type %s", typeName
   WARN;
   return(R_NilValue);
 }

 PROTECT(klass = MAKE_CLASS((char *)typeName));
 PROTECT(ans = NEW(klass));
 ans = SET_SLOT(ans, Rf_install("ref"), R_MakeExternalPtr(ref, Rf_install(typeName), R_NilValue));

 UNPROTECT(2);
 return(ans);
}



/* This could go into RwxRTTI.cpp but is fine here.*/
static bool
checkInheritance(wxObject *obj, const char *typeName)
{
    wxClassInfo *target = wxClassInfo::FindClass(wxString(typeName, wxConvUTF8));
    wxClassInfo *cur = obj->GetClassInfo();
    bool ans = cur->IsKindOf(target);
    return(ans);
}


// string version for quick test.
SEXP
R_wxWidgets_IsKindOf(SEXP r_src)
{
    wxClassInfo *src = wxClassInfo::FindClass(wxString(CHAR(STRING_ELT(r_src, 0)), wxConvUTF8));  
    wxClassInfo *target = wxClassInfo::FindClass(wxString(CHAR(STRING_ELT(r_src, 1)), wxConvUTF8));  

    return(ScalarLogical(src->IsKindOf(target)));
}


void *
R_get_wxWidget_Ref(SEXP ref, const char *typeName, bool nullOk)
{
  SEXP el;
  void *ptr;

  if(nullOk && ref == R_NilValue)
      return(NULL);

  el = GET_SLOT(ref, Rf_install("ref"));

  if(el == R_NilValue || TYPEOF(el) != EXTPTRSXP) {
    PROBLEM "Object passed to R_get_wxWidget_Ref does not have a ref slot that is an external pointer"
    ERROR;
  }


  ptr = R_ExternalPtrAddr(el);

  if(!ptr) {
   PROBLEM "NULL value for external pointer address"
    ERROR;
  }

  if(typeName && Rf_install(typeName) !=  R_ExternalPtrTag(el)) {
//      ptr = wxDynamicCast((wxObject *)ptr, wxObject);
//      ptr = dynamic_cast<wxObject *>(ptr);
      if(!ptr) {
          PROBLEM "invalid reference passed as wxObject (actually for class %s)", typeName
          ERROR;
      }
      if(checkInheritance((wxObject *) ptr, typeName) == false) {
          PROBLEM "Unexpected tag for wxWidgets external pointer: got '%s', expecting '%s' and there isn't an inheritance relationship",
              CHAR(PRINTNAME(R_ExternalPtrTag(el))), 
              typeName
         ERROR;
      }
  }  

  return(ptr);
}

#define DEREF_REF(x, type) *((type *) R_get_wxWidget_Ref(x, #type))

extern "C" {
  SEXP TestDeref(SEXP obj);
}
SEXP 
TestDeref(SEXP obj)
{
  wxSize sz;
  sz = DEREF_REF(obj, wxSize);

  return(R_NilValue);
}

/*
SEXP
R_wxPoint_new(SEXP x)
{
  Point *p = new Point(INTEGER(x)[0], INTEGER(x)[1]);
//XXX want a general reference
  return(R_make_wxWidget_Ref(p, "Point"))
}
*/


#if 0
int
R_get_wxSize(SEXP r_size, wxSize &sz)
{
    sz = wxDefaultSize;

    if(GET_LENGTH(r_size) == 0)
        return(0);

    if(TYPEOF(r_size) == INTSXP) {
        /* Check NA. */
        sz.SetWidth(INTEGER(r_size)[0]);
        sz.SetWidth(INTEGER(r_size)[1]);
    } else {
        wxSize *tmp = R_get_wxWidget_Ref(sz, "wxSize");
        sz = *tmp;
    }

    return(0);
}
#endif




SEXP 
wxStringToR(const wxString &str)
{
  return(mkString(str.mb_str()));
}

SEXP
wxStringArrayToR(const wxArrayString &ans)
{
    SEXP r_ans;
    int n = ans.Count();
    PROTECT(r_ans = NEW_STRING(n));
    for(int i = 0; i < n; i++)
        SET_STRING_ELT(r_ans, i, STRING_ELT(wxStringToR(ans.Item(i)), 0));

    UNPROTECT(1);

      return(r_ans);
}


SEXP
wxArrayIntToR(const wxArrayInt &ans)
{
    SEXP r_ans;
    int n = ans.Count();

    PROTECT(r_ans = NEW_INTEGER(n));
    for(int i = 0; i < n; i++)
        INTEGER(r_ans)[i] = ans.Item(i);

    UNPROTECT(1);

    return(r_ans);
}

wxArrayString
RcharacterToArrayString(SEXP r_items)
{
    wxArrayString items;

    int n = GET_LENGTH(r_items), i;
    items.Alloc(n);

 
    for(i = 0; i < n ; i++) {
        wxString str = wxString(CHAR(STRING_ELT(r_items, i)), wxConvUTF8);
        items.Add(str);
    }
    return(items);
}

#include <wx/dcscreen.h>

SEXP
R_wxWidgets_getScreenDimensions(SEXP asMM)
{
  wxScreenDC dc;
  wxCoord w, h;
  SEXP ans;

  if(LOGICAL(asMM)[0])
    dc.GetSizeMM(&w, &h);
  else
    dc.GetSize(&w, &h);

  ans = allocVector(INTSXP, 2);

  INTEGER(ans)[0] = w;
  INTEGER(ans)[1] = h;

  return(ans);
}



extern "C"
SEXP 
R_wxString_Mid(SEXP r_str, SEXP r_first, SEXP r_count)
{
    DECLARE_RWX_REF(str, wxString);
    size_t first, count = wxSTRING_MAXLEN;

    if(REAL(r_count)[0] != NA_REAL)
        count = (size_t) REAL(r_count)[0];
    first = (size_t) REAL(r_first)[0];

    return(wxStringToR(str->Mid(first, count)));
}


SEXP
R_isMouseUp()
{
#if 0
    wxMouseEvent ev;
    return(ScalarLogical(ev.LeftIsDown()));
#else
    wxMouseState state = wxGetMouseState();
    return(ScalarLogical(!state.LeftDown()));

#endif
    
}

#include <wx/frame.h>

extern "C"
void
R_paintFrame(SEXP r_frame, SEXP r_event)
{
    DECLARE_RWX_REF(frame, wxFrame)
    int w = 0;
    int h = 0;
    frame->GetClientSize( &w, &h );

    wxPaintDC dc(frame);
    // dc.Clear(); -- this kills wxGTK
    dc.SetFont( wxFont( 24, wxDECORATIVE, wxNORMAL, wxNORMAL, false, _T("charter") ) );
    dc.DrawText( _T("Drag text from here!"), 100, h-50 );
}


wxPoint
R_to_wxPoint(const SEXP r_obj)
{
    wxPoint ans;

    if(TYPEOF(r_obj) == INTSXP) {
        ans.x = INTEGER(r_obj)[0];
        ans.y = INTEGER(r_obj)[1];
    } else if(TYPEOF(r_obj) == REALSXP) {
        ans.x = (int) REAL(r_obj)[0];
        ans.y = (int) REAL(r_obj)[1];
    }else if(IS_S4_OBJECT(r_obj)) {
        wxPoint *tmp = (wxPoint *) R_get_wxWidget_Ref(r_obj, "wxPoint");
        ans = *tmp;
    }

    return(ans);
}

wxSize
R_to_wxSize(const SEXP r_obj)
{
    wxSize ans = wxDefaultSize;

    if(TYPEOF(r_obj) == INTSXP) {
        ans.Set(INTEGER(r_obj)[0], INTEGER(r_obj)[1]);
    } else if(TYPEOF(r_obj) == REALSXP) {
        ans.Set((int) REAL(r_obj)[0], (int) REAL(r_obj)[1]);
    } else if(IS_S4_OBJECT(r_obj)) {
        wxSize *tmp = (wxSize *) R_get_wxWidget_Ref(r_obj, "wxSize");
        ans = *tmp;
    }

    return(ans);
}

wxString
R_as_wxString(const SEXP r_obj)
{
    wxString ans;

    if(TYPEOF(r_obj) == STRSXP) {
        
    } else if(IS_S4_OBJECT(r_obj)) {
        wxString *tmp = (wxString *) R_get_wxWidget_Ref(r_obj, "wxString");
        ans = wxString(*tmp);
    }

    return(ans);
}




wxRect
R_to_wxRect(const SEXP r_obj)
{
    wxRect ans;

    if(TYPEOF(r_obj) == INTSXP) {
        ans.x = INTEGER(r_obj)[0];
        ans.y = INTEGER(r_obj)[1];
        ans.width = INTEGER(r_obj)[2];
        ans.height = INTEGER(r_obj)[3];
    } else if(TYPEOF(r_obj) == REALSXP) {
        ans.x = (int) REAL(r_obj)[0];
        ans.y = (int) REAL(r_obj)[1];
        ans.width = (int) REAL(r_obj)[2];
        ans.height = (int) REAL(r_obj)[3];
    } else {

    }

    return(ans);
}


int
RtowxArrayString(SEXP r_choices, wxArrayString &choices)
{
    int n = GET_LENGTH(r_choices);
    choices.Alloc(n);
    for(int i = 0; i < n ; i++) {
        const char *tmp = CHAR(STRING_ELT(r_choices, i));
        choices.Add( wxString(tmp, wxConvUTF8) );
    }

    return(n);
}


extern "C"
void 
R_finalize_wxObject(SEXP r_obj)
{
    void *ptr = R_ExternalPtrAddr(r_obj);
    wxSize *obj = static_cast<wxSize *>(ptr);
    delete obj;
}

extern "C"
SEXP
R_wxObject_setFinalizer(SEXP r_obj, SEXP r_addFinalizer)
{
    R_CFinalizer_t finalizer = NULL;
    if(TYPEOF(r_addFinalizer) == LGLSXP && LOGICAL(r_addFinalizer)[0])
        finalizer = &R_finalize_wxObject;
    else if(TYPEOF(r_addFinalizer) == EXTPTRSXP) {
        finalizer = (R_CFinalizer_t) ( R_ExternalPtrAddr(r_addFinalizer) );
    }
    
    if(finalizer) {
       SEXP tmp = GET_SLOT(r_obj, Rf_install("ref"));
       R_RegisterCFinalizer(tmp, finalizer);
    }

    return(R_NilValue);       
}

/* Testing the ability to create new instances of certain classes either by copying
   */

#include <wx/tipwin.h>
#include <wx/datetime.h>
#include <wx/menu.h>
#include <wx/image.h>
#include <wx/icon.h>
void
testCopy()
{
{ wxString *a, obj;  a = new  wxString (); *a = obj; }
//{ wxMBConv *a, obj;  a = new  wxMBConv (); *a = obj; }
{ wxDateTime *a, obj;  a = new  wxDateTime (); *a = obj; }
{ wxSize *a, obj;  a = new  wxSize (); *a = obj; }
{ wxImage *a, obj;  a = new  wxImage (); *a = obj; }
{ wxObjectEventFunction *a, obj;  a = new  wxObjectEventFunction (); *a = obj; }
{ wxWindowList *a, obj;  a = new  wxWindowList (); *a = obj; }
{ wxRegion *a, obj;  a = new  wxRegion (); *a = obj; }
{ wxCursor *a, obj;  a = new  wxCursor (); *a = obj; }
{ wxIcon *a, obj;  a = new  wxIcon (); *a = obj; }
{ wxIconBundle *a, obj;  a = new  wxIconBundle (); *a = obj; }
{ wxBrush *a, obj;  a = new  wxBrush (); *a = obj; }
{ wxFont *a, obj;  a = new  wxFont (); *a = obj; }
{ wxPen *a, obj;  a = new  wxPen (); *a = obj; }
{ wxColour *a, obj;  a = new  wxColour (); *a = obj; }
{ wxMenuItemList *a, obj;  a = new  wxMenuItemList (); *a = obj; }
{ wxRect *a, obj;  a = new  wxRect (); *a = obj; }
{ wxImage::HSVValue *a, obj;  a = new  wxImage::HSVValue (); *a = obj; }
{ wxBitmap *a, obj;  a = new  wxBitmap (); *a = obj; }
{ wxPoint *a, obj;  a = new  wxPoint (); *a = obj; }
{ wxString *a, obj;  a = new wxString() ; *a = obj; }


//    wxTipWindow *w, tip;
//    *w = tip;
}
