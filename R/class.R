
# This won't work for the wxNonDynamicObject unless we
# explicitly create an instance of the right R class.
# If we have a C++ routine that does not know the specific
# type then it can only create a wxObject and we are sunk after
# that as we can never know unless we cast.
# XXX Generate routines to do casting with dynamic_cast, one routine
# for each class.
#
setGeneric("getWxClassInfo",
           function(obj, recursive = TRUE) {
             standardGeneric("getWxClassInfo")
           })

setMethod("getWxClassInfo", "wxNonDynamicObject",
           function(obj, recursive = TRUE) {
             obj@classes
           })


  #
  # Get the class name hierarchy for an object or class name
  # if recursive = TRUE, this walks the hierarchy.
  # otherwise, it just gets the immediate ancestor classes.
  #
tmp = function(obj, recursive = TRUE)
{
  if(is.character(obj) && obj[1] == "") 
    return(character(0))

  ans = .Call("R_getClassNames", obj, FALSE)

  ans = ans[ans != ""]
  
  if(!recursive)
    return(ans)

  ans = unique(ans)
  if(any(ans != "")) {
    ans = unique(c(ans, unlist(sapply(ans[-1], getWxClassInfo))))
  }

  ans
}
setMethod("getWxClassInfo", "wxObject", tmp)
setMethod("getWxClassInfo", "character", tmp)

wxObject =
  #
  # Creates a wxObject in R from a simple reference
  # and attempts to see if there is a more specific
  # class than wxObject in R that corresponds to the
  # class name of the interal wxObject instance.
  #
function(ref, obj = new("wxObject"))
{
  m = missing(obj)
  if(is(ref, "ExternalPtr"))
    ref = ref@ref
  obj@ref = ref
  if(m) {
    klasses = getWxClassInfo(obj, FALSE)

    if(!is.null(getClassDef(klasses))) {
      obj = new(klasses, ref = obj@ref)
    } else
      warning("Can't find class ", klasses[1])
  }

  obj
}  


getWxMethods =
function(obj)
{
  classes = getWxClassInfo(obj)

  grep(paste("^(", paste(classes, collapse = "|"), ")_", sep = ""), objects("package:RwxWidgets"), value = TRUE)
}  
