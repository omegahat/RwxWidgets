#include <wx/wx.h>

#define R_copyStruct(type) \
 type * \
  R_copy_##type(const type &r) \
  {                           \
   type *ans = new type();    \
   *ans = r;                  \
   return(ans);              \
 }

R_copyStruct(wxRect)
