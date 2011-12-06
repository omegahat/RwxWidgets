wxRadioBox =
function(parent, id = wxID_ANY, label, point = wxDefaultPosition, size = wxDefaultSize,
          choices = character(),
          majorDimension = 0, style = wxRA_SPECIFY_COLS, validator = wxDefaultValidator,
          name = "radioBox")
{
  .Call("R_wxRadioBox_new", parent, as.integer(id), as.character(label), point, size, as.character(choices),
                            as.integer(majorDimension), as.numeric(bitlist(style)), validator,
                            validator, as.character(name))
}  

wxRadioBox_GetStringSelection =
function(this)
{
    .Call("R_wxRadioBox_GetStringSelection", this)
}

wxRadioBox_GetSelection =
function(this)
{
    .Call("R_wxRadioBox_GetSelection", this)
}

wxRadioBox_GetLabel =
function(this)
{
    .Call("R_wxRadioBox_GetLabel", this)
}

wxRadioBox_SetLabel =
function(this, label)
{
    .Call("R_wxRadioBox_SetLabel", this, as.character(label))
}




