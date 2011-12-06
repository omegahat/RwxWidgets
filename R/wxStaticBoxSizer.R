wxStaticBoxSizer =
function(orient, parent, label = "")
{
  .Call("R_wxStaticBoxSizer_new", as.integer(orient), parent, as.character(label))
}  
