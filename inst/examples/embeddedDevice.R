library(RwxWidgets)

#
# This is an example of using an embedded graphics device.  We have 4 choices
# of plots some simple, some more complex.  One selects the desired plot
# via radio buttons and this updates the plot. (For the complex time version,
#  this takes 10 seconds or so as the computations to create the contents of the
# plot are lengthy. This example is taken from the R Graphics Gallery and is
# by Philippe Grosjean, Spirlet and Jangoux from a 2003 paper.)
#
#
# Issues: we don't reset all the relevant parameters for the graphics device
#  when moving to a different plot, e.g. par(mfrow = c(1,2)) is still in effect
#  after we move to another plot. The margins from the complex time plot persist
#  in subsequent plots.
#  The lattice plot doesn't appear yet.

plotChoices = c("histogram", "complex time", "lattice", "hist/boxplot", "lattice stand-alone")

# This is the callback function that draws the plot.
# It is given the radio button widget that was selected to cause the new plot to
# be drawn along with its identifier that was given when the button was add'ed to
# the radioButtonGroup().   Also it receives any additional arguments that were
# specified as part of the ... in the call to radioButtonGroup().
# This avoids the need to have global variables or define this function inside
# another to use lexical scoping to find the variable 'canvas'.
doPlot =
function(el, id, canvas)
{
     if(!canvas$IsRDevice()) 
       asWxDevice(canvas)
     
     x = match(id, plotChoices)     
     cat("selection = ", x, "\n")
     if(x == 1) {
       par(mfrow = c(1, 1))
       x = rnorm(1000)
       hist(x, xlab = "Normal deviates", ylab = "Probability", prob = TRUE, main = "Histogram of normal deviates")
       points(density(x), type = "l", col = "red")
     } else if(x == 2) {
        par(mfrow = c(1, 1))       
        source("examples/source_109.R")
     } else if(x == 3) {
       library(lattice)                   
       data(mtcars)
         # make certain to print or nothing will appear.
       print(xyplot(mpg ~ disp | cyl, mtcars))
     } else if(x == 4) {
        x = rnorm(1000)
        canvas$par(mfrow = c(1, 2))
        canvas$hist(x, xlab = "Normal deviates", ylab = "Probability", prob = TRUE, main = "Histogram of normal deviates")
        canvas$points(density(x), type = "l", col = "red")
        canvas$boxplot(x)
     } else {
        wx()
        library(lattice)                   
        data(mtcars)
        print(xyplot(mpg ~ disp | cyl, mtcars, layout = c(3, 1)))
     }
}


init =
function(app)
{
  library(RwxDevice)

  f = RFrame("Embedded RwxDevice test", size = c(600, 800))
  sz = wxBoxSizer(wxHORIZONTAL)

  canvas = RwxCanvas(f)
      # Defer until the callback or not? Here we do it now and not at the time.
      # the callback function knows whether it has to do this or if it has already
      # been done via the call canvas$IsRDevice()
  # asWxDevice(canvas)
  
   # If we wanted to use a button to start a new drawing.
   #  b = wxButton(f, wxID_ANY, "Plot")
   #  b$AddCallback(wxEVT_COMMAND_BUTTON_CLICKED, function(ev) doPlot(NULL, plotChoices[1], canvas))

   # The radio buttons are managed by a radioButtonGroup().
   # This could also be done via a wxRadioBox in this case
   # but we get some simplicitly by doing it with our existing R
   # functionality.
   # We give the callback for when any one button is set and
   # some additional arguments to pass to the callback, i.e. canvas.
  group = radioButtonGroup(doPlot, canvas)
  choices = wxBoxSizer(wxVERTICAL)

  sapply(plotChoices,
         function(label) {
            rbtn = wxRadioButton(f, wxID_ANY, label)
            group$add(rbtn, label)
            choices$Add(rbtn, 0, wxEXPAND)
         })
  group$set(plotChoices[1])  # make the first one the active one.

   # Now put the components into the frame.
  sz$Add(canvas, 1, wxEXPAND)  
  sz$Add(choices, 0)

  f$SetSizer(sz)
  sz$SetSizeHints(f)

  f$Show()

  TRUE
}

OnInit()
###RApp(OnInit = init, run = TRUE)

