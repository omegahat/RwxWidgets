wxStaticText =
function(parent, id = wxID_ANY, label = "", pos = wxDefaultPosition , size = wxDefaultSize,
                style = 0, name = "staticText")
{
   style = as.numeric(bitlist(style))
   .Call("R_wxStaticText_new", parent, as.integer(id), as.character(label),
                               pos, size, style, as.character(name))
}


wxStaticText_SetLabel =
function(this, label)
  .Call("R_wxStaticText_SetLabel", this, as.character(label))

wxStaticText_GetLabel =
function(this)
  .Call("R_wxStaticText_GetLabel", this)

