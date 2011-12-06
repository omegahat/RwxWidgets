wxGridSizer =
function(rows = 0, cols = 0, vgap = 0, hgap = 0)
{
   .Call("R_wxGridSizer_new", as.integer(rows), as.integer(cols), as.integer(vgap), as.integer(hgap))
}  

wxFlexGridSizer =
function(rows = 0, cols = 0, vgap = 0, hgap = 0)
{
   .Call("R_wxFlexGridSizer_new", as.integer(rows), as.integer(cols), as.integer(vgap), as.integer(hgap))
}

wxGridBagSizer =
function(vgap = 0, hgap = 0)
{
   .Call("R_wxGridBagSizer_new", as.integer(vgap), as.integer(hgap))
}

wxBoxSizer =
function(orient = 4) # 8 for vertical
{
   .Call("R_wxBoxSizer_new", as.integer(orient))
}  


wxBoxSizer_GetOrientation =
function(this)
  .Call("R_wxBoxSizer_GetOrientation", this)


setClass("wxSizerFlags", representation(ref = "externalptr"))

setGeneric("wxSizer_Add", 
            function(this, width, height, proportion = 0, flag = 0, border = 0, userData = NULL) {
                 standardGeneric("wxSizer_Add")
               }
          )

setMethod("wxSizer_Add", c("wxSizer", "wxWindow", "wxSizerFlags"),
          function(this, width, height, proportion = 0, flag = 0, border = 0, userData = NULL) {
            .Call("R_wxSizer_Add_wxWindowp_wxSizerFlags", this, width, height)
          })

setMethod("wxSizer_Add", c("wxSizer", "wxWindow"),
          function(this, width, height, proportion = 0, flag = 0, border = 0, userData = NULL) {
              # Here           C++ method
              # height     -> proportion
              # proportion -> flag
              # flag       -> border
              # border     -> userData
             if(missing(height))
               height = 0

             height = as.integer(height)[1]
             proportion = as.integer(bitlist(proportion))[1]
             flag = as.integer(flag)[1]
             if(missing(border))
               border = NULL
             
            .Call("R_wxSizer_Add_wxWindowp_int_int_int_wxObjectp", this, width, height, proportion, flag, border)
          })



setMethod("wxSizer_Add", c("wxSizer", "wxSizer", "wxSizerFlags"),
          function(this, width, height, proportion = 0, flag = 0, border = 0, userData = NULL) {
            .Call("R_wxSizer_Add_wxSizer_wxSizerFlags", this, width, height)
          })

setMethod("wxSizer_Add", c("wxSizer", "wxSizer"),
          function(this, width, height, proportion = 0, flag = 0, border = 0, userData = NULL) {
             if(missing(height))
               height = 0            
             height = as.integer(height)
             proportion = as.integer(proportion)
             flag = as.integer(flag)

            .Call("R_wxSizer_Add_wxSizer_int_int_int", this, width, height, proportion, flag, border)
          })
setMethod("wxSizer_Add", c("wxSizer", "integer", "integer"),
          function(this, width, height, proportion = 0, flag = 0, border = 0, userData = NULL) {
             width = as.integer(width)[1]
             height = as.integer(height)[1]
             proportion = as.integer(proportion)[1]
             flag = as.integer(flag)[1]
             border = as.integer(border)[1]
             userData = as(userData, "wxObject")

            .Call("R_wxSizer_Add_int_int_int_int_int_wxObjectp", this, width, height, proportion, flag, border, userData)
          })




setGeneric("wxSizer_Insert", 
            function(this, index, width, height, proportion = 0, flag = 0, border = 0) {
                 standardGeneric("wxSizer_Insert")
               }
          )

setMethod("wxSizer_Insert", c("wxSizer", "numeric", "wxWindow", "wxSizerFlags"),
          function(this, index, width, height, proportion = 0, flag = 0, border = 0) {
            .Call("R_wxSizer_Insert_size_t_wxWindow_wxSizerFlags", this, index, width, height)
          })

setMethod("wxSizer_Insert", c("wxSizer", "numeric", "wxWindow", "numeric"),
          function(this, index, width, height, proportion = 0, flag = 0, border = 0) {
             height = as.integer(height)[1]
             proportion = as.integer(proportion)[1]
             flag = as.integer(flag)[1]

            .Call("R_wxSizer_Insert_size_t_wxWindow_int_int_int", this, index, width, height, proportion, flag)
          })

setMethod("wxSizer_Insert", c("wxSizer", "numeric", "wxSizer", "wxSizerFlags"),
          function(this, index, width, height, proportion = 0, flag = 0, border = 0) {
            .Call("R_wxSizer_Insert_size_t_wxSizer_wxSizerFlags", this, index, width, height)
          })

setMethod("wxSizer_Insert", c("wxSizer", "numeric", "wxSizer", "numeric"),
          function(this, index, width, height, proportion = 0, flag = 0, border = 0) {
             height = as.integer(height)[1]
             proportion = as.integer(proportion)[1]
             flag = as.integer(flag)[1]

            .Call("R_wxSizer_Insert_size_t_wxSizer_int_int_int", this, index, width, height, proportion, flag)
          })


setMethod("wxSizer_Insert", c("wxSizer", "numeric", "numeric"),
          function(this, index, width, height, proportion = 0, flag = 0, border = 0) {
             width = as.numeric(width)[1]
             height = as.integer(height)[1]
             proportion = as.integer(proportion)[1]
             flag = as.integer(flag)[1]
             border = as.integer(border)[1]

            .Call("R_wxSizer_Insert_size_t_int_int_int_int_int", this, index, width, height, proportion, flag, border)
          })



wxSizer_SetSizeHints =
function(sizer, parent)
{
  .Call("R_wxSizer_SetSizeHints", sizer, parent)
}  

wxSizer_AddStretchSpacer =
function(sizer, prop = 1)
{
   .Call("R_wxSizer_AddStretchSpacer", sizer, as.integer(prop))
}

wxSizer_AddSpacer =
function(sizer, prop)
{
   .Call("R_wxSizer_AddSpacer", sizer, as.integer(prop))
}  


wxSizer_SetMinSize =
  function(this, x, y)
    .Call("R_wxSizer_SetMinSize_int_int", this, as.integer(x), as.integer(y))



setGeneric("wxSizer_Show",
              function(this, window, show = TRUE, recursive = FALSE)
                 standardGeneric("wxSizer_Show"))


setMethod("wxSizer_Show", c("wxSizer", "wxWindow"),
              function(this, window, show = TRUE, recursive = FALSE)
                  .Call("R_wxSizer_Show_wxWindow_bool_bool", this, window, as.logical(show), as.logical(recursive)))

setMethod("wxSizer_Show", c("wxSizer", "wxSizer"),
              function(this, window, show = TRUE, recursive = FALSE)
                  .Call("R_wxSizer_Show_wxSizer_bool_bool", this, window, as.logical(show), as.logical(recursive)))


setMethod("wxSizer_Show", c("wxSizer", "numeric"),
              function(this, window, show = TRUE, recursive = FALSE)
                  .Call("R_wxSizer_Show_size_t_bool", this, as.numeric(window), as.logical(show)))


wxSizer_Layout =
function(this)
  .Call("R_wxSizer_Layout", this)



wxSizer_GetChildren =
  function(this)
    .Call("R_wxSizer_GetChildren", this)

wxSizer_GetContainingWindow =
  function(this)
    .Call("R_wxSizer_GetContainingWindow", this)



setGeneric("wxSizer_Remove", function(this, window) standardGeneric("wxSizer_Remove"))
setMethod("wxSizer_Remove", c("wxSizer", "wxWindow"),
           function(this, window)
               .Call("R_wxSizer_Remove_wxWindow", this, window))

setMethod("wxSizer_Remove", c("wxSizer", "wxSizer"),
           function(this, window)
               .Call("R_wxSizer_Remove_wxSizer", this, window))



wxFlexGridSizer_AddGrowableRow =
function(this, idx, proportion = 100)
{
   .Call("R_wxFlexGridSizer_AddGrowableRow", this, as(idx, "numeric"), as(proportion, "integer"))
}

wxFlexGridSizer_AddGrowableCol =
function(this, idx, proportion = 100)
{
   .Call("R_wxFlexGridSizer_AddGrowableCol", this, as(idx, "numeric"), as(proportion, "integer"))
}  



if(FALSE) {
setGeneric("wxGridBagSizer_Add",
           function(this, width, height, pos, span = wxDefaultSpan, flag = 0, border = 0)
           {
             tryCatch(standardGeneric("wxGridBagSizer_Add"),
                      error = function(e) {
                        wxSizer_Add(this, width, height, pos, span, flag, border)
                      })
           })

setMethod("wxGridBagSizer_Add",
           c("wxGridBagSizer", "wxWindow"),
           function(this, width, height, pos, span = wxDefaultSpan, flag = 0, border = 0)
{
 .Call("R_wxGridBagSizer_Add_wxWindow_wxGBPosition_wxGBSpan_int_int_wxObject",
          this, width, as(height, "wxGBPosition"), as(pos, "wxGBSpan"), as(span, "integer"), as(flag, "integer"))
})

setMethod("wxGridBagSizer_Add",
           c("wxGridBagSizer", "wxSizer"),
           function(this, width, height, pos, span = wxDefaultSpan, flag = 0, border = 0)
{
 .Call("R_wxGridBagSizer_Add_wxSizer_wxGBPosition_wxGBSpan_int_int_wxObject",
          this, width, as(height, "wxGBPosition"), as(pos, "wxGBSpan"), as(span, "integer"), as(flag, "integer"))
})  


setMethod("wxGridBagSizer_Add",
           c("wxGridBagSizer", "numeric", "numeric"),
           function(this, width, height, pos, span = wxDefaultSpan, flag = 0, border = 0)
{
 .Call("R_wxGridBagSizer_Add_int_int_wxGBPosition_wxGBSpan_int_int_wxObject",
          this, width, height, as(pos, "wxGBPosition"), as(span, "wxGBSpan"), as(flag, "integer"), as(border, "integer"))
})  
} else {


setMethod("wxSizer_Add",
           c("wxGridBagSizer", "wxWindow"),
           function(this, width, height, proportion, flag = 0, border = 0, userData = NULL)
{
  if(is(proportion, "numeric") && proportion == 0)
    proportion = 1
  
 .Call("R_wxGridBagSizer_Add_wxWindow_wxGBPosition_wxGBSpan_int_int_wxObject",
          this, width, as(height, "wxGBPosition"), as(proportion, "wxGBSpan"), as(flag, "integer"), as(border, "integer"))
})

setMethod("wxSizer_Add",
           c("wxGridBagSizer", "wxSizer"),
           function(this, width, height, proportion, flag = 0, border = 0, userData = NULL)
{
  if(is(proportion, "numeric") && proportion == 0)
    proportion = 1
  
 .Call("R_wxGridBagSizer_Add_wxSizer_wxGBPosition_wxGBSpan_int_int_wxObject",
          this, width, as(height, "wxGBPosition"), as(proportion, "wxGBSpan"), as(flag, "integer"), as(border, "integer"))
})  


setMethod("wxSizer_Add",
           c("wxGridBagSizer", "numeric", "numeric"),
           function(this, width, height, proportion, flag = 0, border = 0, userData = NULL)
{
 .Call("R_wxGridBagSizer_Add_int_int_wxGBPosition_wxGBSpan_int_int_wxObject",
          this, width, height, as(proportion, "wxGBPosition"), as(flag, "wxGBSpan"), as(border, "integer"), 0L)#XXX need an extra argument.
})

}
