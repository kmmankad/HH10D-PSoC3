Interfacing the HH10D Humidity Sensor with the PSoC 3
-----------------------------------------------------

This is some basic code to read out Relative Humidity values from the Humidity sensor HH10D.

It involves
-Reading Calibration Constants from the I2C EEPROM on the sensor.
(Sensitivity=395,and offset=7728 for my module)

-Reading Frequency output from the sensor.
-Display of the Relative Humidity value on a 16x2 LCD.

-kmmankad

http://kmmankad.blogspot.com

This work is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License.