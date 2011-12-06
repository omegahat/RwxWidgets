htmlTagHandlers =
  #
  #
  #
function(handlers = list(), objectHandlers = defaultObjectHandlers(), formHandlers = htmlFormTagHandlers(), envir = globalenv())
{
  if(is.function(objectHandlers))
     handlers[["object"]] = objectHandlers
  else if( length(objectHandlers))
     handlers[["object"]] = htmlParserObjectHandler(objectHandlers, envir)

  if(length(formHandlers))
     handlers = c(handlers, formHandlers)

   handlers
}


tagHandler =
function(f, class = "HTMLTagHandler")
{
  class(f) = c(class, class(f))
  f
}

objectTagHandler =
function(f, class = c("HTMLObjectTagHandler", "HTMLTagHandler"))
{
  class(f) = c(class, class(f))
  f
}


ignoreTag = tagHandler(function(...) TRUE)


htmlParserTagHandlers =
  #
  # Idea here (as opposed to above) is that the caller
  # identifies what the functions are for by the class of the
  # function using tagHandler and objectTagHandler.
  # This supports the , separated notation for OBJECT handlers.
  #
  #  needs more controls for easy use yet still specify things of interest, e.g.
  #  the generic object handler function.
  
function(..., .env = globalenv(), .funs = list(..., .defaultHandlers),
          .defaultHandlers = c(htmlFormTagHandlers(), defaultObjectHandlers()),
          .addDefaults = TRUE)
{

   if(!missing(.funs) && .addDefaults)
     .funs = c(.funs, .defaultHandlers)
  
   # elongate the .funs where each element is a  function, not a list
   # so allow ( fun, fun, list(fun, fun)) to become fun, fun, fun, fun

  .funs = unlist(.funs, recursive = FALSE)

   # Find the Object handlers
  is.obj = sapply(.funs, inherits, "HTMLObjectTagHandler")
    # group the object handlers and attach them to the 
  if(any(is.obj)) {
    tmp = .funs[is.obj]
    .funs = .funs[!is.obj]
    .funs[["object"]] = htmlParserObjectHandler(tmp, .env, split = TRUE)
  }

  .funs
}


htmlParserObjectHandler =
  #
  # typeHandlers is a list of functions indexed by mime type name
  # When we encounter an OBJECT tag we look at the type parameter
  # and turn it to lower case and match it in the names of this list.
  # Then we use the function that matches.
function(typeHandlers = defaultObjectHandlers(), evalEnvir = globalenv(),
         fun = defaultObjectHandler, setEnvironment = TRUE, split = TRUE)

{

     # If split is not FALSE, then we get all the names and split them by a comma
     # or split itself it if is a string, and then create an elongated list
     # with a copy of the relevant function for each element of the split names
  if(!is.logical(split) || split) {
     types = strsplit(names(typeHandlers), if(is.logical(split)) "," else as.character(split))
     if(any(sapply(types, length)  > 1)) {
       typeHandlers = unlist(lapply(seq(along = typeHandlers),
                                     function(i) {
                                       ans = replicate(length(types[[i]]), typeHandlers[[i]])
                                       names(ans) = types[[i]]
                                       ans
                                     }),
                             recursive = FALSE)
     }
  }
  
  if(setEnvironment) {
    environment(fun) = new.env(parent = evalEnvir)
       # replacing the default value of the envir parameter in our
       # local copy of fun to be our new environment.
       #  Alternatively, in the fun function, we can
       #  grab its own environment
    if("envir" %in% names(formals(fun)))
       formals(fun)$envir = environment(fun)

    environment(fun)$typeHandlers = typeHandlers      
  }

 
  fun
}

###########################



.HTMLObjectTypeHandlers = list()

.HTMLObjectTypeHandlers [["app/x-R-command"]] =
function(tagHandler, obj, parser, envir = globalenv())
{
  txt = obj$GetContent(parser)  
  w = eval(parse (text = txt), envir)
 # insert the widget if it is a widget.
  TRUE
}


.HTMLObjectTypeHandlers [["app/x-R-widget"]] =
function(tagHandler, obj, parser, envir = globalenv())
{
  w = getCallParameter(obj, parser)

  if(is.null(w)) {
    warning("no <param name='call' value='cmd'> tag within an <OBJECT type='app/x-R-widget'> tag")
    return(FALSE)
  }
  
  e = NULL
  
  if(nchar(w) < 200 && exists(w, mode = "function", envir = envir)) {
    fun = get(w, mode = "function", envir = envir)
    switch(length(formals(fun)),
            "0" = fun(),
            "1" = fun(parser),
            "2" = fun(parser, envir))
  } else {
       ## create a new environment solely to hold the local variables
       ## and make them available to the code in the HTML node/tag
       ## that is being evaluated.
       ## And we make the parent environment the one we are handed
       ## by the general dispatch mechanism for handling OBJECT tags.
    env = new.env(parent = envir)
    env$parser = parser
    e = eval(parse(text = w), envir = env)
  }
 
 
  if(!is.null(e) && isWxWidget(e))   {
    w = obj$GetParam("width")
    h = obj$GetParam("height")
    if(w != "" && h != "") {
      w = as.integer(ifelse(w == "", -1, w))
      h = as.integer(ifelse(w == "", -1, h))      
      wxWindow_SetSize(e, w, h)
    }
    insertEmbeddedComponent(e, parser)
  }
  else {
    warning("Didn't create widget", w, " in app/x-R-widget <OBJECT> handler\n")
    return(FALSE)
  }

  TRUE
}


.HTMLObjectTypeHandlers [["app/x-R-radiobutton"]] =
function(tagHandler, obj, parser, envir = globalenv())
{
  label = getCallParameter(obj, parser, values = "label")
  btn = wxRadioButton(parser$GetWindow(), wxID_ANY, label= label)
  insertEmbeddedComponent(btn, parser)
  
  cb = getCallbackParam(obj, parser)  
  if(!is.null(cb))  {
        # add some code to check these things exist.
      if(!exists(cb$eventId) || !exists(cb$callback, mode = "function"))
          stop("either/both the event identifier ", cb$eventId, " or the callback ", cb$callback, " don't identify an R object")

      btn$AddCallback(get(cb$eventId), get(cb$callback, mode = "function"))
  }

  TRUE
}

getCallbackParam =
  #
  # Get the contents of an HTML node of the form
  #  <callback id="">functionName</callback>
  # 
  #
function(tag, parser = NULL, 
          nodeName = "CALLBACK", envir = globalenv())
{
  el = wxHtmlTag_GetChildren(tag, FALSE)

  while(!is.null(el)) {
    tagName = wxHtmlTag_GetName(el)
    if(tagName == toupper(nodeName)) {
       
       id = wxHtmlTag_GetParam(el, "id")
       txt = wxHtmlTag_GetParam(el, "value")
       if(is.null(txt) || is.na(txt) || txt == "")
          txt = el$GetContent(parser)
       
       return(list(eventId = id, callback = txt))
    }
    
    el = wxHtmlTag_GetNextSibling(el)
  }

  return(NULL)
}  


getCallParameter =
  #
  # Fetch the value from the <param name="call" value="">
  # HTML element that is the child of the given tag.
  #
function(tag, parser = NULL, envir = globalenv(),
          nodeName = "PARAM", param = "name", values = c("init", "call"))
{
  el = wxHtmlTag_GetChildren(tag, FALSE)

  while(!is.null(el)) {
    tagName = wxHtmlTag_GetName(el)
    if(tagName == nodeName && wxHtmlTag_GetParam(el, param) %in% values) {
       txt = wxHtmlTag_GetParam(el, "value")
       if(is.na(txt) || txt == "") {
            # get the body of the PARAM node.
         txt = el$GetContent(parser)
       }
       return(txt)
    }
    
    el = wxHtmlTag_GetNextSibling(el)
  }

  return(NULL)
}  

defaultObjectHandlers =
function(..., .els = list(...), .prefix = "app/x-R-")
{
  ans = .HTMLObjectTypeHandlers
  if(length(.els))  {
     if(length(names(.els)) > 0 && length(.prefix) > 0 )
        names(.els) = paste(.prefix, names(.els), sep = "")
     ans[names(.els)] = .els
   }

  lapply(ans, objectTagHandler)
}  



  #
  # called when an HTML widget needs to act on an
  # <OBJECT> tag for an embedded object.
  # This returns TRUE or FALSE depending on whether it understood
  # and processed the request or not.
  # We can have built-in types or just evaluate the script
  # in the init parameter
  # <PARAM name="init" value="script but must contain ; between expressions">
  #
  #
  #  envir defaults to the environment of this very function. Typically its 
  #  environment is set explicitly before being registered with the HTML parser
  #  as the HandleTag method for a RwxHtmlWinTagHandler which actually invokes it.
  #
defaultObjectHandler =
  ##
  # html is the htmlTagHandler.
 function(html, obj, parser, envir = environment(sys.function()), asIs = FALSE)
 {
     type <- wxHtmlTag_GetParam(obj, "type")
      
      if(type %in% names(typeHandlers)) 
         f = typeHandlers[[type]]
      else
         f = typeHandlers[["app/x-R-command"]]

      if(is.null(f)) {
        warning("no OBJECT handler for ", type)
        return(FALSE)
      }

      typeSpecificHandler = f
      if(length(formals(f)) > 3)  # pass the environment down
         val = typeSpecificHandler(html, obj, parser, envir)         
      else       # otherwise treat this as a regular wxHtmlTagHandler HandleTag method.
         val = typeSpecificHandler(html, obj, parser)

      if(asIs)
        return(val)

      if(isWxWidget(val)) 
         insertEmbeddedComponent(val, parser)
     
      if(is.logical(val))
        return(val)
      else
        return(TRUE)
 }



wxHtmlTagHandler_ParseInner =
function(this, tag)
{
   .Call("R_RwxHtmlWinTagHandler_ParseInner", this, tag) 
}
