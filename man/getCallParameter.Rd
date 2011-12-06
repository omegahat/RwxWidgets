\name{getCallParameter}
\alias{getCallParameter}
\title{ ~~function to do ... ~~ }
\description{
  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
getCallParameter(tag, envir = globalenv())
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{tag}{ ~~Describe \code{tag} here~~ }
  \item{envir}{ ~~Describe \code{envir} here~~ }
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
function (tag, envir = globalenv()) 
{
    el = wxHtmlTag_GetChildren(tag, FALSE)
    while (!is.null(el)) {
        tagName = wxHtmlTag_GetName(el)
        if (tagName == "PARAM" && wxHtmlTag_GetParam(el, "name") == 
            "call") {
            txt = wxHtmlTag_GetParam(el, "value")
            cat("Call parameter ", tagName, "\n")
            return(txt)
        }
        el = wxHtmlTag_GetNextSibling(el)
    }
    return(NULL)
  }
}
% Add one or more standard keywords, see file 'KEYWORDS' in the
% R documentation directory.
\keyword{ ~kwd1 }
\keyword{ ~kwd2 }% __ONLY ONE__ keyword per line
