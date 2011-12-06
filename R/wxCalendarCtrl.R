wxCalendarCtrl =
function(parent, id = wxID_ANY, date = wxDefaultDateTime(),
         pos = wxDefaultPosition, size = wxDefaultSize,
         style = wxCAL_SHOW_HOLIDAYS,
          name = "calendarCtrl")
{
   style = as.numeric(bitlist(style))
   size = as(size, "RwxSize")
   pos = as(pos, "RwxPoint")
   
  .Call("R_wxCalendarCtrl_new",
            parent, as.integer(id),
            as(date, "wxDateTime"),
            pos, size, style, as.character(name))
}


wxCalendarCtrl_GetDate =
function(this)
  .Call("R_wxCalendarCtrl_GetDate", this)

wxCalendarCtrl_SetDate =
function(this, date)
  .Call("R_wxCalendarCtrl_GetDate", this, as(date, "wxDateTime"))




