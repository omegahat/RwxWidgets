#include "RwxUtils.h"

class RwxObject : public wxObject {

public:

    RwxObject() : env(NULL) {
	env = R_GlobalEnv;
        // or create our own hashed environment.
	// setEnv(R_NewHashedEnv(R_GlobalEnv, ScalarInteger(10)));
    }

    RwxObject(SEXP e) {
	setEnv(e);
    }
    SEXP REnv() { return(env); }

protected:
    void setEnv(SEXP e) {
	if(e && GET_LENGTH(e)) {
	    R_PreserveObject(env = Rf_duplicate(e));
	} else
	    env = NULL;
    }

protected:
    SEXP env;

};
