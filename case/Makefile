MODELS:=xm4-usb xm4-nousb testfit
OUTDIR:=$(PWD)/../dist/case

all: $(MODELS)

%:
	mkdir -p $(OUTDIR)
	openscad -o $(OUTDIR)/$@.stl --info -p xm4-cap.json -P $@ xm4-cap.scad
	
