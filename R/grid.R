#  .Call("R_wxGrid_CreateGrid", grid, as.integer(0), as.integer(0))
#  .Call("R_wxGrid_AppendRows", grid, as.integer(40))
#  .Call("R_wxGrid_AppendCols", grid, as.integer(10)) 

wxGrid =
function(parent = NULL,
         id = wxID_ANY,
         position = as.integer(c(0, 0)),
         size = as.integer(c(400, 300)))
#  c("wxWANTS_CHARS" = as.integer(100)), ""
{
 grid =  .Call("R_wxGrid_new", parent, id,
                               position, size) # extra arguments.
}  

wxCreateGrid =
function(grid, row, col)
{
  .Call("R_wxGrid_CreateGrid", grid, as.integer(row), as.integer(col))
}  


wxSetColLabelValue =
function(grid, index, value)
{

}

if(!isGeneric("colnames<-"))
  setGeneric("colnames<-", function(x, value) standardGeneric("colnames<-"))

setWxGridColNames <-
           function(x, value) {
             sapply(seq(along = value),
                    function(i)
                        .Call("R_wxGrid_SetColLabelValue", x, as.integer(i-1), value[i]))
           }  
setMethod("colnames<-", "wxGrid", setWxGridColNames)


if(!isGeneric("rownames<-"))
  setGeneric("rownames<-", function(x, value) standardGeneric("rownames<-"))

setWxGridRowNames <-
  function(x, value) {
             sapply(seq(along = value),
                    function(i)
                        .Call("R_wxGrid_SetRowLabelValue", x, as.integer(i-1), value[i]))
           }
setMethod("rownames<-", "wxGrid", setWxGridRowNames)


wxWindow_Fit =
function(this)
{
  .Call("R_wxWindow_Fit", this)
}




showDataGrid =
  #
  # Experimental (i.e. illustration rather than finished version!)
  #
  #
function(d, frame = RFrame("RWxWidgets example", 
                              as.integer(c(50, 30)),
                              as.integer(450, 300)))
{
 grid = wxGrid(frame, pos = as.integer(c(0, 0)),
                      size = as.integer(c(400, 300)))

 wxCreateGrid(grid, nrow(d), ncol(d))

 setWxGridColNames(grid, colnames(d))
# colnames(grid) <- colnames(d)
# rownames(grid) <- rownames(d) 


  # Now let's get the values into the cells.
  n = nrow(d)
  sapply(seq(1, length = ncol(d)),
             function(j) {
               var = as.character(d[,j])
               sapply(seq(along = var),
                       function(i) {
                         .Call("R_wxGrid_SetCellValue", grid, as.integer(i-1), as.integer(j-1), var[i])
                       })
            })

 .Call("R_wxWindow_Fit", grid)

 grid
}
