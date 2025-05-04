The hex file here is a bog-standard [Optiboot](https://github.com/Optiboot/optiboot) rebuilt for 8MHz system clock and a reduced 38400 baud serial rate.

```
export BOOTLOADER_DIR=${PWD}
git clone 
cd optiboot/optiboot/bootloaders/optiboot
make AVR_FREQ=8000000 BAUD_RATE=38400 atmega328
mv optiboot_atmega328.hex ${BOOTLOADER_DIR}/optiboot_atmega328_8mhz_38400.hex
```
