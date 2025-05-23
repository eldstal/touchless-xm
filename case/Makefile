MODELS:=xm4-oem xm4-usb xm4-nousb xm4-parts xm4-test-mount xm4-test-clearance xm4-test-buttons dummy-pcb
OUTDIR:=$(PWD)/../dist/case
DOCDIR:=$(PWD)/../doc

all: $(MODELS) screenshots

.PHONY: $(MODELS)
$(MODELS):
	mkdir -p $(OUTDIR)
	openscad --backend=manifold -o $(OUTDIR)/$@.stl -p xm4-cap.json -P $@ xm4-cap.scad


.PHONY: screenshots
screenshots:
	openscad --backend=Manifold \
		--colorscheme Monotone \
		--camera=3.42,3.69,11.8,223.00,0,152.6,196.1 \
		--imgsize 2048,2048 \
		-o $(DOCDIR)/preview_inside.png \
		-p xm4-cap.json \
		-P xm4-preview \
		xm4-cap.scad
	openscad --backend=Manifold \
		--colorscheme Monotone \
		--camera=-1.45,-0.96,5.25,45.00,0,326.9,196.1 \
		--imgsize 2048,2048 \
		-o $(DOCDIR)/preview_outside.png \
		-p xm4-cap.json \
		-P xm4-preview \
		xm4-cap.scad
