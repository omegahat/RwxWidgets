wxEvent_Skip =
  function(ev, skip = TRUE) {
    .Call("R_wxEvent_Skip", ev, as.logical(skip))
  }

wxEvent_GetEventObject =
function(ev)
{
  obj = .Call("R_wxEvent_GetEventObject", ev)
  wxObject(obj)
}

wxEvent_GetId =
function(ev)
{
  obj = .Call("R_wxEvent_GetId", ev)
}  


wxKeyEvent_MetaDown =
function(ev)
{
  .Call("R_wxKeyEvent_MetaDown", ev)
}

wxKeyEvent_ControlDown =
function(ev)
{
  .Call("R_wxKeyEvent_ControlDown", ev)
}

wxKeyEvent_GetKeyCode =
function(this)
{
  .Call("R_wxKeyEvent_GetKeyCode", this)
}  


wxCommandEvent_GetString =
function(event)
  .Call("R_wxCommandEvent_GetString", event)
