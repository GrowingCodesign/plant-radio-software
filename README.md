# plant-radio-software
A collection of all the software elements for the plant radio.

**It is important to keep the following naming convention so the plant radios are able to execute the software properly. Furthermore, the sketches should be in their respective folder, or else the plant radio won't be able to locate them when booting.**

### Arduino sketch name:
*gc_arduino.ino*

### Processing sketch name:
*gc_processing.pde*

### PureData sketch name:
*gc_puredata.pd*


# Guide for setting up Raspberry Pi
Insert Micro SD card with Raspberry Pi OS into the Raspberry Pi.

Boot up the Pi, connect it to your WiFi, and use the terminal window to install the following software:

### Install Processing:
``` curl https://processing.org/download/install-arm.sh | sudo sh ```

Download the processing sketch from github:
``` git clone https://github.com/duendue/growing-codesign.git ```

### Install Arduino:
`sudo apt install Arduino`

`cd Downloads `

`ls` (Note the version name of your installation version) 

`tar -xf arduino-####-linuxarm.tar.xz` (Add the listed version) 

`sudo mv ardunio-#### /opt sudo /opt/arduino-####/install.sh`

### Install PureData:
`sudo apt-get install puredata`
