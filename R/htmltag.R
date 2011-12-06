wxHtmlTag_GetParent <-
function(tag)
  .Call("R_wxHtmlTag_GetParent", tag)

wxHtmlTag_GetName <-
function(tag)
  .Call("R_wxHtmlTag_GetName", tag)

wxHtmlTag_GetParam <-
function(tag, param, with_commas = FALSE)
  .Call("R_wxHtmlTag_GetParam", tag, as.character(param), as.logical(with_commas))

wxHtmlTag_HasParam <-
function(tag, param)
  .Call("R_wxHtmlTag_HasParam", tag, as.character(param))

wxHtmlTag_HasEnding <-
function(tag)
  .Call("R_wxHtmlTag_HasEnding", tag)


wxHtmlTag_GetContent =
function(tag, parser, fixNewlines = TRUE,
          fixCDATA = TRUE)
{
  src = parser$GetSource()
  start = tag$GetBeginPos()
  ans = .Call("R_wxString_Mid", src, as.numeric(start), as.numeric(tag$GetEndPos1() - start))

  if(fixNewlines)
    ans = gsub("\\\r\\\n", "\\\n", ans)

  if(fixCDATA)  # doesn't handle multiple CDATA sections.
    ans = gsub("<\\!\\[CDATA\\[(.*)\\]\\]>", "\\1", ans)


  ans
}  

wxHtmlTag_GetBeginPos <-
function(tag)
  .Call("R_wxHtmlTag_GetBeginPos", tag)

wxHtmlTag_GetEndPos1 <-
function(tag)
  .Call("R_wxHtmlTag_GetEndPos1", tag)

wxHtmlTag_GetEndPos2 <-
function(tag)
  .Call("R_wxHtmlTag_GetEndPos2", tag)


wxHtmlTag_GetAllParams <-
function(tag, split = TRUE) {
  ans = .Call("R_wxHtmlTag_GetAllParams", tag)
  if(split)
    processHTMLParameters(ans)
  else
    ans
}
wxHtmlTag_GetChildren <-
function(tag, all = FALSE)
  .Call("R_wxHtmlTag_GetChildren", tag, as.logical(all))

wxHtmlTag_GetNextSibling <-
function(tag)
  .Call("R_wxHtmlTag_GetNextSibling", tag)

"[[.HTMLTagChildrenList" =
function(x, i, ...)
{
  if(is.character(i))
    i = toupper(i)
  
  unclass(x)[[i]]
}




wxHtmlTag_GetAttr =
  #
  # Added manually as a way to make this look like xmlGetAttr
  # but this is vectorized.
  #
function(tag, id, default = NULL, converter = NULL)
{
 ans = sapply(seq(along = id),
               function(i) {
                 if(tag$HasParam(id[i])) {
                   tmp = tag$GetParam(id[i])
                   if(!is.null(converter))
                     converter(tmp)
                   else
                     tmp
                 } else {
                   if(length(default))
                      default[[i]]
                   else
                     NULL
                 }
             })

 names(ans) = id
 ans
}  
