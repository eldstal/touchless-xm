MODELS:=xm4-usb xm4-nousb xm4-testfit
OUTDIR:=$(PWD)/../dist/case

all: $(MODELS)

.PHONY: $(MODELS)
$(MODELS):
	mkdir -p $(OUTDIR)
	openscad -o $(OUTDIR)/$@.stl -p xm4-cap.json -P $@ xm4-cap.scad
	
