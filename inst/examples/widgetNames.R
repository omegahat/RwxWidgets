library(RwxWidgets)

# This example illustrates the use of the
# static methods
#     wxWindow_FindWindowBy{Name,Label,Id}
# and also the regular object method wxWindow_FindWindow (using the Id)

# We create three buttons as children of
# There is nothing specific to the fact that this is a very shallow
# widget hierarchy which has the form
#
#                        f
#                    /   |   \
#                   A    B    C
#
# (where A, B, C are the buttons with those labels)
# If we had a deeper hierarchy

init =
function(...)
{
  f = RFrame("Testing names", size = c(500,500))
  f$CreateStatusBar()
  f$SetStatusText("An example of identifying widgets by name, not R variable")

   sizer = wxBoxSizer(wxHORIZONTAL)

   labels = c("A", "B", "C")
   btns = lapply(seq(along = labels),
                 function(i) {
                   b = wxButton(f, id = 100 + i, labels[i], name = tolower(labels[i]))
                   sizer$Add(b, 0)
                   b
                 })

        # This button and callback allows us to see what happens when we have
        # widgets with the smame name and/or id.
        # At least on Linux, this illustrates that when there are widgets
        # with the same name or id or label, we get the "first" one.
        # This might be the first one created, or the "first" in the tree based on the
        # the path used to traverse the tree.
   other = wxButton(f, id = 101, "Other button", name = "a")
   sizer$Add(other, 0)
   other$AddCallback(wxEVT_COMMAND_BUTTON_CLICKED,
                      function(ev) {
                         
                        firstA = wxWindow_FindWindowByLabel("A")
                        byName = wxWindow_FindWindowByName("a")
                        byId = wxWindow_FindWindowById(101)
                        cat("Other\n")
                        print(other)
                        cat("Original/First button created\n")
                        print(btns[[1]])                        
                        cat("Result of finding by label 'A'\n")
                        print(firstA)
                        cat("Result of finding by Id 101\n")                        
                        print(byId)
                        cat("Result of finding by Name 'a'\n")                                                
                        print(byName)

                        TRUE
                      })
  
  
   btns[[1]]$AddCallback(wxEVT_COMMAND_BUTTON_CLICKED,
                          function(ev) {
                             tmp = wxWindow_FindWindowByName("a")
                             print(tmp)
                               # here we are calling a static method wxWindow_FindWindowByName
                               # but as if it were a regular object method. The staticMethod
                               # attribute on the definition of the function allows the $
                               # method for wxObject to discard the 'this' in the actual call.
                             print(f$FindWindowByName("a"))
                             cat("Label on button named 'a' = ", tmp$GetLabel(), "\n")
                             print(wxWindow_FindWindowByName("b"))
                             print(btns[1:2])

                           
                               # this is the non-static method which uses f as the parent
                               # of the sub-tree to search.
                             b = f$FindWindow(102)
                             cat("Label for 'b' =", b$GetLabel(), "\n")
                          })


  
   f$SetSizer(sizer)
   sizer$SetSizeHints(f)

   f$Show()

   TRUE
}  

RApp(OnInit = init, run = TRUE)
