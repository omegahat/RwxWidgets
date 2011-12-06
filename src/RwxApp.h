#include <wx/app.h>
#include <RwxUtils.h>

#include <stdio.h>

class RwxApp : public wxApp
{
   public:

    RwxApp(SEXP onInit) 
         : wxApp() { 

        setOnInit(onInit);
    };


    RwxApp() : wxApp() { setOnInit(Rf_install("OnInit")); };


    virtual bool OnInit();


    SEXP setOnInit(SEXP onInit) {
        SEXP prev = NULL;

	prev = R_OnInit;
        R_OnInit = onInit;
	if(R_OnInit != 0 && Rf_length(R_OnInit))
           R_PreserveObject(R_OnInit);


        return(prev);
    }

   protected:

     SEXP R_OnInit;    

};
