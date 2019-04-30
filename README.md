# Light Detector
Arduino project to detect ambience light with a photo resistor, group the current brightness into three brackets (day, night or twilight) and lights a corresponding LED:

 * Red: Day
 * Green: Twilight
 * Blue: Night

Additional the current brightness level can be transmitted back to PC via a push button press. The button handling is debounced and the application periodically retransmits the ambience as well as the photo resistor values. 

## Circuit
Circuit image created with [Fritzing](http://fritzing.org/).

![1](/Circuit.png)

Part list:
 * 4 x 220Ω resistor
 * 1 x 10kΩ (pull-up / pull-down) resistor
 * 1 x green LED
 * 1 x blue LED
 * 1 x red LED
 * photo resistor
 * push button
 * wires

## Known Issues
None

## by [thex](https://github.com/thexmanxyz)
Copyright (c) 2019, free to use in personal and commercial software as per the [license](/LICENSE.md).
