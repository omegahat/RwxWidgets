library(RwxWidgets)

OnInit =
function(...)
{  
 f <- RFrame("RWxWidgets example",
              as.integer(c(50, 30)),
              as.integer(Size(450, 300)))


 grid =  wxGrid(f, wxID_ANY,
                as.integer(c(0, 0)),
                as.integer(c(400, 300)))
 #
#                c("wxWANTS_CHARS" = as.integer(100)

 grid$CreateGrid(100, 50)
 grid$Fit()
 f$Show()
}

OnInit()
#app = RApp(OnInit = OnInit, run = TRUE)
