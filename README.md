## I2C-datalogger
Use CW01 to log data to SD card using CS11 as a slave device. This guide helps you how to do it easily.

### What you need
* CW01
* CS11
* IP01
* microSD card

### How to do
* Download latest release from this page. The release contains two file **UPDATE.bin** and **RESTART.UF2**. Copy and paste UPDATE.bin file to your microSD card, and put it into CS11 slot.
* From examples, flash **DATA_LOGGER-RandomNumber.ino** code to your CW01
* Now connect CW01, CS11 and IP01, and power the xchips with your laptop/Power Bank
* If successfully done, CW01 will shine Green LED, and CS11 will shine RED LED. That means data is being logged
* Your data files will be stored in DATA folder

### Troubleshooting
* Blue LED on CS11 fading in and out —> CS11 is in boot mode

  Click on reset button on CS11 once, red LED should shine then.

* RED LED on CS11 is not showing up —> UPDATE.bin might not have flashed from SD card

  Check if UPDATE.bin is still inside SD card. If its still there, UPDATE.bin has not flashed properly. Flash RESTART.UF2 to CS11 in boot mode by double clicking reset button to restart CS11 flash memory.

* Sky Blue LED is showing up on CS11 —> microSD card not inserted properly into CS11 slot

  Insert microSD card into CS11 slot.
  
* RED LED is showing up on CW01 —> CS11 is not connected properly.

  Check CS11 connection.
  




