wxMenuBar =
function(style = 0)
  .Call("R_wxMenuBar_new", as.numeric(style))

wxMenuBar_Append =
function(this, menu, title)
  .Call("R_wxMenuBar_Append", this, menu, as.character(title))
