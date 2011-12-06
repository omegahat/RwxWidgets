library(RwxWidgets)
library(RwxDevice)
library(bitops)

wxRB_GROUP =  as.integer(0x0004)

OnInit = function(app) {

  deviceNumbers <- integer()

# Possible distributions 
  distList = c("Normal", "Uniform", "Beta", "Exponential")
  probDist <- distList[1]
  
# Values for the sample size, number of repeats in sumulation, sample statistics
  curStats <- NULL
  sampleSize <- 25
  sampleRepeats <- 1000
  
# Possible Statistics
  statList = c("mean", "median", "sd", "min")
  initialize =
    function() {
      statType <<- statList[1]
      probDist <- distList[1]      
      sampleSize <<- 25
      sampleRepeasts <<- 1000
      curStats <<- NULL
      curSimView <<- dispTypes[1]
#      showDist(probDist)
      
      TRUE
    }


# Display types for the simulation results
  dispTypes = c("Histogram", "Normal Quantile")
  curSimView = dispTypes[1]

  runSim = function(n = sampleSize, repeats = sampleRepeats, 
          distribution = probDist, stat = statType)  {

    #this subroutine computes the sample statistics stat based on
    # repreated sampling of a sample of size samplesize from a given distribution 

    num = n * repeats
    if (distribution == "Beta") {
      samples = rbeta(num, shape1 = 3, shape2 = 2)
      dname = "Beta(3,2)" 
    } 
    else if (distribution == "Normal") {
      samples = rnorm(num)
      dname = "Standard Normal" 
    }
    else if (distribution == "Uniform") {
      samples = runif(num)
      dname = "Uniform(0, 1)" 
    }
    else if (distribution == "Exponential") {
      samples = rexp(num, rate = 2)
      dname = "Exponential(2)" 
    }
    else stop("Invalid distribution")

    samples = matrix(samples, nrow = repeats)
    curStats <<- apply(samples, 1, get(stat, mode="function") )

    return(list(stats = curStats, dname = dname) )
  }

showSim = 
function(stats = curStats, dname = probDist, samples = sampleSize, type = statType, view = curSimView, numBins = 20)
 {

    # This function is called by the handler startSim.
    # It is in charge of plotting the empirical sampling distribution.

    center = mean(stats)
    spread = sd(stats)
    
    dev.set( deviceNumbers["simulation"] )
    main = paste("Sampling Distribution of", type, "\n for", 
            samples, "sample draws from the", dname)

    if (view == "Histogram") {
       xlab = paste("Values of", type, "statistic")
       hist(stats, breaks = numBins, col="red", freq = FALSE,
          main = main, xlab = xlab, ylab = "density") 
       curve(dnorm(x, center, spread), from = min(stats), max(stats), 
                      n = 500, col = "blue", add = TRUE) 
    }

    else if (view == "Normal Quantile") {
       ylab = paste("Values of", type, "statistic")
       qqnorm(stats, ylab = ylab)
    }

    else stop("Incorrect View")

    return(c(center = center, spread = spread))
  }

  showDist = function(dist = probDist) {
  # Plots the chosen probability distibution in the "sample" panel.
  
    ylab = "Density"
    dev.set( deviceNumbers["sample"] )

    if (dist == "Normal") 
         curve(dnorm, from = -3, to = 3, xlab = "Standard Normal", col = "blue", ylab=ylab)
    else if (dist == "Exponential") 
         curve(dexp(x, rate = 2), from = 0, to =10, xlab = "Exponential(2)", col = "blue", ylab= ylab)
    else if (dist == "Uniform") 
         curve(dunif, from = 0, to = 1, xlab = "Uniform(0, 1)", col = "blue", ylab = ylab)
    else if (dist == "Beta") 
         curve(dbeta(x, shape1 = 3, shape2 = 2), from = 0, to = 1, xlab = "Beta(3, 2)", col = "blue", ylab = ylab)
    else {
      stop("Invalid choice of probability distribution: ", dist)  
    }
  }

  changeDist = function(event) {
     # This handler is called when the distribution is changed.

      # Get dist from the list control
    obj = event$GetEventObject()
    curPosition =  obj$GetSelections()

    if (curPosition != wxNOT_FOUND) 
        dist = distList[curPosition + 1]
        # Check to see if the distribution selected has really changed or not.
        if (probDist != dist) { 
          showDist(dist)
          probDist <<- dist
        }
  }

  changeStat = function(event) {
  # This handler is called when the statistic is changed.
  # I would prefer to get this information at the time the button is selected
  # but the closures don't seem right for it.

  # Get statistic from the list box control
     obj = event$GetEventObject()
     curPosition =  obj$GetSelections()

    if (curPosition != wxNOT_FOUND) 
         statType <<- statList[curPosition + 1]
  }

  changeSimView = function(event) {
  # This handler is called when the graphic for the summary statistics is changed.
  # Look through the array of radio buttons to determine which one changed. 

     for(btn in names(radioViews)) {
         if ( radioViews[[btn]]$GetValue() & (btn != curSimView) ) {
            curSimView <<- btn
            showSim() 
         }
     }
  }

  changeSize = function(event, w) {
  # This handler is called when the sample size is changed.
  # I would prefer to get this information at the time the button is selected
  # but the closures don't seem right for it.

  # Get sample size from the spin control
     # obj = event$GetEventObject()
     sampleSize <<-  w$GetValue()    
  }

  startSim = function(event) {
  # This handler is called when the "Simulate" button is pushed.
  # It is supposed to go off and pick up the values for the sample size and statistic
  # Instead, we already have the values for these because of the call backs. 

    statsAndMain = runSim(n = sampleSize, distribution = probDist, stat = statType)

    simStats = showSim(stats = statsAndMain$stats, dname = statsAndMain$dname)

   # Update the labels in the panel below the grphics device
    simMean$SetLabel(paste("Average: ", simStats$center))
    simSD$SetLabel(paste("Standard Deviation: ", simStats$spread))
  }

  
#This function builds the panel with the sampling controls where the user
# specifies the smaple size, distribution, and stample stat

  createSamplingControls =
    function(win) {

      controlPanel = wxPanel(win)
      controlSz = wxBoxSizer(wxHORIZONTAL)

      distnChoice = wxListBox(controlPanel, wxID_ANY, wxLB_SINGLE, choices = distList)
      distnChoice$AddCallback(wxEVT_COMMAND_LISTBOX_SELECTED, changeDist)
     
      sampleSizeChoice = wxSpinCtrl(controlPanel, wxID_ANY, value = sampleSize, min = 1, max = 100000, initial = 10)
      sampleSizeChoice$AddCallback(wxEVT_COMMAND_SPINCTRL_UPDATED, changeSize, sampleSizeChoice)

# I would like this to be a choice box, but need to check if it exists
      statChoice = wxListBox(controlPanel, wxID_ANY, wxLB_SINGLE, choices = statList)
      statChoice$AddCallback(wxEVT_COMMAND_LISTBOX_SELECTED, changeStat)
     
      simulate = wxButton(controlPanel, wxID_ANY, "Simulate")

      simulate$AddCallback(wxEVT_COMMAND_BUTTON_CLICKED, startSim) 

      controlSz$Add(distnChoice, 1)
      controlSz$Add(sampleSizeChoice, 1)      
      controlSz$Add(statChoice, 1)      
      controlSz$Add(simulate, 0, wxLEFT, 10)


      controlPanel$SetSizer(controlSz)
      controlSz$SetSizeHints(controlPanel)

      controlPanel
    }

# This function creates the lefthand panel where the parameters for the
# simulation are specified.
  createSamplingArea =
     function(win) {

# Panel to place inside the lefthand splitter window
# The panel contains a vertical sizer box which will hold the
# graphics device that shows the distribution and the controls
  
          panel = wxPanel(win)
          sz = wxBoxSizer(wxVERTICAL)

          dev = RwxCanvas(panel)
          asWxDevice(dev)
          deviceNumbers["sample"] <<- dev.cur()
          sz$Add(dev, as.integer(5), c(wxEXPAND, wxALL), as.integer(10))

         controls = createSamplingControls(panel)
         sz$Add(controls, 1, wxEXPAND)

         panel$SetSizer(sz)          
         sz$SetSizeHints(panel)

         panel
  }


  createSimulationView =
    function(win) {

      simViewPanel = wxPanel(win)
      simViewSz = wxBoxSizer(wxVERTICAL)

      simMean <<- wxStaticText(simViewPanel, wxID_ANY, style = wxALIGN_LEFT, 
                   label = "Average: " )
      simSD <<- wxStaticText(simViewPanel, wxID_ANY, style = wxALIGN_LEFT, 
                   label = "Standard Deviation: " )

      simViewSz$Add(simMean, 1)
      simViewSz$Add(simSD, 1)

      
      radioViews <<- list()

      lapply(dispTypes, function(label) {
         if (label == dispTypes[1])
               radioViews[[label]] <<- wxRadioButton(simViewPanel, wxID_ANY, label, style = wxRB_GROUP)
         else 
              radioViews[[label]] <<- wxRadioButton(simViewPanel, wxID_ANY, label)
         radioViews[[label]]$AddCallback(wxEVT_COMMAND_RADIOBUTTON_SELECTED, changeSimView)
         simViewSz$Add(radioViews[[label]], 1)
      })

      radioViews[[dispTypes[1]]]$SetValue(TRUE) 


      simViewPanel$SetSizer(simViewSz)
      simViewSz$SetSizeHints(simViewPanel)

      simViewPanel
    }
  
  
  createSimulationArea =
    function(win) {
          panel = wxPanel(win)
          sz = wxBoxSizer(wxVERTICAL)

          dev = RwxCanvas(panel)
          asWxDevice(dev)
          deviceNumbers["simulation"] <<- dev.cur()
          sz$Add(dev, as.integer(5), c(wxEXPAND), as.integer(10))

         summaries = createSimulationView(panel)
         sz$Add(summaries, 1, wxEXPAND)

         panel$SetSizer(sz)          
         sz$SetSizeHints(panel)

         panel
    }


  
  top = RFrame("CLT Lab",  size = as.integer(c(1000, 800)))

  top$CreateStatusBar()
  top$SetStatusText("Select the details of a distribution and generate samples from it.")

  split = wxSplitterWindow(top, wxID_ANY)

  left = createSamplingArea(split)
  right = createSimulationArea(split)
  
  split$SplitVertically(left, right)

  top$Show()

  
  createExternalDevices = function() {
    wx()
    deviceNumbers["simulation"] <<- dev.cur()
    wx()
    deviceNumbers["sample"] <<- dev.cur()
  }

#  createExternalDevices()
  
  initialize()
  
  TRUE         
}

OnInit()
#RApp(OnInit = OnInit, run = TRUE)
