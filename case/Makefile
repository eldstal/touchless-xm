MODELS:=xm4-usb xm4-nousb xm4-testfit xm4-buttons
OUTDIR:=$(PWD)/../dist/case

all: $(MODELS)

.PHONY: $(MODELS)
$(MODELS):
	mkdir -p $(OUTDIR)
	openscad --backend=manifold -o $(OUTDIR)/$@.stl -p xm4-cap.json -P $@ xm4-cap.scad
	
