## Touchlæss XM

A mod for Sony WH1000-XM3, WH1000-XM4 and WH1000-XM5 (experimental) headphones to remove the gesture-based touch controls and add physical buttons.

![Outside view](doc/preview_outside.png)
![Inside view](doc/preview_inside.png)

### Status
The project is not yet ready for use.

#### Case
A design is ready for the first prototype run and test fit against the XM4 chassis.

#### PCB
The design is ready for the first prototype production run, based on a benchtop proof-of-concept.

Boards will not be fabricated before the case is known to be compatible

#### Firmware
Not even started yet. Will likely be implemented using the Arduino bootloader.



### Compatibility
I only have a pair of XM4 to test with, so the design is made to fit them.

#### WH1000-XM3
The XM3 touch board and battery connector appear to be electrically identical to XM4, so the PCB should be compatible. A different case design may be needed.


#### WH1000-XM4
The project is designed for these, so these will be the ones primarily tested. The OEM touch board has a flat cable which Touchlæss is designed to reuse.

The battery uses a 2-pin JST ZH series connector. There is no vertical space inside the case for a matching connector on the board, so I've resorted to soldering a Y-connector onto the Touchlæss pcb.


#### WH1000-XM5
Experimental support is included in the initial board design, but I **do not** own a pair of XM5 and cannot test them. The board shouldn't be able to do any damage to the headphones. If you have a pair of XM5s and would like to help me test the compatibility, feel free to reach out!

At a minimum, the XM5 has a different connector (24-pin FPC instead of 22-pin FFC), and the OEM design doesn't include a loose cable for us to reuse. You will need a suitable flat cable, which is 24-pin FFC with 0.5mm pitch and same-side connectors. [This Würth 687624050002](https://eu.mouser.com/ProductDetail/Wurth-Elektronik/687624050002?qs=P%2FTEqz%252BQfndQFFKLalvVUA%3D%3D) should work, but may not be the proper length.

The battery connector for XM5 is also different, a 3-pin of unknown design. If you have more information about this, let me know!


### Modifications

#### I don't want another USB port
That's OK, it's only needed for development (reprogramming the touchless board without disassembling the headphones). Simply snap the USB connector off from the main board (see perforations) and print yourself a case without a USB block. Set `with_usb=false` in `xm4-cap.scad` to get a case that's closed at the bottom.


#### I don't like how you've placed the buttons
That's no problem! Snap them off of the main board (see perforations) and use the solder points on the front or back to connect your own buttons placed wherever you want them.


#### I don't have a 3D printer
No problem! If you remove the buttons and the USB addition (see above), the touchless board fits inside the OEM ear cup (you have to remove the original touch board first, which may be destructive). Make cuts as needed to mount buttons where you want them, and wire them up to the exposed button solder points on the front or back of the PCB.


#### The case is fine, but I want to reconfigure the buttons
Easiest way to do this is in the firmware. This will be documented once there is firmware. You'll need the (free) Arduino IDE and either the included USB port or a serial cable to program the board after you've made your modifications.

## License
Touchlæss XM © 2025 by Albin Eldstål-Ahrens is licensed under CC BY-NC 4.0 