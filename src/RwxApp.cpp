#include "RwxApp.h"
#include <string.h>

extern "C" {
   SEXP R_RwxApp_new(SEXP onInit);
   SEXP R_wxWidgets_init(SEXP args, SEXP r_doStart);
   SEXP R_wxWidgets_wxInitialize();
   SEXP R_wxWidgets_wxCleanup();	
   SEXP R_wxApp_wxTheApp(SEXP onInit);

   SEXP R_wxApp_ExitMainLoop(SEXP r_app);	

   void R_wx_main(char **args, int *nargs);

    SEXP R_wxAppBase_MainLoop(SEXP r_app);
}

#define RWXAPP_DECLARE_APP 0 

#ifdef RWXAPP_DECLARE_APP

#if 1
DECLARE_APP(RwxApp); 
#if 1
IMPLEMENT_APP(RwxApp);
#else
IMPLEMENT_APP_NO_MAIN(RwxApp); 
#endif
#endif

#else
/* This doesn't work. Need wxInitializeStockObjects() to be called somewhere.*/
wxAppConsole *R_wxCreateApp() {
        wxAppConsole::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE,         
                                        "your program");                   
        return(NULL);
}
wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction) R_wxCreateApp);        
wxApp& wxGetApp() { return *wxTheApp; }


#endif /* RWXAPP_DECLARE_APP */


class R_internal_wxApp : public wxApp {
  public:
   virtual bool OnInit()   {
  
      SEXP e;
      PROTECT(e = allocVector(LANGSXP, 1));
      SETCAR(e, Rf_install("OnInit"));
      Rf_eval(e, R_GlobalEnv);
      UNPROTECT(1);
      return(true);
   }
};

#ifdef RWXAPP_DECLARE_APP
void
R_wx_main(char **args,  int *nargs)
{
  new R_internal_wxApp();
  main(*nargs, args);
}
#endif

#include <wx/image.h>

SEXP 
R_wxWidgets_wxInitialize()
{
    bool ans;
    static char *argv[] = {"RwxWidgets"};
    ans = wxInitialize(); // need wxChar sizeof(argv)/sizeof(argv[0]), argv); 

    wxInitAllImageHandlers();

    return(Rf_ScalarLogical(ans));
}

SEXP 
R_wxWidgets_wxCleanUp()
{// what about ::wxCleanUp () 
//    wxApp::CleanUp();
    return(R_NilValue);
}

#include <wx/image.h>

static int Rwx_Initialized =  false;

SEXP
R_wxWidgets_init(SEXP args, SEXP r_doStart)
{
  int argc = Rf_length(args), i;
  char **argv;
  int status;
  bool doStart = (bool) LOGICAL(r_doStart)[0];
  SEXP ans;

  if(Rwx_Initialized)
      return(R_NilValue);

  argv = (char **) calloc(argc + 1, sizeof(char *));
  for(i = 0; i < argc; i++)
    argv[i] = strdup(CHAR(STRING_ELT(args, i)));
/*  argv[argc] = '\0'; */


  wxInitAllImageHandlers();

  if(doStart) {
      ans = Rf_ScalarLogical(wxEntryStart(argc, argv));
  } else {
      status = wxEntry(argc, argv);
      ans = Rf_ScalarInteger(status);
  }

  Rwx_Initialized = true;

  return(ans);
}


SEXP
R_RwxApp_new(SEXP onInit)
{
  RwxApp *app = new RwxApp(onInit);
  return(R_make_wxWidget_Ref(app, "RwxApp"));
}


SEXP
R_wxApp_wxTheApp(SEXP onInit)
{
  return(R_make_wxWidget_Ref(wxTheApp, "RwxApp"));
}

bool 
RwxApp::OnInit()
{
  SEXP r_ans;
  bool ans = false;
  SEXP e;

  ans = wxApp::OnInit();
  if(!this->R_OnInit || this->R_OnInit == R_NilValue) {
      /* call the inherited method */
      ans = false;
      return(ans);
  }

  PROTECT(e = allocVector(LANGSXP, 2));
  SETCAR(e, this->R_OnInit);
  SETCAR(CDR(e), R_make_wxWidget_Ref(this, "RwxApp"));

  PROTECT(r_ans = Rf_eval(e, R_GlobalEnv));

  if(TYPEOF(r_ans) == LGLSXP) {
    ans = LOGICAL(r_ans)[0]; 
  }
  UNPROTECT(2);

  return(ans);
}



SEXP 
R_wxApp_ExitMainLoop(SEXP r_app)
{
    DECLARE_RWX_REF(app, wxApp);
    app->ExitMainLoop();
    return(R_NilValue);
}	


SEXP
R_wxApp_MainLoop(SEXP r_app)
{
    DECLARE_RWX_REF(app, wxApp);
    if(!app) {
        PROBLEM  "not a wxApp"
        ERROR;
    }

    int status = app->MainLoop();
    return(Rf_ScalarInteger(status));
}
