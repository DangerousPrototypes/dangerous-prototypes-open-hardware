echo Note: To make the Flash Destroyer act as a USB device in order to update firmware, you must hold the button down, apply power, THEN hook up the USB cable. Otherwise, it'll not work.
pause
fw_update -e -w -v -m flash -vid 0x04D8 -pid 0xFBEB -ix FD-firmware-v1.1.hex
pause