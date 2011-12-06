# The idea is to display several examples
# within an HTML document with tabs for the
# different examples
# Each example has the title and description
# displayed in an HTML widget.
#
#

# Note.
# Almost working, but the notebook is not behaving quite right.
# We cannot select the second tab and sometimes the tabs are not
# drawn after a while.

library(RwxWidgets)
library(bitops)

# fileName = system.file("exampleData", "basic.xml", package="XML")

exampleHandlers =
function() {

      # shared by the two handler functions.  <example>
      # adds a page to it.
 notebook = NULL
      # create the notebook and then run the ParseInner
 examples = function(this, node, parser) {
    parent = wxHtmlParser_GetWindow(parser)
    # parent = RFrame()
    
    notebook <<- wxNotebook(parent, size = c(400, 500))
  
    insertEmbeddedComponent(notebook, parser)
    this$ParseInner(node)
    notebook$Show()

    TRUE
  }

  eg = function(handler, node, parser) {

        # top-level container for the html widget, text and html widget
        # We could use a single HTML widget and 
    page =  wxPanel(notebook)
    sizer = wxBoxSizer(wxVERTICAL)
    
    kids = node$GetChildren(all = TRUE)

       # grab the contents of the description node and put them into a new
       # html widget
    desc = wxHtmlWindow(page)
    desc$SetPage(kids[["description"]]$GetContent(parser)) 
    sizer$Add(desc, 1, c(wxEXPAND, wxALL))

      # Get the code for this example
    code = kids[["rcode"]]$GetContent(parser)

      # display it in a text control widget
    codeText = wxTextCtrl(page, code, style = wxTE_MULTILINE)
      # Increase the font. 
    sizer$Add(codeText, 1, c(wxEXPAND, wxALL))
   
       # evaluate the code in the example
    out = capture.output(eval(parse(text = code), globalenv()))
    out = paste(out, collapse = "\n")

           # Would like to use CDATA here, but it doesn't seem to do the job.
           # so substitute < and > with their named entities.
    out = gsub("<", "&lt;", out)
    out = gsub(">", "&gt;", out)
    out = paste("<HTML><BODY><PRE>", out, "</PRE></BODY></HTML>", sep = "\n")

    output = wxHtmlWindow(page)    
    output$SetPage(out)
    sizer$Add(output, 1, c(wxEXPAND, wxALL))

    page$SetSizer(sizer)
    sizer$SetSizeHints(page)    

    page$Show()
     # now insert the page into the notebook
     # XXX add the tooltip
    notebook$AddPage(page, node$GetParam("id"))

    NULL
  }

 
  rcode =
     # evaluate the code inside a <rcode> node.
     # This won't see those nodes inside the <example>
     # nodes as we don't call Parse_Inner on those.
    function(this, node, parser) {
        code = node$GetContent(parser)
        eval(parse(text = code), globalenv())
    }
 
  list(examples = examples, example = eg, rcode = rcode)
}

htmlViewer("rdocExamples.html",
           tagHandlers = htmlTagHandlers(exampleHandlers()),
           run = TRUE)

