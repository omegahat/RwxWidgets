#include <wx/notebook.h>
#include <wx/imaglist.h>
#include "RwxUtils.h"

/*
 Image list accessors and manipulation.
*/

extern "C" {

    SEXP R_wxNotebook_new(SEXP r_parent, SEXP r_id, SEXP r_pos, SEXP r_size, SEXP r_style, SEXP r_name);
SEXP R_wxNotebook_AddPage(SEXP r_this, SEXP r_page, SEXP r_text, SEXP r_selected, SEXP r_imageId);
SEXP R_wxNotebook_InsertPage(SEXP r_this, SEXP r_index, SEXP r_page, SEXP r_text, SEXP r_selected, SEXP r_imageId);

SEXP R_wxNotebook_GetPageCount(SEXP r_book);
SEXP R_wxNotebook_GetRowCount(SEXP r_book);
SEXP R_wxNotebook_GetSelection(SEXP r_book);
SEXP R_wxNotebook_GetPageImage(SEXP r_this, SEXP r_index);

SEXP R_wxNotebook_RemovePage(SEXP r_this, SEXP r_index);
SEXP R_wxNotebook_AdvanceSelection(SEXP r_this, SEXP r_forward);

SEXP R_wxNotebook_SetPageImage(SEXP r_this, SEXP r_page, SEXP r_index);
SEXP R_wxNotebook_SetPageText(SEXP r_this, SEXP r_page, SEXP r_text);

SEXP R_wxNotebook_DeleteAllPages(SEXP r_book);
SEXP R_wxNotebook_DeletePage(SEXP r_this, SEXP r_index);

SEXP R_wxNotebook_GetImageList(SEXP r_book);
SEXP R_wxNotebook_SetSelection(SEXP r_book, SEXP r_page);

}


SEXP
R_wxNotebook_new(SEXP r_parent, SEXP r_id, SEXP r_pos, SEXP r_size, SEXP r_style, SEXP r_name)
{
 wxWindow *parent = GET_RWX_REF(r_parent, wxWindow);
 wxWindowID id = (wxWindowID) INTEGER(r_id)[0];
 long style = (long) REAL(r_style)[0];
 SEXP r_ans;
 wxString name = wxString(CHAR(STRING_ELT(r_name, 0)), wxConvUTF8);
 wxNotebook *ans;
 wxSize sz = wxDefaultSize;

 if(LENGTH(r_size))
     sz = R_to_wxSize(r_size);

 id = INTEGER(r_id)[0];

 ans = new wxNotebook(parent, id, wxDefaultPosition, sz, style, name);

 r_ans = R_make_wxWidget_Ref(ans, "wxNotebook");

 return(r_ans);
}


SEXP 
R_wxNotebook_GetImageList(SEXP r_book)
{
 DECLARE_RWX_REF(book, wxNotebook); 
 wxImageList *ans;
 SEXP r_ans;

 ans = book->GetImageList();

 r_ans = R_make_wxWidget_Ref(ans, "wxImageList");

 return(r_ans);
}


SEXP 
R_wxNotebook_DeleteAllPages(SEXP r_book)
{
 DECLARE_RWX_REF(book, wxNotebook); 
 SEXP r_ans;
 bool ans;

 ans = book->DeleteAllPages();

 r_ans = ScalarLogical(ans);

return(r_ans);
}

SEXP 
R_wxNotebook_GetPageCount(SEXP r_book)
{
 DECLARE_RWX_REF(book, wxNotebook); 
 SEXP r_ans;
 size_t ans;

 ans = book->GetPageCount();
 r_ans = ScalarInteger(ans);

return(r_ans);
}

SEXP 
R_wxNotebook_GetRowCount(SEXP r_book)
{
 DECLARE_RWX_REF(book, wxNotebook); 
 SEXP r_ans;
 size_t ans;

 ans = book->GetRowCount();
 r_ans = ScalarInteger(ans);

return(r_ans);
}


SEXP 
R_wxNotebook_GetSelection(SEXP r_book)
{
 DECLARE_RWX_REF(book, wxNotebook); 
 SEXP r_ans;
 int ans;

 ans = book->GetSelection();
 r_ans = ScalarInteger(ans);

return(r_ans);
}


SEXP R_wxNotebook_RemovePage(SEXP r_book, SEXP r_index)
{
 DECLARE_RWX_REF(book, wxNotebook); 

 size_t index = INTEGER(r_index)[0];
 bool ans;
 SEXP r_ans;

 ans = book->RemovePage(index);

 r_ans = ScalarLogical(ans);
 
 return(r_ans);
}

SEXP R_wxNotebook_DeletePage(SEXP r_book, SEXP r_index)
{
 DECLARE_RWX_REF(book, wxNotebook); 

 size_t index = INTEGER(r_index)[0];
 bool ans;
 SEXP r_ans;

 ans = book->DeletePage(index);

 r_ans = ScalarLogical(ans);
 
 return(r_ans);
}



SEXP R_wxNotebook_GetPageImage(SEXP r_book, SEXP r_index)
{
 DECLARE_RWX_REF(book, wxNotebook); 

 size_t index = INTEGER(r_index)[0];
 int ans;
 SEXP r_ans;

 ans = book->GetPageImage(index);

 r_ans = ScalarInteger(ans);
 
 return(r_ans);
}

SEXP R_wxNotebook_SetPageImage(SEXP r_book, SEXP r_page, SEXP r_index)
{
 DECLARE_RWX_REF(book, wxNotebook); 

 size_t index = INTEGER(r_index)[0];
 size_t page = INTEGER(r_page)[0];
 bool ans;
 SEXP r_ans;

 ans = book->SetPageImage(page, index);

 r_ans = ScalarLogical(ans);
 
 return(r_ans);
}



SEXP R_wxNotebook_SetSelection(SEXP r_book, SEXP r_page)
{
 DECLARE_RWX_REF(book, wxNotebook); 

 size_t page = INTEGER(r_page)[0];
 int ans;
 SEXP r_ans;

 ans = book->SetSelection(page);

 r_ans = ScalarInteger(ans);
 
 return(r_ans);
}



SEXP 
R_wxNotebook_SetPageText(SEXP r_book, SEXP r_page, SEXP r_text)
{
 DECLARE_RWX_REF(book, wxNotebook); 

 size_t page = INTEGER(r_page)[0];
 wxString text = wxString(CHAR(STRING_ELT(r_text, 0)), wxConvUTF8);
 bool ans;
 SEXP r_ans;

 ans = book->SetPageText(page, text);

 r_ans = ScalarLogical(ans);
 
 return(r_ans);
}



SEXP R_wxNotebook_AddPage(SEXP r_book, SEXP r_page, SEXP r_text, SEXP r_selected, SEXP r_imageId)
{
 DECLARE_RWX_REF(book, wxNotebook); 

 DECLARE_RWX_REF(page, wxWindow);//XXX when looking for the class name this is actually wxWindow  but the type is  wxNotebookPage, a simple typedef.

 wxString text = wxString(CHAR(STRING_ELT(r_text, 0)), wxConvUTF8);
 bool selected = LOGICAL(r_selected)[0];
 int imageId = INTEGER(r_imageId)[0];
 bool ans;
 SEXP r_ans;

 ans = book->AddPage(page, text, selected, imageId);

 r_ans = ScalarLogical(ans);
 
 return(r_ans);
}


SEXP 
R_wxNotebook_InsertPage(SEXP r_book, SEXP r_index, SEXP r_page, SEXP r_text, SEXP r_selected, SEXP r_imageId)
{
 DECLARE_RWX_REF(book, wxNotebook); 

 DECLARE_RWX_REF(page, wxNotebookPage);

 size_t index = INTEGER(r_index)[0];
 wxString text = wxString(CHAR(STRING_ELT(r_text, 0)), wxConvUTF8);
 bool selected = LOGICAL(r_selected)[0];
 int imageId = INTEGER(r_imageId)[0];
 bool ans;
 SEXP r_ans;

 ans = book->InsertPage(index, page, text, selected, imageId);

 r_ans = ScalarLogical(ans);
 
 return(r_ans);
}


SEXP 
R_wxNotebook_AdvanceSelection(SEXP r_book, SEXP r_forward)
{
  DECLARE_RWX_REF(book, wxNotebook)
  bool forward = LOGICAL(r_forward)[0];
  SEXP ans = R_NilValue;

  book->AdvanceSelection(forward);

  return(ans);
}

extern "C"
SEXP 
R_wxNotebook_SetImageList(SEXP r_book, SEXP r_imageList)
{
    DECLARE_RWX_REF(book, wxNotebook); 
    DECLARE_RWX_REF(imageList, wxImageList); 
       
    book->SetImageList(imageList);
    return(R_NilValue);
}


extern "C"
SEXP 
R_wxNotebook_GetPageText(SEXP r_book, SEXP r_page)
{
 DECLARE_RWX_REF(book, wxNotebook); 

 size_t page = INTEGER(r_page)[0];
 wxString ans;
 SEXP r_ans;

 ans = book->GetPageText(page);

 r_ans = wxStringToR(ans);
 
 return(r_ans);
}



extern "C"
SEXP 
R_wxNotebook_GetPage(SEXP r_book, SEXP r_page)
{
 DECLARE_RWX_REF(book, wxNotebook); 

 size_t page = INTEGER(r_page)[0];
 wxNotebookPage *ans;
 SEXP r_ans;

 ans = book->GetPage(page);

 r_ans = R_make_wxWidget_Ref(ans, "wxNotebookPage");
 
 return(r_ans);
}


extern "C"
SEXP 
R_wxNotebook_GetCurrentPage(SEXP r_book)
{
 DECLARE_RWX_REF(book, wxNotebook); 

 wxNotebookPage *ans;
 SEXP r_ans;

 ans = book->GetCurrentPage();

 r_ans = R_make_wxWidget_Ref(ans, "wxNotebookPage");
 
 return(r_ans);
}
