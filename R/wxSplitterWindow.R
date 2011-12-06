wxSplitterWindow =
function(parent, id, pos = wxDefaultPosition, size = wxDefaultSize, style = wxSP_3D,
           name = "splitterWindow")
{
   .Call("R_wxSplitterWindow_new", parent, as.integer(id),
                                   pos, size, as.numeric(bitlist(style)),
                                   as.character(name))
}  

wxSplitterWindow_SplitHorizontally =
function(this, window1, window2, sashPosition = 0)
  .Call("R_wxSplitterWindow_SplitHorizontally", this, window1, window2, as.integer(sashPosition))

wxSplitterWindow_SplitVertically =
function(this, window1, window2, sashPosition = 0)
  .Call("R_wxSplitterWindow_SplitVertically", this, window1, window2, as.integer(sashPosition))


wxSplitterWindow_SetSashPosition =
function(this, position, redraw)
{
  .Call("R_wxSplitterWindow_SetSashPosition", this, as.integer(position), as.logical(redraw))
}  
