
setGeneric("wxToolBar_AddTool",
            function(this, id, label, bitmap, helpString = "", kind = wxITEM_NORMAL) {
              standardGeneric("wxToolBar_AddTool")
            })

setMethod("wxToolBar_AddTool",
            c("wxToolBar", "integer", "character", "wxBitmap"),
            function(this, id, label, bitmap, helpString = "", kind = wxITEM_NORMAL) {
              .Call("R_wxToolBar_AddTool_int_wxString_wxBitmap_wxString_wxItemKind",
                       this,
                       as.integer(id), as.character(label),
                       as(bitmap, "wxBitmap"),
                       as.character(helpString), as.integer(kind))
            })


wxToolBar_Realize =
  function(this)
  .Call("R_wxToolBar_Realize", this)
