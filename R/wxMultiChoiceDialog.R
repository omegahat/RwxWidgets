wxMultiChoiceDialog =
function(parent, message, caption, choices, style = wxCHOICEDLG_STYLE, pos = wxDefaultPosition)
{
  style = bitlist(style)
  .Call("R_wxMultiChoiceDialog_new", parent, as.character(message), as.character(caption),
                                     as.character(choices), style, pos)
}


wxMultiChoiceDialog_GetSelections =
function(this)
  .Call("R_wxMultiChoiceDialog_GetSelections", this)



wxSingleChoiceDialog =
function(parent, message, caption, choices, style = wxCHOICEDLG_STYLE, pos = wxDefaultPosition)
{
  style = bitlist(style)
  .Call("R_wxSingleChoiceDialog_new", parent, as.character(message), as.character(caption),
                                     as.character(choices), style, pos)
}


wxSingleChoiceDialog_GetSelection =
function(this)
  .Call("R_wxSingleChoiceDialog_GetSelection", this)
