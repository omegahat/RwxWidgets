library(RwxWidgets)
wxInit()

OnInit = function(...)  {

  topWin <- RFrame("Simple R GUI",
                  size = c(1000L, 800L),
                  OnQuit = function(event) q("ask"))
  topWin$AddCallback(wxEVT_MOVE, function(...) cat("Moved top window\n"))
  topWin$Show()
}

OnInit()
#RApp(OnInit = OnInit, run = TRUE)

