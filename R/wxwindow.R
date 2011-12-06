setGeneric("wxWindow_SetSize", function(this, x, y, width, height, sizeFlags = integer())
                       standardGeneric("wxWindow_SetSize"))

setMethod("wxWindow_SetSize",
          c("wxWindow", "numeric", "numeric", "missing", "missing", "missing"),
          function(this, x, y, width, height, sizeFlags = numeric()) {
            .Call("R_wxWindow_SetSize_int_int", this, as.integer(x), as.integer(y))
          })

setMethod("wxWindow_SetSize",
          c("wxWindow", "numeric", "numeric", "numeric", "numeric"),
          function(this, x, y, width, height, sizeFlags = numeric()) {
            .Call("R_wxWindow_SetSize_int_int_int_int_int", this, as.integer(x), as.integer(y), as.integer(width), as.integer(height),as.integer(sizeFlags))
          })


wxWindow_GetSize =
function(win)
{
  .Call("R_wxWindow_GetSize", win)
}


wxWindow_Raise =
function(win)
{
  .Call("R_wxWindow_Raise", win)
}



wxWindow_GetSizer =
function(win)
{
  ans = .Call("R_wxWindow_GetSizer", win)
  new(getWxClassInfo(ans)[1], ans)
}





wxWindow_Show = function(this, show = TRUE)
{
 .Call("R_wxWindow_Show", this, as.logical(show))
}


wxWindow_SetSizer = function(this, sizer, deleteOld = TRUE)
{
  .Call("R_wxWindow_SetSizer", this, sizer, as.logical(deleteOld))
}

wxWindow_SetSizerAndFit = function(this, sizer, deleteOld = TRUE)
{
  .Call("R_wxWindow_SetSizerAndFit", this, sizer, as.logical(deleteOld))
}  


wxWindow_FindWindowByName =
function(name, parent = NULL)
{
  .Call("R_wxWindow_FindWindowByName", as.character(name), parent)
}
attr(wxWindow_FindWindowByName, "staticMethod") <- TRUE

wxWindow_FindWindowByLabel =
function(label, parent = NULL)
{
  .Call("R_wxWindow_FindWindowByLabel", as.character(label), parent)
}
attr(wxWindow_FindWindowByLabel, "staticMethod") <- TRUE

wxWindow_FindWindowById =
function(id, parent = NULL)
{
  .Call("R_wxWindow_FindWindowById", as.numeric(id), parent)
}  
attr(wxWindow_FindWindowById, "staticMethod") <- TRUE


wxWindow_FindWindow =
function(this, id)
{
  .Call("R_wxWindow_FindWindow", this, as.numeric(id))
}  


wxWindow_GetChildren =
function(this)   
{  
  ans = .Call("R_wxWindow_GetChildren", this)
  ans
}


# Make a method.
wxWindow_SetToolTip = function(this, text)
{
  .Call("R_wxWindow_SetToolTip_wxString", this, as.character(text))
}

wxWindow_Destroy =
function(this)
{
  .Call("R_wxWindow_Destroy", this)
}


wxWindow_SetDropTarget =
function(this, target)
{
  .Call("R_wxWindow_SetDropTarget", this, target)
}


wxWindow_SetBackgroundColour =
function(this, colour = NULL) #XXX
{
  .Call("R_wxWindow_SetBackgroundColour", this, colour)
}


  
setGeneric("wxWindow_PopupMenu",
           function(this, menu, x, y)
             standardGeneric("wxWindow_PopupMenu"))

setMethod("wxWindow_PopupMenu",
           c("wxWindow", "wxMenu", "numeric", "numeric"),
           function(this, menu, x, y)
             .Call("R_wxWindow_PopupMenu_wxMenu_int_int", this, menu, as.integer(x), as.integer(y)))

setMethod("wxWindow_PopupMenu",
           c("wxWindow", "wxMenu", "numeric", "missing"),
           function(this, menu, x, y) {
              length(x) = 2
              wxWindow_PopupMenu(this, menu, x[1], x[2])
           })

setMethod("wxWindow_PopupMenu",
           c("wxWindow", "wxMenu", "wxPoint"),
           function(this, menu, x, y)
             .Call("R_wxWindow_PopupMenu_wxMenu_wxPoint", this, menu, x))



wxWindow_Reparent =
function(this, parent)
  .Call("R_wxWindow_Reparent", this, parent)

wxWindow_Enable =
function(this, enable = TRUE)
{
  .Call("R_wxWindow_Enable", this, as.logical(enable))
}

