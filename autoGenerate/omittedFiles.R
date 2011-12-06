#
# The idea here is to take our .cpp file and 
# find out all the files that it includes.
# Then we find out which ones in the wx directory
# were left out.

ignore = paste("wx/", c("access.h", "dde.h", "fmappriv.h", "isqlext.h", "isql.h", "thrimpl.cpp", "xti.h", "wave.h"), sep = "")

if(!file.exists("deps"))
  system("make deps")

deps = readDependencies("deps")
# Only the top-level ones.
prefix = "/usr/local/include/wx-2.6/"
wxFiles = list.files(paste(prefix, "wx", sep = ""), full.names = TRUE)
wxFiles = wxFiles[ ! file.info(wxFiles)$isdir ]

excluded = setdiff(wxFiles, deps)

excluded = gsub(prefix, "", excluded)
excluded = setdiff(excluded, ignore)

paste("#include <", excluded, ">", sep = "", collapse = "\n")

