wxListCtrl =
function(parent, id = wxID_ANY, pos = wxDefaultPosition, size = wxDefaultSize,
          style = wxLC_ICON, validator = wxDefaultValidator, name = "wxListCtrl")
{
  if(is(pos, "numeric"))
    pos = as.integer(pos)
  if(is(size, "numeric"))
    size = as.integer(size)
  style = bitlist(style)

  .Call("R_wxListCtrl_new", parent, as.integer(id), pos, size, style, validator, as.character(name))
}  

setGeneric("wxListCtrl_InsertItem",
            function(this, index, label, imageIndex)
                   standardGeneric("wxListCtrl_InsertItem"))

setMethod("wxListCtrl_InsertItem",
           c("wxListCtrl",  "numeric", "character", "missing"),
          function(this, index, label, imageIndex)  {
            .Call("R_wxListCtrl_InsertItem_long_wxString", this, as.numeric(index), as.character(label))
          })

setMethod("wxListCtrl_InsertItem",
           c("wxListCtrl",  "numeric", "numeric"),
          function(this, index, label, imageIndex)  {
            .Call("R_wxListCtrl_InsertItem_long_int", this, as.numeric(index), as.character(label))
          })

setMethod("wxListCtrl_InsertItem",
           c("wxListCtrl",  "numeric", "character", "numeric"),
          function(this, index, label, imageIndex)  {
            .Call("R_wxListCtrl_InsertItem_long_wxString_int", this, as.numeric(index), as.character(label), as.integer(imageIndex))
          })


setGeneric("wxListCtrl_SetItem",
            function(this, index, col, label, imageId = -1)
                   standardGeneric("wxListCtrl_SetItem"))

setMethod("wxListCtrl_SetItem",
          c("wxListCtrl",  "numeric", "numeric", "character"), 
          function(this, index, col, label, imageId = -1)  {
            .Call("R_wxListCtrl_SetItem_long_int_wxString_int",
                        this, as.numeric(index), as.integer(col), as.character(label), as.integer(imageId))
          })

setMethod("wxListCtrl_SetItem",
          c("wxListCtrl",  "wxListItem"),
          function(this, index, col, label, imageId = -1)  {
            stop("Not implemented yet")
            .Call("R_wxListCtrl_InsertItem_wxListItem", this, index)
          })


wxListCtrl_SetImageList = 
function(this, imageList, which)
{
  .Call("R_wxListCtrl_SetImageList", this, imageList, as.integer(which))
}

wxListCtrl_AssignImageList = 
function(this, imageList, which)
{
  .Call("R_wxListCtrl_SetImageList", this, imageList, as.integer(which))
}


wxListCtrl_InsertColumn = 
function(this, col, heading, format = wxLIST_FORMAT_LEFT, width = -1)
{
  format = bitlist(format)
  .Call("R_wxListCtrl_InsertColumn_long_wxString_int_int",
          this, as.numeric(col), as.character(heading), as.integer(format), as.integer(width))
}


wxListCtrl_SetColumnWidth =
function(this, col, width)
{
  .Call("R_wxListCtrl_SetColumnWidth", this, as.integer(col), as.integer(width))
}

wxListCtrl_GetItem =
function(this, id)
{
  .Call("R_wxListCtrl_GetItem", this, as.numeric(id))
}

wxListCtrl_ClearAll =
function(this)
{
  .Call("R_wxListCtrl_ClearAll", this)
}

wxListCtrl_SetItemImage =
function(this, item, image)
{  
  .Call("R_wxListCtrl_SetColumnWidth", this, as.numeric(item), as.integer(image))
}

# SetItem SetItemBackground.
