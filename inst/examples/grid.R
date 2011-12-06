library(RwxWidgets)
wxInit()

# Get the row labels to size appropriately
# resizable column labels for the first column, i.e. row labels.
# scrolling
# resize window and maintain scroll bars  - fine with sizer.


OnInit <-
function(this)
{
  f <- RFrame("RWxWidgets example",
               as.integer(c(50, 30)),
               as.integer(Size(450, 300)))

  if(FALSE) {
    f$CreateStatusBar()
    f$SetStatusText("An example of R-wxWidgets events")
 }

  data(mtcars)
  grid = showDataGrid(mtcars, f)

   # wxAlignment.
  .Call("R_wxGrid_SetRowLabelAlignment", grid, c("left" = as.integer(0)), as.integer(0))

if(TRUE) {
    # We don't need a sizer here.
  sizer = wxBoxSizer(wxVERTICAL)
  sizer$Add(grid, 1, wxEXPAND)
#  f$SetAutoLayout(TRUE)
  .Call("R_wxWindow_SetAutoLayout", f, TRUE) 
  f$SetSizer(sizer)
  sizer$SetSizeHints(f)
  # sizer$Fit()
}

  ###XXX Broken the events now!
newCallbacks = TRUE
  if(newCallbacks)
   grid$AddCallback(wxEVT_GRID_COL_SIZE,
                   function(ev) cat("Column size\n"))
  else
  .Call("R_Rwx_Connect", grid, .Call("R_wxWindow_GetId", grid), #grid$GetId(),
             as.integer(1589),
             function(ev) cat("Column size\n"),
             NULL, NULL, list(), FALSE)
  
    # works.
  if(newCallbacks)
  grid$AddCallback(10213, #not the same wxEVT_GRID_CELL_CHANGE,
                    function(ev) cat("Changed a cell\n"))

   # Not working yet.

    # Doesn't activate yet!
  # grid$AddCallback()
  if(newCallbacks)
  grid$AddCallback(wxEVT_GRID_CELL_LEFT_CLICK,
                                function(ev) cat("Selected a cell\n"))
  else
  .Call("R_Rwx_Connect", grid, .Call("R_wxWindow_GetId", grid),
             as.integer(1580),
             function(ev) cat("Selected a cell\n"),
             NULL, NULL, list(), FALSE)


   f$Show()
}


if(FALSE) {
 app = RApp(OnInit = OnInit, run = TRUE)
} else {
#  app = .C("R_wx_main", c("R"), as.integer(1))
  OnInit()
}
