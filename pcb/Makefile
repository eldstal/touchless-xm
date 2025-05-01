all: have_vrml2scad vrml step scad

vrml:
	for PCB in */*.kicad_pcb; do \
		VRML=$$(basename $$PCB .kicad_pcb).vrml; \
		kicad-cli pcb export vrml --units mm -f --output $$VRML $$PCB; \
	done


step:
	for PCB in */*.kicad_pcb; do \
		STEP=$$(basename $$PCB .kicad_pcb).step; \
		kicad-cli pcb export step --grid-origin -f --output $$STEP $$PCB; \
	done

have_vrml2scad:
	which vrml2scad 2>/dev/null || ( echo "-- ERROR --"; echo "Need vrml2scad."; echo "cargo install --git https://github.com/agausmann/vrml2scad"; exit 1)

scad: have_vrml2scad
	for VRML in *.vrml; do \
		SCAD=$$(basename $$VRML .vrml).scad; \
		vrml2scad < $$VRML > $$SCAD; \
	done
