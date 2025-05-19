MODELS:=xm4-oem xm4-usb xm4-nousb xm4-testfit xm4-parts xm4-testclearance
OUTDIR:=$(PWD)/../dist/case

all: $(MODELS)

.PHONY: $(MODELS)
$(MODELS):
	mkdir -p $(OUTDIR)
	openscad --backend=manifold -o $(OUTDIR)/$@.stl -p xm4-cap.json -P $@ xm4-cap.scad
	
