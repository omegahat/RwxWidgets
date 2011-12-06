wxHtmlWindow =
function(parent, id = wxID_ANY, OnLinkClicked = NULL, pos = wxDefaultPosition, size = wxDefaultSize,
           style = wxHW_DEFAULT_STYLE, name = "htmlWindow")
{
  .Call("R_wxHtmlWindow_new", parent, id, OnLinkClicked, pos, size, as.numeric(style), name)
}  

wxHtmlWindow_LoadPage =
function(html, page)
{
  .Call("R_wxHtmlWindow_LoadPage", html, as.character(page))
}

wxHtmlWindow_AppendToPage =
function(html, page)
{
  .Call("R_wxHtmlWindow_AppendToPage", html, as.character(page))
}


wxHtmlWindow_SetPage =
function(html, content)
{
  .Call("R_wxHtmlWindow_SetPage", html, as.character(content))
}

wxHtmlWindow_SetRelatedFrame =
function(html, parent, title)
{
  .Call("R_wxHtmlWindow_SetPage", html, parent, as.character(title))
}


wxHtmlWindow_GetParser =
function(html)
{
  .Call("R_wxHtmlWindow_GetParser", html)
}


wxHtmlWindow_AddTagHandler =  #XXX remove this.
  wxHtmlParser_AddTagHandler  =
function(parser, handler)
{
  .Call("R_wxHtmlWinParser_AddTagHandler", parser, handler)
}

wxHtmlParser_PushTagHandler  =
function(parser, handler, tags)
{
  .Call("R_wxHtmlParser_PushTagHandler", parser, paste(handler, collapse = ","))
}

wxHtmlParser_PopTagHandler  =
function(parser)
{
  .Call("R_wxHtmlParser_PopTagHandler", parser)
}



RwxHtmlWinTagHandler = RwxHtmlWinTagHandler_new =
function(tags, handler)
{
  tags = toupper(tags)
  if(length(tags) > 1)
    paste(tags, sep = ",")
  .Call("R_RwxHtmlWinTagHandler_new", tags, handler)
}

wxHtmlParser_AddText =
function(parser, text)
  .Call("R_wxHtmlParser_AddText", parser, paste(text, collapse = " "))



wxHtmlParser_GetWindow =
function(parser)
  .Call("R_wxHtmlParser_GetWindow", parser)

wxHtmlParser_GetSource =
function(parser)
  .Call("R_wxHtmlParser_GetSource", parser)

wxHtmlParser_GetContainer =
function(parser)
   .Call("R_wxHtmlParser_GetContainer", parser)

wxHtmlParser_GetCharWidth =
function(parser)
   .Call("R_wxHtmlParser_GetCharWidth", parser)

wxHtmlParser_GetCharHeight =
function(parser)
   .Call("R_wxHtmlParser_GetCharWidth", parser)

wxHtmlParser_GetDC  =
function(parser)
{
  .Call("R_wxHtmlParser_GetDC", parser)
}


wxHtmlWidgetCell_new =
function(window, float = 0)  
  .Call("R_wxHtmlWidgetCell_new", window, as.integer(float))

wxHtmlContainerCell_InsertCell =
function(container, widget)  
  .Call("R_wxHtmlContainerCell_InsertCell", container, widget)


wxHtmlWordCell =
function(word, dc)
{
  .Call("R_wxHtmlWordCell_new", as.character(word), as(dc, "wxDC"))
}



htmlViewer =
  #
  # An experimental wx "application" which one can call to display an HTML document
  # in its own window.
  # Based on code from examples/htmlparser.R

  # Bugs:
  #   Need to get the images for all types working
  #
function(doc = character(), linkCB = NULL, tagHandlers = htmlTagHandlers(),
         title = "HTML Viewer",
         size = c(400, 700),
         run = FALSE,  app = NULL # RApp(OnInit = OnInit)  
        )
{
  html <- NULL

       # Make certain all the image handlers are available.
#  .Call("R_wxInitAllImageHandlers", PACKAGE = "RwxWidgets")
  
  OnInit =
  function(...) {
     f =  RFrame(title, size = size)  # c(800, 600) - this causes problems!

     html <<- createHtmlViewer(f, doc, linkCB, tagHandlers)
     f$Show()     

     TRUE
  }

  if(is.null(app))
    OnInit()

  if(run) 
    wxEntry()
  
  list(html = function() html)
}  


createHtmlViewer =
function(parent, doc = character(), linkCB = NULL, tagHandlers = htmlTagHandlers())
{
     html <- wxHtmlWindow(parent, as.integer(-1), linkCB)

    if(length(tagHandlers)) {
       parser = html$GetParser()

       lapply(names(tagHandlers),
              function(id) {
                h = RwxHtmlWinTagHandler(id, tagHandlers[[id]])
                wxHtmlParser_AddTagHandler(parser, h) 
              })
     }


     if(length(doc)) {
       if(file.exists(doc))
         wxHtmlWindow_LoadPage(html, path.expand(doc))
       else
         wxHtmlWindow_SetPage(html, doc)
     }

     html
}

