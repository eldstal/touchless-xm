# Touchless Board (tobo) firmware

## First time installation (bootloader)
Connect an ISP programmer (e.g. an AVRISPmk2 or an arduino wired up to MOSI/MISO/SCK/RST) and run

```
pio run --env avrispv2 --target bootloader --upload-port=/dev/ttyUSB0
```


## Update firmware
Connect to the RX/TX/RST hooks (or via the on-board USB connector) and run
```
pio run --target upload --upload-port=/dev/ttyUSB0
```


