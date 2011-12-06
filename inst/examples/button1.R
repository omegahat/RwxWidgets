library(RwxWidgets)
OnInit = function(...)  {

  topWin <- RFrame("Simple R GUI",
                   size = c(1000L, 800L),
                   OnQuit = function(event) q("ask"))

  btn = wxButton(topWin, 10010, "Button")
  topWin$AddCallback(wxEVT_COMMAND_BUTTON_CLICKED, function(ev, ...) cat("event: ", class(ev), "\n"), objId = 10010)

  topWin$Show()
  
  TRUE
}

wxInit()
OnInit()
# RApp(OnInit = OnInit, run = TRUE)
