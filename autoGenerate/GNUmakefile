target:
-include local.config

#include $(OMEGA_HOME)/Config/GNUmakefile.config
#include $(OMEGA_HOME)/Config/GNUmakefile.xml

WX_CFLAGS=$(shell wx-config --cxxflags)

#CXX=/usr/bin/g++

#PREFIX=/tmp/wxWidgets/

mapping.html: mapping.xml

CPP_FILES=$(wildcard *.cpp)
TUS=$(CPP_FILES:%=$(PREFIX)%.tu)

all: $(TUS)

deps: wx.cpp
	$(CXX) -M $(WX_CFLAGS) $< > $@

localDeps: wx.cpp
	$(CXX) -MM $(WX_CFLAGS) $< > $@



$(PREFIX)%.cpp.tu: $(PREFIX)%.cpp
	(cd $(@D) ; $(CXX) -c $(WX_CFLAGS) -fdump-translation-unit $< -o /dev/null)

$(PREFIX)%.cpp.E: $(PREFIX)%.cpp
	(cd $(@D) ; $(CXX) -E $(WX_CFLAGS) -fdump-translation-unit $< -o $@)

include $(OMEGA_HOME)/Config/GNUmakefile.rules

code tmp/RwxBindings.cpp: run.R
	R --vanilla < run.R

target tmp/RwxBindings.o: tmp/RwxBindings.cpp 
	(cd tmp ; R CMD COMPILE RwxBindings.cpp)


tmp/RwxBindings.cpp.E: 	tmp/RwxBindings.cpp
	g++ -E -I. -I/home/duncan/Projects/R-devel/include -I/home/duncan/Projects/R-devel/include -I/usr/local/lib/wx/include/gtk2-unicode-release-2.6 -I/usr/local/include/wx-2.6 -DGTK_NO_CHECK_CASTS -D__WXGTK__ -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -DNO_GCC_PRAGMA  -I.. -I/home/duncan/Projects/org/omegahat/R/RAutoGenRunTime/inst/include -Wno-deprecated -Wno-deprecated-declarations -I/usr/local/include    -fpic  -g $< > $@

include $(DYN_DOCS)/inst/Make/Makefile
