library(RwxWidgets)
library(bitops)
library(RwxDevice)

wxSL_HORIZONTAL = wxHORIZONTAL
wxSL_TICKS = as.integer(0x0010)
wxSL_AUTOTICKS = wxSL_TICKS




OnInit =
function(this.app)
{

  f = RFrame("Slider example", size= c(400, 400))

  if(TRUE) {
    d = RwxCanvas(f)
    asWxDevice(d)
  } else {
     d = wxButton(f, label = "Does nothing")
     x11()
  }

  sl = wxSlider(f, value = 0, min = -100, max = 100, style = c(wxHORIZONTAL, wxSL_AUTOTICKS))

#  wxEVT_COMMAND_SCROLLBAR_UPDATED
  sl$AddCallback(wxEVT_SCROLL_THUMBRELEASE, function(ev) {  # wxEVT_SCROLL_CHANGED
     m = c(sl$GetMin(), sl$GetMax())
     print(c(sl$GetValue(), m))
     
     mu = -4 + 8*(sl$GetValue() - m[1])/(m[2] - m[1])
     hist(rnorm(1000, mu), xlim = c(-6, 6), prob = TRUE, 
               main = substitute(rnorm(n = 100, mu = mu), list (mu = mu)))
     curve(dnorm(x, mu, 1), -4 + mu, mu + 4, add = TRUE, col = "red")     
   })
  
  sz = wxBoxSizer(wxVERTICAL)
  sz$Add(d, 1, wxEXPAND)
  sz$Add(sl, 0, wxEXPAND)  
  f$SetSizer(sz)
  sz$SetSizeHints(f)

  curve(dnorm(x, 0, 1), -4, 4)
  
  f$Show()
}

#app = RApp(OnInit = OnInit, run = TRUE)

wxInit()
OnInit()
