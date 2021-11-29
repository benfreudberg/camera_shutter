# General instructions
<img src="./imgs/IMG_E0556.jpg" alt="programmer1" width="1000"/>

## Taking a picture
Pushing the shutter button will cause the servo to move through its full range of motion and then back. Pushing the button on the remote will do the same thing after a `3 second` delay. The green `General Status LED` will flash 3 times during the 3 second countdown. It will turn off while the servo is being moved.

## IR Sensor Sensitivity
The sensor will have the best range if it is shielded from direct sunlight. In direct sunlight, it will only have a range of a few feet. Outside on a bright day where the sensor is not in direct sunlight, the range is about 20 feet. Indoors, the range is very far.

## Battery and Charging
The system will be powered any time the USB port is connected to a power source. If the power switch is also in the `On` position, then the battery will charge from the USB power source.

If the battery is low and the USB is not plugged in, the red `Battery Status LED` will turn on. Plugging in the USB may cause the LED to blink or it may turn off. `Blinking` is supposed to indicate `charging` while `off` is supposed to indicate `full`, however, due to how things are measured, the led will likely turn off long before the battery is actually full. You can check the battery voltage with a multimeter when the USB is not plugged in in order to get an estimate of the battery's state of charge.
