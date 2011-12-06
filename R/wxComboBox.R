wxComboBox =
function(parent, id = wxID_ANY, value = "", pos = wxDefaultPosition, size = wxDefaultSize,
         choices, style = 0, validator = NULL, name = "comboBox")
{
  .Call("R_wxComboBox_new", parent, as.integer(id), as.character(value), pos, size, as.character(choices),
                             as.numeric(bitlist(style)), validator, as.character(name))
}  

wxComboBox_SetSelection =
function(this, from, to)
{
 .Call("R_wxComboBox_SetSelection", this, as.numeric(from), as.numeric(to))
}

wxComboBox_GetValue =
function(this)
{
 .Call("R_wxComboBox_GetValue", this)
}

wxComboBox_SetValue =
function(this, text)
{
 .Call("R_wxComboBox_SetValue", this, text)
}  
