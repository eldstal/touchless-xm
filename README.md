## Touchlæss XM

A mod for Sony WH1000-XM3, WH1000-XM4 and WH1000-XM5 (experimental) headphones to remove the gesture-based touch controls and add physical buttons.

![Outside view](doc/preview_outside.png)
![Inside view](doc/preview_inside.png)

### Status
The project is not yet ready for use.

#### Case
A design is ready for the first prototype run and test fit against the XM4 chassis. It will be 3D-printable, but you can probably get even better quality and finish by ordering it from a fabrication company.

#### PCB
The design is ready for the first prototype production run, based on a benchtop proof-of-concept.

Boards will not be fabricated before the case is known to be compatible. Once I've made a first production run, I'll also upload all the files you need to order your own board from a vendor such as PCBWay.

#### Firmware
Not even started yet. Will likely be implemented using the Arduino bootloader. USB support (only for programming) is already included in the main board.



### Compatibility
I only have a pair of XM4 to test with, so the design is made to fit them.

#### WH1000-XM2 (Not compatible!)
The service manual suggests that the XM2 uses a 12-pin cable for its touch board. As such, the touchless design won't be directly compatible.
If you're *really* lucky, there may be an offset placement in the XM4 connector that happens to work, but I wouldn't want to test it.

If you have an XM2 and would like to help me figure out the pinout of the touch board, let me know!

#### WH1000-XM3 (Probably compatible)
The XM3 touch board and battery connector appear to be electrically identical to XM4, so the PCB should be compatible. A different case design may be needed.


#### WH1000-XM4 (Compatible)
The project is designed for these, so these will be the ones primarily tested. The OEM touch board has a flat cable which Touchlæss is designed to reuse.

The battery uses a 2-pin JST ZH series connector. There is no vertical space inside the case for a matching connector on the board, so I've resorted to soldering a Y-connector onto the Touchlæss pcb. Separate from the PCB BOM, you'll need one male and one female JST ZH-2 connector and some red/black cables.


#### WH1000-XM5 (Possibly compatible)
Experimental support is included in the initial board design, but I **do not** own a pair of XM5 and cannot test them. The XM5 connector is entirely based on reverse-engineering of incomplete photos, so I may have made a mistake! The Touchless board shouldn't be able to do any damage to the headphones. If you have a pair of XM5s and would like to help me test the compatibility, feel free to reach out!

At a minimum, the XM5 has a different connector (24-pin FPC instead of 22-pin FFC), and the OEM design doesn't include a loose cable for us to reuse. You will need a suitable flat cable, which is 24-pin FFC with 0.5mm pitch and same-side connectors. [This Würth 687624050002](https://eu.mouser.com/ProductDetail/Wurth-Elektronik/687624050002?qs=P%2FTEqz%252BQfndQFFKLalvVUA%3D%3D) should work, but may not be the proper length.

The battery connector for XM5 is also different, a 3-pin of unknown design. If you have more information about this, let me know!


### Modifications

#### Will this work for other headphones from other manufacturers?
**Highly** unlikely. At the very least, you'll need to figure out the pinout for the touch sensor board. Most likely there will be other things that need tuning as well. If you want to make something like touchless for a different headset, take a look at the [technical documentation](doc/README.md) for some pointers on how Touchless works.

#### I don't want another USB port
That's OK, it's only needed for development (reprogramming the Touchless board without disassembling the headphones). Simply snap the USB connector off from the main board (see perforations) and print yourself a case without a USB block. Set `with_usb=false` in `xm4-cap.scad` to get a case that's closed at the bottom.


#### I don't like how you've placed the buttons
That's no problem! Snap them off of the main board (see perforations) and use the solder points on the front or back to connect your own buttons placed wherever you want them. If you're keen on PCB design, it's not that hard to redesign the PCB for button placement (or add/remove buttons as needed).


#### I don't have a 3D printer
No problem! If you remove the buttons and the USB addition (see above), the touchless board fits inside the OEM ear cup (you have to remove the original touch board first, which may be destructive). Make cuts as needed to mount buttons where you want them, and wire them up to the exposed button solder points on the front or back of the PCB.


#### The case is fine, but I want to reconfigure the buttons
Easiest way to do this is in the firmware. This will be documented once there is firmware. You'll need the (free) Arduino IDE and either the included USB port or a serial cable to program the board after you've made your modifications.


#### I want buttons for other features
That won't be possible, sorry. Touchlæss only works by simulating touches and swipes, so it can only do what the headphones allow you to do with the touch panel.


#### I want the buttons on the left cup
That will be an adventure. Touchlæss interfaces with the board in the right cup, so you'll need to run wires across the headband to get to the other side. Not impossible, but certainly a lot of work.

## License
Touchlæss XM © 2025 by Albin Eldstål-Ahrens is licensed under Creative Commons BY-NC 4.0 

This means you are free to use, modify, distribute, remix, redesign the project however you wish as long as you
1. Do not do it for commercial purposes.
2. Credit the original project where appropriate

If you want to order some boards and share the cost with your friends, go for it! Just don't open some web shop and sell my stuff, please.