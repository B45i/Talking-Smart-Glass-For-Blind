# Talking Smart Glass For Blind

![Person wearing smart glass](./images/IMG_20180605_092232.jpg)

There are multiple smart accessories such as smart glasses, smart watches etc available in the market. But all of them are built for us.
There is a significant lack of technology to aid the physically challenged. I wanted to build something that is useful for the visually challenged people. So i designed low cost smart glass that can be used to help the visually impaired.

This project uses few Ultrasonic distance sensors, an arduino pro mini, mp3 Player module and some vibration motors.

Circuit board used in this project is designed in the form of a spectacle, that can be worn by visually impaired person. Arduino mounted on the spectacle will detect the obstacle with the help of the sensors and notify the user through headphones and vibration motors.

![PCB Back ](./images/IMG_20180605_092439.jpg "PCB Back side")
![PCB Front](./images/IMG_20180605_092352.jpg "PCB Front side")

## Parts needed

* 1 * Arduino pro mini 5v 16Mhz (Any version of arduino like nano or uno cane be used, but pro mini is easier to mount on the spectacles).
* 3 * HC SR04 Ultrasonic distance sensor.
* 1 * DF Player mini.
* 3 * Vibration motors.
* 3.5mm audio jack.
* 2 * Slide switches.
* 1 * SD card

### Optional

* FTDI Breakout cable (only if you are using the pro mini)
* My custom PCB  from [jlcpcb.com](https://jlcpcb.com/quote/eda?eadLink=2&uuid=c2ed7d40916740bd957b6fa516fbd572) or [pcbway.com](https://www.pcbway.com/project/shareproject/Talking_Smart_Glass_For_Blind.html)
* 3W Speaker

## The Circuit Diagram

![Circuit Diagram](./images/circuit_diagram.png "Circuit Diagram")

## Flash the pro micro

* Connect arduino pro mini to the computer using FTDI cable.
* Select proper COM port.
* Select 'arduino pro or pro mini'.
* Click upload
> Make sure to flash arduino before soldering it to pcb. One all the components are soldered, it will be bit harder to connect the programming header.

## Assembling the PCB

* Solder the components like Arduino, DF Player, Audio jack, Slide Switches to the PCB first.

* We can't directly solder the HC-SR04 module available from market. some modification need to be done.

![Unmodified HC-SR04](./images/ultrasonic_1.jpg "Unmodified HC-SR04")

* Straighten the male header using a plier or de-solder the 90&deg; and solder normal headers.

![modified HC-SR04](./images/ultrasonic_2.jpg "modified HC-SR04")

* Add electrical tape to tha back of HC-SR04 to avoid short circuit.

* Insert HC-SR04 to designated solder pads.
 hold the left and right HC-SR04 at an angle and apply solder.

![solder HC-SR04](./images/ultrasonic_3.jpg "solder HC-SR04 at an angle")

* Solder rest of the components such as power supply cable, slide switches, vibration motors etc.

## Copying audio files to the SD card

Copy content of the [Audio files folder](https://github.com/B45i/Talking-Smart-Glass-For-Blind/tree/master/Audio%20files) to the root of the SD card.

> **Copy folders (01, 02, 03) itself, not its content.**

![Audio files in SD card](./images/audio_files.png "Audio files in SD card")
