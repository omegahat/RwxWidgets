wxMenuItem =
function(parentMenu = NULl, id = wxID_SEPARATOR, text = "", helpString = "", kind = wxITEM_NORMAL, subMenu = NULL)
  .Call("R_wxMenuItem_new", parentMenu, as.integer(id), as.character(text), as.character(helpString),
                            as.integer(kind), subMenu)


wxMenuItem_GetId =
function(this)
{
  .Call("R_wxMenuItem_GetId", this)
}

wxMenuItem_GetText =
function(this)
{
  .Call("R_wxMenuItem_GetText", this)
}

wxMenuItem_SetBitmap =
function(this, bmp)
{
  .Call("R_wxMenuItem_SetBitmap", this, bmp)
}  
