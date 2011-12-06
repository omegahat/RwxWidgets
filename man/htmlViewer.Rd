\name{htmlViewer}
\alias{htmlViewer}
\title{A top-level, blocking "application" for viewing an HTML document}
\description{
  This function creates a top-level window and displays an HTML document
  within it and runs the wxWidgets event loop.
}
\usage{
htmlViewer(doc, linkCB = NULL, tagHandlers = htmlTagHandlers(), title = "HTML Viewer", run = FALSE, app = RApp(OnInit = OnInit))
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{doc}{the document to be displayed, either a file name or the
    HTML content itself}
  \item{linkCB}{ a function which is to be called when the user clicks
    on a link in the HTML document.}
  \item{tagHandlers}{}
  \item{title}{a string giving the title for the top-level window's frame}
  \item{run}{a logical value indicating whether to run the event loop}
  \item{app}{the wxApp object that is used as the sole application for
    this R session}
}
\details{
}
\value{
}
\references{}
\author{Duncan Temple Lang}

\seealso{ ~~objects to See Also as \code{\link{help}}, ~~~ }
\examples{

}
\keyword{IO}
\concept{document}
