#
# Taken originally from the gtkhtml.S file in RGtkViewers.
# This is intended to provide an extensible collection of 
# handlers for processing HTML tags that are associated with
# embedded "cells" or components within the document, e.g.
# sliders, graphics devices, data grids, other HTML viewers,
# 


.HTMLObjectTypeHandlers = list()

.HTMLObjectTypeHandlers[["app/x-color"]] =
  function(html, obj, envir = globalenv()) {
         # Create a color selection dialog.
       obj$Add(gtkColorSelection())
  }

.HTMLObjectTypeHandlers[["app/x-button"]] =
  function(html, obj, envir = globalenv()) {
        # Create a button and a simple callback.
       label <- obj$GetParameter("label")
       if(label == "")
         label <- "Embedded Widget"
       btn <- gtkButton(label)
       obj$Add(btn)
       val = obj$GetParameter("clicked")
       if(!is.null(val) && val != "") {
         f = eval(parse(text = val), envir = envir)
         if(is.function(f))
           btn$AddCallback("clicked", f)
         else {
           btn$AddCallback("clicked", f, data = envir)
         }
       }
       btn
   }

.HTMLObjectTypeHandlers[["app/x-slider"]] =
  function(html, obj, envir = globalenv()) {
        # Create a slider, using values from the parameters for the min, max and value
        # if provided.
       mn <- obj$GetParameter("min")
       mn <- ifelse(mn != "", as.numeric(mn), 0)
       mx <- obj$GetParameter("max")
       mx <- ifelse(mn != "", as.numeric(mx), 0)
       val <- obj$GetParameter("value")
       val <- ifelse(val != "", as.numeric(val), mn)


       adj <- gtkAdjustment(val, mn, mx, .1, 1, 1)
       
       mn <- obj$GetParameter("vertical")
       if(mn != "" && as.logical("vertical"))
          scale <- gtkVScale(adj)
       else
          scale <- gtkHScale(adj)         


       obj$Add(scale)
       
       val <- obj$GetParameter("value-changed")
       if(!is.null(val)) {
         f <- eval(parse(text = val), envir = envir)
         if(!is.null(f)) {
          if(is.function(f))
            adj$AddCallback("value-changed", f)
          else {
               # Make the evaluation of the call/expression occur in this active environment.
            adj$AddCallback("value-changed", f, envir)
          }
        }
       }

       adj
  }

.HTMLObjectTypeHandlers[["app/x-R-device"]] =
function(html, obj, envir = globalenv()) {
       require(gtkDevice)
       dev <- gtkDrawingArea()
       asGtkDevice(dev)
       dev$Show()
       box <- gtkHBox(TRUE,10)
       box$PackStart(dev)
       init <- obj$GetParameter("init")
       if(!is.null(init)) {
         eval(parse(text = init), envir = envir)          
       }
       obj$Add(box)
       return(dev.cur())
}

.HTMLObjectTypeHandlers[["app/x-R-generic"]] =
function(html, obj, envir = globalenv()) {
        # Check if there is an init paramter and if so,
        # attempt to evaluate it as an S command/expression.
       init <- obj$GetParameter("init")       
       if(init != "") {
         val <-  eval(parse(text = init), envir = envir)
          # If the result is a GtkWidget, then add it to the
          # embedded widget container.
         add <- as.logical(obj$GetParameter("addWidget"))
         if(inherits(val, "GtkWidget") && (is.na(add) || add == TRUE)) {
           obj$Add(val)
           val$Reparent(obj)
           val
         } else if(is.function(val)) {
           val(html, obj)
         }
       } else {
           # say that we did't handle this.
         return(FALSE)
       }
}

.HTMLObjectTypeHandlers[["app/x-R-command"]] =
function(html, obj, envir = globalenv()) {
   init <- obj$GetParameter("init")
   eval(parse(text = init), envir = envir)
   TRUE
}


.HTMLObjectTypeHandlers[["app/x-R-textentry"]] =
function(html, obj, envir = globalenv())
{
  w = obj$GetParameter("size")
  w = ifelse(w == "", "10", as.numeric(w))
  e = gtkEntry(w)

  w = obj$GetParameter("value")
  e$SetText(w)

  obj$Add(e)
  
  e
}

.HTMLObjectTypeHandlers[["app/x-R-widget"]] =
function(html, obj, envir = globalenv())
{
  w = obj$GetParameter("call")

  e = NULL  
  if(exists(w, mode="function")) {
    e = get(w, mode="function")()
  } else {
    e = eval(parse(text = w), envir = envir)
  }

  if(!is.null(e))
     obj$Add(e)
  else
    cat("Didn't create widget", w, "\n")
  e
}



.HTMLObjectTypeHandlers[["app/x-R-label"]] =
function(html, obj, envir = globalenv())
{
  w = obj$GetParameter("call")

  e = NULL
  if(w == "") {
    e = gtkLabel("")
  } else if(exists(w, mode="function")) {
    e = get(w, mode="function")()
  } else {
    e = eval(parse(text = w), envir = envir)
  }

  if(is.null(e))
    stop("Didn't create widget ", w, "\n") 

  w = obj$GetParameter("label")
  if(w == "") {
     w = obj$GetParameter("size")
     if(w != "")
      w = rep("", as.integer(w))
   }

  if(w != "")
     e$SetText(w)
  
  obj$Add(e)

  e
}

addMIMEObjectHandler <-
function(name, handler)
{
  .HTMLObjectTypeHandlers[[name]] <<- handler

  invisible(.HTMLObjectTypeHandlers)
}  

embeddedObjectHandler <-
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
function(html, obj, envir = globalenv(), asIs = FALSE)
{
     type <- obj[["Type"]]

      
      if(type %in% names(.HTMLObjectTypeHandlers)) 
         f = .HTMLObjectTypeHandlers[[type]]
       else
         f = .HTMLObjectTypeHandlers[["app/x-R-command"]]

      val = f(html, obj, envir)

      if(asIs)
        return(val)
     
      if(is.logical(val))
        return(val)
      else
        return(TRUE)
}
