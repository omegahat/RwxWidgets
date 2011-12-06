\name{createHtmlViewer}
\alias{createHtmlViewer}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ ~~function to do ... ~~ }
\description{
  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
createHtmlViewer(doc, parent, linkCB = NULL, tagHandlers = htmlTagHandlers())
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{doc}{ ~~Describe \code{doc} here~~ }
  \item{parent}{ ~~Describe \code{parent} here~~ }
  \item{linkCB}{ ~~Describe \code{linkCB} here~~ }
  \item{tagHandlers}{ ~~Describe \code{tagHandlers} here~~ }
}
\details{
  ~~ If necessary, more details than the description above ~~
}
\value{
  ~Describe the value returned
  If it is a LIST, use
  \item{comp1 }{Description of 'comp1'}
  \item{comp2 }{Description of 'comp2'}
  ...
}
\references{ ~put references to the literature/web site here ~ }
\author{ ~~who you are~~ }
\note{ ~~further notes~~ 

 ~Make other sections like Warning with \section{Warning }{....} ~
}
\seealso{ ~~objects to See Also as \code{\link{help}}, ~~~ }
\examples{
##---- Should be DIRECTLY executable !! ----
##-- ==>  Define data, use random,
##--	or do  help(data=index)  for the standard data sets.

## The function is currently defined as
function (doc, parent, linkCB = NULL, tagHandlers = htmlTagHandlers()) 
{
    html <- wxHtmlWindow(parent, as.integer(-1), linkCB)
    if (length(tagHandlers)) {
        parser = html$GetParser()
        lapply(names(tagHandlers), function(id) {
            h = RwxHtmlWinTagHandler(id, tagHandlers[[id]])
            wxHtmlWindow_AddTagHandler(parser, h)
        })
    }
    if (file.exists(doc)) 
        wxHtmlWindow_LoadPage(html, path.expand(doc))
    else wxHtmlWindow_SetPage(html, doc)
    html
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
