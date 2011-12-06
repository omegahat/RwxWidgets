setGeneric("wxGBSpan",
           function(rowspan = 1, colspan = 1)
             standardGeneric("wxGBSpan"))

setMethod("wxGBSpan",
           c("numeric", "numeric"),
           function(rowspan = 1, colspan = 1)
              .Call("R_wxGBSpan_new_int_int", as.integer(rowspan), as.integer(colspan)))


setMethod("wxGBSpan",
           c("missing", "missing"),
           function(rowspan = 1, colspan = 1)
              .Call("R_wxGBSpan_new"))

