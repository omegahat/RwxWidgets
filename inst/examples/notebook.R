library(RwxWidgets)

OnInit =
function(...)  
{
  f = RFrame("Notebook example",
             as.integer(c(50, 30)),
             as.integer(Size(450, 450))) # Doesn't size correctly by itself.

  book = wxNotebook(f)
  txt = c(a= "This is the first page.",
          b = "And a second page",
          c = "And a third")


  pages = lapply(names(txt),
                 function(x) {
                   ctrl = wxTextCtrl(book, txt[x])
                   #book$AddPage(ctrl, x)
                   wxNotebook_AddPage(book, ctrl, x)
                   ctrl
                 })
  book$SetSelection(1)

  f$Show()
  list(book = book, pages = pages, frame = f)
}

app = RApp(OnInit = OnInit, run = TRUE)


