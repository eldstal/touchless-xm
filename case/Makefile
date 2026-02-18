
OUTDIR:=$(PWD)/../dist/case
RELEASEDIR=$(PWD)/../release/case
DOCDIR:=$(PWD)/../doc

MODELS_CAP_LOGO:=\
		xm4-usb \
		xm4-nousb

MODELS_CAP_NOLOGO:=\
		xm4-oem \
		xm4-nologo-nousb \
		xm4-nologo-usb

MODELS_PARTS:=\
		xm4-nologo-parts \
		xm4-parts

MODELS_TEST:=\
		xm4-test-mount \
		xm4-test-clearance \
		xm4-test-buttons \
		dummy-pcb

MODELS:=$(MODELS_CAP_LOGO) $(MODELS_CAP_NOLOGO) $(MODELS_PARTS) $(MODELS_TEST)

CAPS:=$(filter-out %-test% %dummy-% %-parts%,$(MODELS))

all: $(MODELS) screenshots

release: $(models)

.PHONY: $(MODELS)
$(MODELS):
	mkdir -p $(OUTDIR)
	openscad --backend=manifold -o $(OUTDIR)/$@.stl -p xm4-cap.json -P $@ xm4-cap.scad

.PHONY: release
release:
	mkdir -p "$(RELEASEDIR)"
	for CAP in $(MODELS_CAP_NOLOGO); do \
		zip --junk-paths $(RELEASEDIR)/case-$${CAP}.zip $(OUTDIR)/xm4-nologo-parts.stl $(OUTDIR)/$${CAP}.stl; \
	done
	for CAP in $(MODELS_CAP_LOGO); do \
		zip --junk-paths $(RELEASEDIR)/case-$${CAP}.zip $(OUTDIR)/xm4-parts.stl $(OUTDIR)/$${CAP}.stl; \
	done

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
