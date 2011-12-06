PKG_NAME=$(shell grep Package ../DESCRIPTION | sed -e 's/.*: //')

index.html: index.html.in configure
	./configure

include $(OMEGA_HOME)/R/Config/RPackageWebConfig

Rexif.pdf:
	R CMD Rd2dvi -o Rexif.pdf --pdf ../../Rexif

#html
indexInstall: index.html
	scp index.html $(TARGET_DIR)

ANN_EXAMPLE_XML= ../inst/doc/DragNDrop.xml ../inst/doc/wxImageList.xml ../inst/doc/RC++Methods.xml \
             ../inst/examples/menu.xml ../inst/examples/treeCtrl.xml ../inst/examples/xmlTree.xml \
             ../inst/examples/sizerShow.xml ../inst/examples/multiChoiceDialog.xml ../inst/examples/RwxDialog.xml

XML_FILES=$(ANN_EXAMPLE_XML)

ANN_EXAMPLE_FILES=$(ANN_EXAMPLE_XML) $(ANN_EXAMPLE_XML:%.xml=%.pdf) $(ANN_EXAMPLE_XML:%.xml=%.html)  

#IMAGES=$(shell xsltproc $(OMEGA_HOME)/Docs/XSL/getImageRefs.xsl $(ANN_EXAMPLE_XML))

#IMAGE_FILES=$(foreach f, $(ANN_EXAMPLE_XML), $(dir $(f))$(shell xsltproc $(OMEGA_HOME)/Docs/XSL/getImageRefs.xsl $(f)) )
IMAGE_FILES=$(foreach f, $(ANN_EXAMPLE_XML), $(patsubst %,$(dir $(f))%, $(shell xsltproc $(OMEGA_HOME)/Docs/XSL/getImageRefs.xsl $(f)) ))

images:
	@echo "$(IMAGE_FILES)"

annExamples: $(ANN_EXAMPLE_FILES)
	@echo "Created the files?"

shipAnnotatedExamples shipAnnExamples: $(ANN_EXAMPLE_FILES) $(IMAGE_FILES)
	scp $(ANN_EXAMPLE_FILES) ../inst/doc/index.html $(IMAGE_FILES) $(TARGET_DIR)/ExampleDocuments 

%.pdf: %.xml
	$(MAKE) -C $(@D) $(@F)

%.html: %.xml
	$(MAKE) -C $(@D) $(@F)

configure: configure.in
	autoconf
	chmod +x $@

include $(OMEGA_HOME)/R/Config/RPackageWebRules

#include $(OMEGA_HOME)/Config/GNUmakefile.xml
