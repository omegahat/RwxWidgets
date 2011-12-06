wxFileDialog =
function(parent, message = "Choose a file", defaultDir = "",
         default = "", wildcard = "*.*", style = 0, pos = wxDefaultPosition)
{
  .Call("R_wxFileDialog_new", parent, as.character(message), as.character(defaultDir),
                              as.character(default), as.character(wildcard), as.numeric(bitlist(style)),
                              pos)
}

wxFileDialog_GetPath =
function(this)
{
   .Call("R_wxFileDialog_GetPath", this)
}

