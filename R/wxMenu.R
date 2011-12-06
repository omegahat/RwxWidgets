wxMenu =
function(title = "", style = 0)  
  .Call("R_wxMenu_new", as.character(title), as.numeric(style))

wxMenu_AppendSeparator =
function(this)  
  .Call("R_wxMenu_AppendSeparator", this)

wxMenu_AppendRadioItem =
function(this, id, item, helpString = "")  
  .Call("R_wxMenu_AppendRadioItem", this, as.integer(id), as.character(item), as.character(helpString))

wxMenu_AppendCheckItem =
function(this, id, item, helpString = "")  
  .Call("R_wxMenu_AppendCheckItem", this, as.integer(id), as.character(item), as.character(helpString))

wxMenu_Check =
function(this, id, check)  
  .Call("R_wxMenu_Check", this, as.integer(id), as.logical(check))

wxMenu_Enable =
function(this, id, enable)  
  .Call("R_wxMenu_Enable", this, as.integer(id), as.logical(enable))


setGeneric("wxMenu_Delete", function(this, item) standardGeneric("wxMenu_Delete"))


setMethod("wxMenu_Delete", "wxMenuItem",
            function(this, item)
              .Call("R_wxMenu_Delete_wxMenuItem", this, item))


setMethod("wxMenu_Delete", "numeric",
            function(this, item)
              .Call("R_wxMenu_Delete_int", this, as.integer(item)))


setGeneric("wxMenu_Append", function(this, id, item, helpString = "", kind = wxITEM_NORMAL) standardGeneric("wxMenu_Append"))

setMethod("wxMenu_Append", c("wxMenu", "numeric", "character"), 
           function(this, id, item, helpString = "", kind = wxITEM_NORMAL)
             .Call("R_wxMenu_Append_int_wxString_wxString_wxItemKind",
                       this, as.integer(id), as.character(item), as.character(helpString), as.integer(kind)))


setMethod("wxMenu_Append", c("wxMenu", "numeric", "character", "wxMenu"), 
           function(this, id, item, helpString = "", kind = wxITEM_NORMAL)
             .Call("R_wxMenu_Append_int_wxString_wxMenu_wxString",
                       this, as.integer(id), as.character(item), helpString, as.character(kind)))

setMethod("wxMenu_Append", c("wxMenu", "wxMenuItem"),
           function(this, id, item, helpString = "", kind = wxITEM_NORMAL)
             .Call("R_wxMenu_Append_wxMenuItem", this, id))

