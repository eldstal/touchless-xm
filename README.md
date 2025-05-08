# Touchlæss XM

A mod for Sony WH1000-XM2 (experimental), WH1000-XM3, WH1000-XM4 and WH1000-XM5 (experimental) headphones to remove the gesture-based touch controls and add physical buttons.

- [Project Status](#Status)
- [Compatible headsets](#compatibility)
- [Modifications](#modifications)
- [How to program your board](#how-to-program)
- [License](#license)

![Outside view](doc/preview_outside.png)
![Inside view](doc/preview_inside.png)

## Status
The project is not yet ready for use.

### Case
A design is ready for the first prototype run and test fit against the XM4 chassis. It will be 3D-printable, but you can probably get even better quality and finish by ordering it from a fabrication company.

### PCB
The design is ready for the first prototype production run, based on a benchtop proof-of-concept.

Boards will not be fabricated before the case is known to be compatible. Once I've made a first production run, I'll also upload all the files you need to order your own board from a vendor such as PCBWay.

### Firmware
Mostly ready for testing. USB support (only for programming) is already included in the main board. The project uses platform.io and OptiBoot to run an Arduino-based firmware.



## Compatibility
I only have a pair of XM4 to test with, so the design is made to fit them.

### 🟡 Sony WH1000-XM2 (Experimental)
I've laid out the board for experimental support for the XM2. These are the most different out of the bunch, so there are caveats.

⚠️**WARNING**⚠️
The OEM cable will not work, because the XM2 has the touch board's connector at the front. Either turn your Touchlæss upside down or get a slightly longer cable **with opposite side contacts**. Possibly [This Würth 687712100002](https://eu.mouser.com/ProductDetail/Wurth-Elektronik/687712100002?qs=PhR8RmCirEbjmYLiy2w9eg%3D%3D) is suitable.

There is no bespoke connector for the XM2, you need to very carefully position it in the XM4 or XM5 connector using the lines on the PCB.

It's also necessary to modify the firmware pin map slightly, since the Y pins are in the opposite order. Use `--environment xm2` when you compile the firmware.

If you've got a pair of XM2s and want to help me tune the compatibility, let me know!

### 🟡 Sony WH1000-XM3 (Probably compatible)
The XM3 touch board and battery connector appear to be electrically identical to XM4, so the PCB should be compatible. A different case design may be needed.


### 🟢 Sony WH1000-XM4 (Compatible)
The project is designed for these, so these will be the ones primarily tested. The OEM touch board has a flat cable which Touchlæss is designed to reuse.

The battery uses a 2-pin JST ZH series connector. There is no vertical space inside the case for a matching connector on the board, so I've resorted to soldering a Y-connector onto the Touchlæss pcb. Separate from the PCB BOM, you'll need one male and one female JST ZH-2 connector and some red/black cables.


### 🟡 Sony WH1000-XM5 (Possibly compatible)
Experimental support is included in the initial board design, but I **do not** own a pair of XM5 and cannot test them. The XM5 connector is entirely based on reverse-engineering of photos, so I may have made a mistake! The Touchless board shouldn't be able to do any damage to the headphones. If you have a pair of XM5s and would like to help me test the compatibility, feel free to reach out!

At a minimum, the XM5 has a different connector (24-pin FPC instead of 22-pin FFC), and the OEM design doesn't include a loose cable for us to reuse. You will need a suitable flat cable, which is 24-pin FFC with 0.5mm pitch and same-side connectors. [This Würth 687624050002](https://eu.mouser.com/ProductDetail/Wurth-Elektronik/687624050002?qs=P%2FTEqz%252BQfndQFFKLalvVUA%3D%3D) should work, but may not be the proper length.

The battery connector for XM5 is also different, a 3-pin of unknown design. If you have more information about this, let me know!

### 🟡 Sony WH1000-XM6 (Not even released yet)
With any luck, the XM6 touch board will be similar to the XM5. It will be a while before I get my hands on a new high-end headset to test it, though.

If you're getting a pair of XM6 and would like to send me some nice photos of the internals, I'll be very grateful!

### 🔴 Other manufacturers/headsets
**Highly** unlikely. At the very least, you'll need to figure out the pinout for the touch sensor board. Most likely there will be other things that need tuning as well. If you want to make something like touchless for a different headset, take a look at the [technical documentation](doc/README.md) for some pointers on how Touchless works.


## Modifications

#### I don't want another USB port on my headset
That's OK, it's only needed for development (reprogramming the Touchless board without disassembling the headphones). Simply snap the USB connector off from the main board (see perforations) and print yourself a case without a USB block. Set `with_usb=false` in `xm4-cap.scad` to get a case that's closed at the bottom.


#### I don't like how you've placed the buttons
That's no problem! Snap the button portion off of the main board (see perforations) and use the solder points on the front or back to connect your own buttons placed wherever you want them. If you're keen on PCB design, it's not that hard to redesign the PCB for button placement (or add/remove buttons as needed).

There is no need for external resistors etc, just connect a switch between one button contact and the COM and you're good to go.


#### I don't have a 3D printer
No problem! If you remove the buttons and the USB addition (see above), the touchless board should fit inside the OEM ear cup (you have to remove the original touch board first, which may be destructive). Make cuts in the case as needed to mount buttons where you want them, and wire them up to the exposed button solder points on the front or back of the PCB.


#### The case is fine, but I want to reconfigure the buttons
Easiest way to do this is in the firmware. Take a look at [buttonmap.cpp](firmware/tobo/src/buttonmap.cpp) to switch and swap however you like. You'll need the included USB port or a serial cable to program the board after you've made your modifications. Instructions are [down below](#step-2-firmware).


#### I want buttons for other features
That won't be possible, sorry. Touchlæss only works by simulating touches and swipes, so it can only do what the headphones allow you to do with the touch panel.


#### The buttons are too slow!
Yes. There is a significant delay between pushing a button and the headset responding. This isn't something we can control, since Touchlæss simulates touch gestures. If a swipe takes 120ms to perform, the headset can't react sooner than that.


#### I want the buttons on the left cup
That will be an adventure. Touchlæss interfaces with the board in the right cup, so you'll need to run wires across the headband to get to the other side. Not impossible, but certainly a lot of work.


#### I want to make and sell these
That's great! I won't ask for any royalties or whatever. If you do set something up, I'm happy to include a link here so people can buy from you.

## How to program

⚠️**WARNING**⚠️ The VCC loop on the PCB is directly connected to the headphone battery. **Do not** connect an external supply to this hook while the battery is connected. It is only needed in order to program and test the board without a headset connected.

### Step 1: Bootloader
**This only needs to be done once per board**

When you have a fresh board with a factory-stock microcontroller, you'll have to start with the Arduino bootloader. An image is included in this repo, but you need a hardware AVR programmer, for example:

- AVRISPmk2 (tested, works)
- An Arduino ([Instructions](https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP/#how-to-wire-your-boards))
- A [Bus Pirate](http://www.dangerousprototypes.com/docs/Bus_Pirate_AVR_Programming)
- An [USBAsp](https://www.fischl.de/usbasp/)

...or anything else supported by avrdude or [platform.io](https://platformio.org/). Install [the platform.io tools](https://platformio.org/install/cli) and let's go!

1. Connect your programmer to MISO, MOSI, SCK, GND and RST.
2. Connect **either** the battery or the VCC terminal

Add the needed environment to `firmware/tobo/platformio.ini` to use your programmer.

**Warning** Ensure that your new environment extends `env:tobo`, so that the frequency and fuses are programmed properly. If you do not, you may need to temporarily connect an external crystal (see PCB markings) in order to recover the board.

```
cd firmware/tobo
pio run --environment avrispv2 --target bootloader
```

If there are no errors, congratulations! Your tobo board is an Arduino! You're ready for the next step.

### Step 2: Firmware
**If you've made changes to the code and want to update your board, this step is the only one you need to repeat**

If your board has the bootloader installed, you can put your ISP programmer away and use either the on-board USB port or your own serial adapter. This can be an FTDI cable, a different USB-to-serial adapter, or an arduino board with no microcontroller.

Hook up your serial cable to the tobo:

| tobo | serial adapter |
|------|----------------|
| RX | TX |
| TX | RX |
| GND | GND |
| RST | DTR |
| VCC  | VCC **Only if you don't have the battery plugged in**|


```
cd firmware/tobo
pio run --target upload
```

If all went well, you're ready to go!

## License
Touchlæss XM © 2025 by Albin Eldstål-Ahrens is licensed under Creative Commons BY-SA 4.0 

This means you are free to use, modify, distribute, remix, redesign the project however you wish as long as you
1. Credit the original work where relevant
2. Release your own modified work under a similar CC license

If you want to make and sell kits of this, feel free! If you make money from my work, please consider making a charitable donation or something as a thank you!