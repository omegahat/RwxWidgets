wxNotebook =
function(parent, id = wxID_ANY, pos = wxDefaultPosition, size = wxDefaultSize,
          style = 0, name = "notebook")
{
  if(is(pos, "numeric"))
    pos = as.integer(pos)
  if(is(size, "numeric"))
    size = as.integer(size)
  
  .Call("R_wxNotebook_new", parent, as.integer(id), pos, size, as.numeric(style), as.character(name))
}  

wxNotebook_GetCurrentPage =
function(this)
{
  .Call("R_wxNotebook_GetCurrentPage", this)
}


wxNotebook_GetImageList =
function(this)
{
  .Call("R_wxNotebook_GetImageList", this)
}  



wxNotebook_DeleteAllPages =
function(this)
{
  .Call("R_wxNotebook_DeleteAllPages", this)
}  


wxNotebook_GetPageCount =
function(this)
{
  .Call("R_wxNotebook_GetPageCount", this)
}  


wxNotebook_GetRowCount =
function(this)
{
  .Call("R_wxNotebook_GetRowCount", this)
}  


wxNotebook_GetSelection =
function(this)
{
  .Call("R_wxNotebook_GetSelection", this)
}  

wxNotebook_RemovePage =
function(this)
{
  .Call("R_wxNotebook_RemovePage", this)
}  

wxNotebook_DeletePage =
function(this)
{
  .Call("R_wxNotebook_DeletePage", this)
}  


wxNotebook_GetPageImage =
function(this, page)
{
  .Call("R_wxNotebook_GetPageImage", this, as.integer(page))
}

wxNotebook_SetPageImage =
function(this, page, index)
{
  .Call("R_wxNotebook_SetPageImage", this, as.integer(page), as.integer(index))
}  

wxNotebook_SetSelection =
function(this, page)
{
  .Call("R_wxNotebook_SetSelection", this, as.integer(page))
}

wxNotebook_SetPageText =
function(this, page, text)
{
  .Call("R_wxNotebook_SetPageText", this, as.integer(page), as.character(text))
}

wxNotebook_AddPage =
function(this, page, text, selected = FALSE, image = -1)
{
  .Call("R_wxNotebook_AddPage", this, page, as.character(text), as.logical(selected), as.integer(image))
}

wxNotebook_InsertPage =
function(this, index, page, text, selected = FALSE, image = -1)
{
  .Call("R_wxNotebook_InsertPage", this, as.integer(index), page, as.character(text), as.logical(selected), as.integer(image))
}

wxNotebook_AdvanceSelection =
function(this, forward)
{
  .Call("R_wxNotebook_SetSelection", this, as.logical(forward))
}

wxNotebook_SetImageList =
function(this, imageList)
{
  .Call("R_wxNotebook_SetImageList", this, imageList)
}


wxNotebook_GetPageText =
function(this, page)
{
  .Call("R_wxNotebook_GetPageText", this, as.integer(page))
}

wxNotebook_GetPage =
function(this, page)
{
  .Call("R_wxNotebook_GetPage", this, as.integer(page))
}

wxNotebook_GetCurrentPage =
function(this)
{
  .Call("R_wxNotebook_GetCurrentPage", this)
}
