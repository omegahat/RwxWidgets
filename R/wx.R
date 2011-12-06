Point =
  #
  # Two things can happen here
  #  create an R Point object,
  # or
  #  create an internal C++ Point object.
function(x, y, ref = TRUE)
{
  p = as.integer(c(x, y))
  class(p) <- "Point"
  p
}  


Size =
  #
  # Two things can happen here
  #  create an R Point object,
  # or
  #  create an internal C++ Point object.
function(w, h, ref = TRUE)
{
  p = as.integer(c(w, h))
  class(p) <- "Size"
  p
}  


isWxWidget =
function(obj)
{
 ans = !is.null(obj) && (is(obj, "wxWidget") || is(obj, "RwxObject") || is(obj, "wxWindow"))
 # Perhaps check the origin of the class definition, i.e. the package attribute is RwxWidgets.
 
 ans
}

setMethod("$", "C++ExternalPtr",
          function(x, name) {
            fn = paste(class(x), name, sep = "_")
            if(!exists(fn, mode = "function")) {
                   # lookup ancestor classes
              ancestors = extends(class(x))
              for(i in ancestors) {
                ok = FALSE
                fn = paste(class(x), name, sep = "_")
                if(exists(fn, mode = "function")){
                  ok = TRUE
                  break
                }

                if(!ok)
                  stop("No such 'method' ", name, " for ", class(x)) 
              }
            }
            fn = get(fn, mode = "function")
            return(function(...) 
                    fn(x, ...))
          })



setMethod("$", "wxObject",
          function(x, name) {
           classes = getWxClassInfo(x, TRUE)
           if(length(classes) == 0)
             stop("No classes for supposed wxObject")

           klasses = classes
           classes = paste(classes, name, sep = "_")
           for(tmp in classes) {
             if(exists(tmp, mode = "function")) {
               f = get(tmp, mode = "function")

               if("staticMethod" %in% names(attributes(f)))
                 return(function(...) f(...))
               else
                 return(function(...) { f(x, ...) })
             }
           }

           stop("Cannot find method ", name, " for any of ", paste(klasses, collapse = ", "), " classes")
          })



wxWindow_GetId =
function(this)
{
  .Call("R_wxWindow_GetId", this)
}


