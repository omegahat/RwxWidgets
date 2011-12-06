WX_CONFIG=/usr/local/bin/wx-config
wxConstants: wxConstants.cpp
	$(CXX) -o $@ -I../../src $(shell $(WX_CONFIG) --cflags --libs) $<

wxDefines: wxDefines.cpp
	$(CXX) -o $@ -I../../src $(shell $(WX_CONFIG) --cflags --libs) $<
