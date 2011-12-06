wxFrame =
function(parent = NULL, id = wxID_ANY, title = "", pos = wxDefaultPosition, size = wxDefaultSize, style = 0, name = "frame")  
{
  size = as(size, "RwxSize")
  pos = as(size, "RwxPoint")  

  .Call("R_wxFrame_new", parent, as.integer(id), as.character(title),
                         pos, size, style, as.character(name))
}

RFrame <-
  #
  #  Create a frame
  #
function(title = "R-wxWidgets",
         pos = c(50, 100),
         size = c(400, 300),
         id = -1,
         OnQuit = NULL)
{
  if(!is.null(OnQuit))
    OnQuit = as.function(OnQuit)  

  size = as(size, "RwxSize")
  pos = as(pos, "RwxPoint")    

  ans = .Call("R_RwxFrame_new", as.character(title),
                   pos, size, as.integer(id),
                   OnQuit)

  if(length(OnQuit) && is.function(OnQuit))
    ans$AddCallback(wxEVT_CLOSE_WINDOW, OnQuit)

  ans

}

wxFrame_CreateStatusBar =
function(this)
{
  .Call("R_wxFrame_CreateStatusBar", this)
}

wxFrame_CreateToolBar =
function(this, style = c(wxNO_BORDER, wxTB_HORIZONTAL), id = -1, name = "toolBar")
{
  style = bitlist(style)
  .Call("R_wxFrame_CreateToolBar", this, as.numeric(style), as.integer(id), as.character(name))
}

wxFrame_SetStatusText =
function(this, msg)
{
  .Call("R_wxFrame_SetStatusText", this, as.character(msg))
}


wxFrame_GetMenuBar = 
function(this)
{
  .Call("R_wxFrame_GetMenuBar", this)
}  

wxFrame_SetMenuBar = 
function(this, menuBar)
{
  .Call("R_wxFrame_SetMenuBar", this, menuBar)
}  


