wxIcon =
function(name, type, desiredWidth = -1, desiredHeight = -1)
{
  type = as(type, "wxBitmapType")
  .Call("R_wxIcon_new_wxString_wxBitmapType_int_int", as.character(name), type, as.integer(desiredWidth), as.integer(desiredHeight))
}

wxIcon_LoadFile =
function(this, name, type)
{
  type = as(type, "wxBitmapType")
  .Call("R_wxIcon_LoadFile", as.character(name), type)
}

wxIcon_Ok =
function(this)
{
 .Call("R_wxIcon_Ok", this)  
}
