<?xml version="1.0"?>

<article>  
library(RwxWidgets)
wxInit()

wxNO_BORDER = wxBORDER_NONE

f = RFrame("Menu example", size = c(300, 300))

menuBar = wxMenuBar()
menuBar$Show()
f$SetMenuBar(menuBar)

menu = wxMenu()
i = menu$Append(wxID_ANY, "Entry 1")
print(i$GetId())
# Note that we are adding the callback to f (a wxWindow)
f$AddCallback(wxEVT_COMMAND_MENU_SELECTED, function(ev) cat("Menu item selected"), objId = i$GetId())
# next one causes things to hang.
#i$AddCallback(wxEVT_COMMAND_MENU_SELECTED, function(ev) cat("In direct wxMenuItem handler"))
menu$Append(wxID_ANY, "Entry 2")

menuBar$Append(menu, "A")

subMenu = wxMenu("B")
subMenu$Append(wxID_ANY, "Red")
subMenu$Append(wxID_ANY, "Blue")
subMenu$Append(wxID_ANY, "Green")
menu$Append(wxID_ANY, "B", subMenu)


menu$AppendSeparator()
menu$AppendCheckItem(wxID_ANY, "Check box")
menu$AppendRadioItem(wxID_ANY, "Radio button")

menu = wxMenu("European Cities")
cityNames = attr(eurodist, "Labels")
sapply(seq(along = cityNames),
         function(i) menu$Append(400 + i , cityNames[i]))
f$AddCallback(wxEVT_COMMAND_MENU_SELECTED,
              objId = c(401, 400 + length(cityNames)),
              function(ev) {
                   i = ev$GetId()
                   cat("Selected city",  i, cityNames[i - 400], "\n")
                   print(ev$GetString())
              })

menuBar$Append(menu, "City")


menu$AddCallback(wxEVT_COMMAND_MENU_SELECTED, function(ev) cat("Menu item selected"), objId = wxID_ANY)

f$CreateToolBar()

f$Show()

eloop = wxEventLoop()
eloop$Run()

