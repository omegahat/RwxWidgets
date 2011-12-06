wxSlider =
function(parent, id = -1, value, min, max,
          point = wxDefaultPosition, size = wxDefaultSize,
          style = wxSL_HORIZONTAL,         
          name = "wxSlider")
{
  parent = as(parent, "wxWindow")
  
  size = as(size, "RwxSize")
  point = as(point, "RwxPoint")
  
   .Call("R_wxSlider_new", parent, as.integer(id), as.integer(value), as.integer(min), as.integer(max),
                            point, size, as.numeric(bitlist(style)))
}  


wxSlider_GetValue =
function(slider)
{
   .Call("R_wxSlider_GetValue", slider)
}  

wxSlider_SetValue =
function(slider, value)
{
   .Call("R_wxSlider_SetValue", slider, as.integer(value))
}  


wxSlider_GetMin =
function(slider)
{
   .Call("R_wxSlider_GetMin", slider)
}

wxSlider_SetMin =
function(slider, value)
{
   .Call("R_wxSlider_SetMin", slider, as.integer(value))
}  


wxSlider_GetMax =
function(slider)
{
   .Call("R_wxSlider_GetMax", slider)
}

wxSlider_SetMax =
function(slider, value)
{
   .Call("R_wxSlider_SetMax", slider, as.integer(value))
}  


wxSlider_GetPageSize =
function(slider)
{
   .Call("R_wxSlider_GetPageSize", slider)
}

wxSlider_SetPageSize =
function(slider, value)
{
   .Call("R_wxSlider_SetPageSize", slider, as.integer(value))
}  


wxSlider_SetThumbLength =
function(slider, value)
{
   .Call("R_wxSlider_SetThumbLength", slider, as.integer(value))
}  

