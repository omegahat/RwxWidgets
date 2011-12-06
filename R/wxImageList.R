setGeneric("wxImageList",
           function(width, height, mask = TRUE, initialCount = 1) {
             standardGeneric("wxImageList")
           })

setMethod("wxImageList", c("missing", "missing"),
          function(width, height, mask = TRUE, initialCount = 1)
             .Call("R_wxImageList_new")
            )

setMethod("wxImageList", c("numeric", "numeric"),
          function(width, height, mask = TRUE, initialCount = 1)
          {
            .Call("R_wxImageList_new_int_int", as.integer(width), as.integer(height),
                  as.logical(mask), as.integer(initialCount))
          })


setGeneric("wxImageList_Add",
            function(this, bitmap , mask = wxNullBitmap)
                standardGeneric("wxImageList_Add"))

setMethod("wxImageList_Add",
           c("wxImageList", "wxBitmap"),
            function(this, bitmap, mask = wxNullBitmap) {
              .Call("R_wxImageList_Add_wxBitmap_wxBitmap", this, as(bitmap, "wxBitmap"), mask) 
            })

setMethod("wxImageList_Add",
           c("wxImageList", "wxBitmap", "wxColour"),
            function(this, bitmap, mask = wxNullBitmap) {
              .Call("R_wxImageList_Add_wxBitmap_wxColour", this, bitmap, mask)
            })

setMethod("wxImageList_Add",
           c("wxImageList", "wxIcon"),
            function(this, bitmap, mask = wxNullBitmap) {
              .Call("R_wxImageList_Add_wxIcon", this, bitmap)
            })

wxImageList_GetImageCount =
function(this)
  .Call("R_wxImageList_GetImageCount", this)

wxImageList_GetSize =
function(this, index = -1)
  .Call("R_wxImageList_GetImageCount", this, as.integer(index))


wxImageList_GetBitmap =
function(this, index)
  .Call("R_wxImageList_GetBitmap", this, as.integer(index))

setMethod("length", "wxImageList",
          function(x)
            wxImageList_GetImageCount(x))

setMethod("[[", "wxImageList",
          function(x, i, j, ...)
            wxImageList_GetBitmap(x, i - 1))
