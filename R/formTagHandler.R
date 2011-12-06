setClass("HTMLForm",
          representation(name = "character",
                         components = "list",
                         hidden = "list",
                         parameters = "character",                         
                         initialValues = "list",
                         values = "list" # may not need this anymore as we pick up the values dynamically, i.e. at submit time
                         ))

setClass("PostForm", contains = "HTMLForm")
setClass("GetForm", contains = "HTMLForm")


CheckedValues = c("true", "TRUE", "True", "yes", "1", "")

wxHtmlTag_GetParamNumber = getParamNumber = 
function(tag, name, defaultValue, Coerce = as.numeric)
{
  if(!tag$HasParam(name))
    return(defaultValue)
  
  val = tag$GetParam(name)
  if(val == "")
      val = defaultValue
   else
      val = Coerce(val)
}


initializeHTMLForm =
function(values, components)
{
      grps = components[ sapply(components, inherits, "RadioButtonGroup") ]
      if(length(grps)) {
        sapply(names(grps),
               function(id) {
                 # cat("Setting", id, "to", values[[id]], "\n")
                 grps[[id]]$set( values[[ id ]] ) 
               })
      }

      TRUE
}



# text/textarea password checkbox radio submit
# image reset button hidden file
# select/option
htmlFormTagHandlers =
  #
  # We can process multiple forms within this function
  # storing the details of each form in an HTMLForm object.
  # Each HTMLForm object has information about all of the widgets
function(submit = callbacks[["submit"]], callbacks = list(),
          setEnvironment = FALSE)
{
    # Multiple form objects
  forms <- list()
  
   # details within a particular form
  components <- list()
  hidden <- list()
  initialValues <- list()
  values <- list()

   # To reset/reinitialize the form
   # we need to know the name-value pairs
   # and match them to the relevant components.
   # Buttons don't need to be reset.
   # Text fields do.

   # To submit a form, we need to get the current values.
   # These can be stored by catching selection events and
   # storing the values as they are set. For text fields this is
   # not necessarily a good idea.  Instead, we can query their values
   # at submit-time.  And we can do that for essentially all the
   # components. If we store the components by name

   # If we store wxWindow elements as values, then we know to harvest their
   # current contents when submitting.
   # wxTextCtrl and wxFileDialog entries are such examples.
   # For radio buttons, checkboxes, "menus" via the select/option combinations,
   # we can trap the events that reset these and set the value appropriately
   # (for checkboxes or multiple select/option menus allowing multiple values)
   #
   # In a callback for one of these "instant" value setting components,
   # we need the name/index of the form, the name of the component and the
   # value itself.
  
  textarea = function(handler, tag, parser, type = tolower(wxHtmlTag_GetParam(tag, "type"))) {

     win = wxHtmlParser_GetWindow(parser)

     rows = getParamNumber(tag, "rows", 1)
     cols = getParamNumber(tag, "cols", 35)

     size = c(cols * parser$GetCharWidth(), rows * parser$GetCharHeight())
     
      # Now set the size for the rows and columns dealing with fonts, etc.

     style = 0
     if(type == "password") {
        style = wxTE_PASSWORD
        size[2] = 2* size[2]
      }

     if(rows > 1)
       style = c(style, wxTE_MULTILINE)
     
     w = wxTextCtrl(win, style = style, size = size)

     if(tag$GetParam("readonly") != "" || tag$GetParam("disabled") != "") 
          wxText_SetEditable(w, FALSE)

     name = wxHtmlTag_GetParam(tag, "name")
      # 
     components[[ name ]] <<- w
     values[[ name ]]  <<- w
       # get initial value content
     if(type != "password") {
       txt = tag$GetContent(parser)
     } else
       txt = tag$GetParam("value")
     
     w$SetValue(txt)
     initialValues[[ name ]] <<- txt
     insertEmbeddedComponent(w, parser)
     
     TRUE
  }

  options <- list()
  option =
    function(handler, tag, parser)
    {
      # we need the sub-text.
      text = tag$GetContent(parser)
        
      value = ifelse(tag$HasParam("value"), tag$GetParam("value"), text)
      selected = ifelse(tag$HasParam("selected"), tag$GetParam("selected") %in% CheckedValues, FALSE)
      
      options[[length(options) + 1]] <<- list(value = value, selected = selected, text = text)

      FALSE
    }
  
  select =
    function(handler, tag, parser) {
      options <<- list() 
      wxHtmlTagHandler_ParseInner(handler, tag)

      win = wxHtmlParser_GetWindow(parser)
      style = ifelse(tag$HasParam("selected"), wxLB_MULTIPLE, 0) # is selected the correct attribute XXX
      #XXX get the style, size and choice of wxListBox or wxChoiceBox right.
#      w = wxListBox(win, wxID_ANY, choices = sapply(options, function(x) x[["text"]]), style = style)
      w = wxChoice(win, wxID_ANY, choices = sapply(options, function(x) x[["text"]]), style = style)
      insertEmbeddedComponent(w, parser)      

      name = tag$GetParam("name")
      components[[name ]] <<- structure(list(widget = w, options = options,
                                             getSelections = function(this) {
                                                 idx = this$widget$GetSelections() + 1
                                                 sapply(this$options[idx], function(x) x[["value"]])
                                             }),
                                        class = "HTMLListBox")
        # indices of the selected elements.
      initialValues[[ name ]] <<- which(sapply(options, function(x) x[["selected"]]))
      
      FALSE # TRUE
    }

 
  
  form = function(handler, tag, parser) {

    params = processHTMLParameters(tag)

    wxHtmlTagHandler_ParseInner(handler, tag)    

    currentForm <- new("HTMLForm", parameters = params)    
    currentForm@components <- components
    currentForm@hidden <- hidden
    currentForm@initialValues <- initialValues

    initializeHTMLForm(initialValues, components)    
    forms <<- append(forms, currentForm)

    .reset()
    
    TRUE
  }

  
  .reset =
    # This resets the parsing of the form, not the values within a form.
    # that is done by resetForm
    function() {
     
      components <<- list() # reset
      hidden <<- list()
      initialValues <<- list()
      values <<- list()

      TRUE
    }


  resetForm =
    function(formNum) {
      form = forms[[ formNum ]]

      sapply(names(form@components),
              function(id) 
                setValue(form@components[[id]], form@initialValues[[id]], id)
            )
      # print(form@initialValues) #XXX finish off.
    }

  setValue =
    function(el, val, id) {
      k = class(el)
      switch(k,
             RwxButton = FALSE,
             RadioButtonGroup = el$set(val),
             list = sapply(names(el), function(id) el[[id]]$SetValue(id %in% val)), # check boxes
             wxTextCtrl = el$SetValue(val),
             HTMLListBox = wxListBox_SetSelections(el$widget, val),
                          #XXX this - el$widget$SetSelections(val) - doesn't work because getWxClassInfo(el$widget) skips over wxControlWithItems
              cat("Didn't handle", k, "in setValue\n")             
            )
    }

  getValue =
    function(x) {
       k = class(x)

       switch(k,
              RwxButton = character(),
              RadioButtonGroup = x$getValue(),
              list = { tmp = sapply(x, getValue); names(x)[tmp]},
              wxTextCtrl = x$GetValue(),
              wxCheckBox = x$GetValue(),
              wxFileDialog = x$GetPath(),
              HTMLListBox = x$getSelections(x),
              cat("Didn't handle", k, "in getValue\n")
             )
    }

  .submit =
    function(formNum, submit = NULL)
    {
      form = forms[[formNum]]
      vals = c(lapply(form@components,  getValue), form@hidden)

      #XXX
      if(is.function(submit))
        return(submit(vals, form@parameters, form))
      else
      if("submit" %in% names(callbacks))
        callbacks$submit(vals, form@parameters, form)
      else if("onsubmit" %in% names(form@parameters)) {
          e = parse(text = form@parameters["onsubmit"])
          if(length(e) == 0)
            stop("onsubmit attribute not properly understood ", form@parameters["onsubmit"])

          if(class(e[[1]]) == "name") {
            f = get(e[[1]])
            f(vals, form@parameters, form)
          } else if(is.call(e[[1]]) && is(e[[1]][[1]], "name") && as.character(e[[1]][[1]]) == "function") {
            eval(e)(vals, form@parameters, form)
          } else {
            #XXX check this.
            e = substitute(e, list(form = form, params = form@parameters, values  = vals))
            eval(e)
          }
      } else
        print(vals)
    }  


  
  input = function(handler, tag, parser) {

     type = tolower(wxHtmlTag_GetParam(tag, "type"))
     name = wxHtmlTag_GetParam(tag, "name")              
     value = wxHtmlTag_GetParam(tag, "value")
     
     win = wxHtmlParser_GetWindow(parser)
     w = NULL
     
     if(type %in% c("text", "password"))
        return(textarea(handler, tag, parser, type))
     else if(type %in% c("submit", "button", "reset")) {
       fun = NULL
       if(value == "" && type == "submit") {
         value = "Submit"
       }
       
         # put correct callback.       
       w = wxButton(win, wxID_ANY, value)

       w$AddCallback(wxEVT_COMMAND_BUTTON_CLICKED,
                       function(ev, formId, type) {
                            cat(type, "'ing form", formId, "\n")
                            if(type == "submit")
                              .submit(formId)
                            else if(type == "reset")
                              resetForm(formId)
                       }, length(forms) + 1, type)
     } else if (type == "radio") {
              # need to group the radio buttons by name and then ensure that we have
              # mutually exclusive settings within this group and not across all groups.
              #XXX w = wxRadioButton(win, wxID_ANY, "") # , style = c(wxRB_GROUP, wxRB_SINGLE))
       w = wxCheckBox(win, wxID_ANY, "")
              # Find the handlers for this group and if there is none, create one and assign it.
       tmp  = components[[ name ]]
       if(is.null(tmp)) {
         tmp = radioButtonGroup()
         components[[ name ]] <<- tmp
       }
       i = tmp$add(w, value)

       
         # Add a callback for selecting this.
       checked = tag$HasParam("checked") && wxHtmlTag_GetParam(tag, "checked") %in% CheckedValues
       w$SetValue(checked)
       if(checked) 
         initialValues[[ name ]] <<- value
       
       name = ""  # don't assign this to the components[[ ]] as we have added the grp there.
       
     } else if (type == "checkbox") {
       w = wxCheckBox(win, wxID_ANY, "")
       checked = tag$HasParam("checked") && wxHtmlTag_GetParam(tag, "checked") %in% CheckedValues
       w$SetValue(checked)
       if(checked) 
         initialValues[[ name ]] <<- c(initialValues[[ name ]], value)
       #XXX add this to the components under name but then index by value within that list.                 
     } else if (type == "file") {
       w = wxButton(win, wxID_ANY, "Browse")
       w$AddCallback(wxEVT_COMMAND_BUTTON_CLICKED,
                     function(ev, name, formId) {
                       if(!(name %in% names(components)) ||
                            is.null(dlg <- components[[name]])) {
                         dlg = wxFileDialog(win)
                                        # Add callback to trap destroy by clicking on the frame controls and set components[[name]] = NULL
                         forms[[formId]]@components [[ name ]] <<- dlg
                       }
                       if(dlg$ShowModal() != wxID_CANCEL)
                         values[[ name ]] <<- dlg$GetPath()
                     }, name, length(forms) + 1)

       name = "" # don't add w  to the list of components.
     } else if(type == "hidden") {
        hidden[[ name ]] <<- value
     } else
        return(FALSE)

     if(!is.null(w))
       insertEmbeddedComponent(w, parser)
     
     if(name == "" || is.null(w))
       return(FALSE)

     
       # Put the component into the R collection of components for this form.
     if(name %in% names(components)) {
        tmp = components[[name]]
        if(!is.list(tmp))
          tmp = list(tmp)
        if(is(w, "wxButton"))
          warning("(at least) two buttons with the same name ", name, " or a button with the same name as another element")
        components[[name]] <<- append(tmp, w)
     } else if(is(w, "wxCheckBox"))
        components[[ name ]] <<- list(w)
     else
       components[[ name ]] <<- w

     if(is.na(value) || value == "")
       value = name
     if(is.list(components[[name]]))
       names(components[[name]])[length(components[[name]])] <<- value     

     FALSE
  }


  ans = list(textarea = textarea,
             input = input,
             form = form,
             option = option,
             select = select,
             .submit = .submit,
             .forms = function() forms
            )

  if(setEnvironment) 
    callbacks <- lapply(callbacks, function(f) {environment(f) <- environment(textarea); f})

  ans[names(callbacks)] = callbacks

  ans
}



insertEmbeddedComponent =
function(w, parser,
         container = wxHtmlParser_GetContainer(parser))
{
  widgetCell = wxHtmlWidgetCell_new(w)  
  wxHtmlContainerCell_InsertCell(container, widgetCell)
  widgetCell
}  

######################################################################

radioButtonGroup =
  #
  # This function creates a set of handlers to manage
  # checkboxes or radio buttons that want to behave
  # as if they are mutually exclusive but which we have
  # to manage ourselves.
  #
  # After creating an checkbox or radio button, add it to this group
  # using the add() function giving the wxObject and optionally a name.
  # 
  # A callback is then attached to that wxObject and when it is set by the user
  # we update the state in this group, ensuring that the other elements are
  # unset.
  #
  # callback is a function that is called when an entry is set
  #  and is called with two arguments giving the element being set
  #  and its "name" within this group.  When calling set() to explicitly
  #  set the current value, e.g. at the end of the initialization,
  #  one may not want the callback invoked. Use doCallback = FALSE for this.
  #
  #
  #
  
function(callback = NULL, ..., elements = list(), currentValue = NA)
{

 add = function(el, name = NA,
                 eventType = if(is(el, "wxCheckBox")) wxEVT_COMMAND_CHECKBOX_CLICKED else wxEVT_COMMAND_RADIOBUTTON_SELECTED) {
   
   elements[[ length(elements) + 1 ]] <<- el
   i = length(elements)                    
   if(is.na(name))
      name = as.character(i)
     
   names(elements)[length(elements)] <<- name

   el$AddCallback(eventType, function(ev, id) {
                               set(id)
                             }, i)

   i
 }

 set = function(el, doCallback = TRUE) {

  
     if(is.character(el))
       el = match(el, names(elements))

     if(is(el, "wxObject"))
       # find the index.
       stop("Not handled yet")

     if(doCallback && !is.null(callback))
       callback(elements[[el]], names(elements)[el], ...) # where do these ... come from ?
     
     elements[[el]]$SetValue(TRUE)
     currentValue <<- names(elements)[el]
     
     sapply(elements[-el], function(x, val) x$SetValue(val), FALSE)
 }

 remove = function(el) {
     if(is.character(el))
       el = match(el, names(elements))

    # Need to remove the callback also so need the handle.

     elements <<- elements[ - el]
     TRUE
 }

 getSelected =
   # Find out which element is currently the selected one.
   function() {
     for(i in seq(along = elements)) {
       if(elements[[i]]$GetValue())
         return(i)
     }
  }

 structure(list(add = add, set = set, remove = remove,
                getSelected = getSelected,
                getValue = function() currentValue,
                elements = function(i) if(missing(i))
                                            elements
                                       else
                                            elements[[i]]
               ),
           class = "RadioButtonGroup")
  
}  


######################################################################

processHTMLParameters =
function(tag) {
    params = wxHtmlTag_GetAllParams(tag, FALSE)
    els = strsplit(params, '"')[[1]]
    if(length(els) == 0)
      return("")
    i = seq(2, length(els), by = 2)
    params = els[i]
    names(params) = gsub("=$", "", els[i-1])
    params
}
