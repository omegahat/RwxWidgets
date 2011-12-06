wxSpinCtrl =
function(parent, id = wxID_ANY, value = "", style = wxSP_ARROW_KEYS,
          min = 0, max = 100, initial = 0, name = "wxSpinCtrl")
{

  .Call("R_wxSpinCtrl_new", parent, as.integer(id), as.character(value), as.numeric(bitlist(style)),
            as.integer(min), as.integer(max), as.integer(initial), as.character(name))

}


wxSpinCtrl_GetValue =
function(this)
{
  .Call("R_wxSpinCtrl_GetValue", this)
}  


setGeneric("wxSpinCtrl_SetValue",
             function(this, value)
                standardGeneric("wxSpinCtrl_SetValue"))

setMethod("wxSpinCtrl_SetValue", c(value = "character"),
          function(this, value) {
            .Call("R_wxSpinCtrl_GetValue_wxString", this, value)
          })

setMethod("wxSpinCtrl_SetValue", c(value = "numeric"),
          function(this, value) {
            .Call("R_wxSpinCtrl_GetValue_int", this, as.integer(value))
          })
