OUTDIR:=$(PWD)/../dist/pcb

#
# make bom
# make gerber
# make scad
# make vrml
# make step
#

all: gerber bom


gerber:
	for PCB in tobo/tobo*.kicad_pcb; do \
		GRBDIR=tobo-gerbers; \
		GRBZIP=tobo-gerbers.zip; \
		rm -r "$(OUTDIR)/$${GRBDIR}/"; \
		rm "$(OUTDIR)/$${GRBZIP}"; \
		mkdir -p "$(OUTDIR)/$${GRBDIR}/"; \
		kicad-cli pcb export gerbers -o "$(OUTDIR)/$${GRBDIR}" \
			--layers "F.Cu,B.Cu,F.Paste,B.Paste,F.Silkscreen,B.Silkscreen,F.Mask,B.Mask,Edge.Cuts" \
			--exclude-value \
			$${PCB}; \
		(cd "$(OUTDIR)" && zip -r "$${GRBZIP}" "$${GRBDIR}"); \
	done

bom:
	for SCH in tobo/tobo*.kicad_sch; do \
		BOM="$(OUTDIR)/tobo-bom.csv"; \
		kicad-cli sch export bom -o "$${BOM}" \
			--preset "PCBway" \
			$${SCH}; \
	done




#
# The rules below are just for the CAD preview of the board
# They are not needed for fabrication.
#


vrml:
	mkdir -p $(OUTDIR)
	for PCB in tobo/tobo*.kicad_pcb; do \
		VRML=$(OUTDIR)/$$(basename $$PCB .kicad_pcb).vrml; \
		kicad-cli pcb export vrml --units mm -f --output $$VRML $$PCB; \
	done


step:
	mkdir -p $(OUTDIR)
	for PCB in tobo/tobo*.kicad_pcb; do \
		STEP=$(OUTDIR)/$$(basename $$PCB .kicad_pcb).step; \
		kicad-cli pcb export step --grid-origin -f --output $$STEP $$PCB; \
	done

have_vrml2scad:
	which vrml2scad 2>/dev/null || ( echo "-- ERROR --"; echo "Need vrml2scad."; echo "cargo install --git https://github.com/agausmann/vrml2scad"; exit 1)

scad: have_vrml2scad vrml
	mkdir -p $(OUTDIR)
	for VRML in $(OUTDIR)/*.vrml; do \
		SCAD=$(OUTDIR)/$$(basename $$VRML .vrml).scad; \
		vrml2scad < $$VRML > $$SCAD; \
	done
