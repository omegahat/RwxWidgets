#if 0
#include <wx/utils.h>
#include "RwxUtils.h"

extern "C" {
    SEXP R_wxGetMouseState();
}

SEXP 
R_wxGetMouseState()
{
  wxMouseState state = wxGetMouseState();
  state.LeftDown()
}

#else

static void foo() {}

#endif
