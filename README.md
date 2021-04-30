
![Banner](https://github.com/jonathanrjpereira/LP55231-Programmable-9-LED-Driver/blob/main/img/Banner-01.svg)

 - Three Independent Program Execution Engines with instructions stored in the Internal Program Memory.
 - 9 Programmable Outputs With 25.5-mA Full-Scale Current, 8-Bit Current Setting Resolution and 12-Bit PWM Control Resolution.
 - Simultaneous control of groups of LEDs with Master Faders.
 - Built-in LED Test, Temperature and Voltage measurement capability.

# Chip Configuration
- The LP55231 I2C pins are connected to `PB7(SDA1)` and `PB6(SCL1)` of the STM32L4 and runs on 3V.
- After Power-On Reset, the chip enters the standby mode. In this mode values can be written to the registers but all LED functions are disabled. Once the chip is enabled, LED functions can execute depending upon the register configuration.
- To enable the chip, the `EN` pin of the LP55231 must be set and the `CHIP_EN` bit must also be set. GPIO `PA3` is used to set the `EN` pin. After a startup sequence delay of 500us, the chip enters Normal mode.
- In normal mode, the clock source and charge pump gain must be selected. The charge pump is used to boost the battery supply voltage to suitable levels for the LEDs.
- The `CLK_DET_EN` and `INT_CLK_EN` bits of the `MISC` register are set such that the chip is clocked by its internal clock.
- The `CP_MODE` bits of the `MISC` register are configured such that the charge pump operation mode is set to 1.5x.


# Direct PWM Control
- Each LED channel can be controlled independently by writing a 8-bit value to the channels respective PWM control register via I2C. 
- The output current for each channel is configured by writing an 8-bit value to the `Dx_CURRENT_CONTROL` register which defaults to 17.5mA.
- LED dimming mode is controlled according to the logarithmic or linear scale. The `LOG_EN` bit in the `Dx_CONTROL` register can be configured to set the dimming control mode. i.e `0: Linear`, `1: Log`. According to the datasheet, by using the logarithmic ramp setting the visual effect appears like a linear ramp, because the human eye behaves in a logarithmic way.

# Master Fader
- The LP55231 has 3 master faders. Channels can be grouped together by mapping them to a particular master fader. Once the initial brightness is set for a channel, the master fader is used to fade multiple LEDs within the same group simultaneously using a single I2C command.
- The LED channel is assigned to a particular Master Fader by configuring the `MAPPING` bits within the `Dx_CONTROL` register.
- An 8-bit value is written to the `MASTER_FADERx` register to control all the LEDs that are mapped to it.

# Diagnostics
The chip has a few internal sensors that can be used for diagnostic purposes to measure the chip’s internal temperature and various voltage levels.
## Internal Temperature Sensor
- To start the temperature measurement we need to set the `EN_TEMP_SENSOR` bit in the `TEMPERATURE_ADC_CONTROL` register.
- The measurement period varies depending on the temperature. Hence we monitor the `TEMP_MEAS_BUSY` bit to check if the temperature measurement is active or not.
- The temperature reading (two’s complement format) can be read `TEMPERATURE_READ` register.

## LED Driver Output
- To start the voltage measurement we set the `EN_LEDTEST_ADC` bit in the `LED_TEST_CONTROL` register. We then wait for 3ms to account for the measurement cycle that takes 2.7ms.
- The channel number is used to configure the `LED_TEST_CONTROL` bits.
- We can read the 8-bit value from the `LED_TEST_ADC` register. The voltage can be derived using the formula:
 `Voltage = (Result * 0.03) - 1.478 V`.
 
## Measure VDD 
- This is similar to the LED Driver Output measurement.
- To start the voltage measurement we set the `EN_LEDTEST_ADC` bit in the `LED_TEST_CONTROL` register. We then wait for 3ms to account for the measurement cycle that takes 2.7ms.
- Depending on the voltage source i.e `VDD`, `Vout` or `INT` that we wish to measure, we can configure the `LED_TEST_CONTROL` bits appropriately. To measure `VDD`, it is configured as `0x10`.
- We can read the 8-bit value from the `LED_TEST_ADC` register. The voltage can be derived using the formula: `Voltage = (Result * 0.03) - 1.478 V`.


# Test Plan and Results
## Power On Self Test (POST)
Once the chip is enabled and the `MISC` register is configured, a Power On Self Test (POST) is performed by periodically varying the brightness of each channel consecutively. The brightness control is set to the Linear scale.

## Lighting Sequence 
A multicolor LED follower sequence is performed to resemble the lighting effects seen on the Google Home Mini.

## Master Fader 
- The Master fader functionality is tested by grouping all 3-channels connected to LED1. The R, G and B channels of LED1 are set to their maximum values using the Direct PWM registers in order to display a white color. The channels are configured to the logarithmic scale. They are then grouped together such that they are mapped to Master Fader 1. The value of Master Fader 1 is periodically incremented such that the mapped channels vary in a ratiometric manner.
- When the brightness is reduced in a ratiometric manner using the master fader feature, it is observed that the color changes from white to yellow. This is probably caused by the blue LED having a lower wavelength than the red and green LEDs. Thus at lower intensities, it is easier to see red and green (yellow) rather than red, green and blue which produces white.

## Diagnostics
Configured channel 7’s brightness to maximum. Printed the diagnostic information such as LED forward voltage, VDD and internal temperature.

# References
1. [Texas Instruments LP55231 - Datasheet](https://www.ti.com/lit/ds/symlink/lp55231.pdf?ts=1607053477451&ref_url=https%253A%252F%252Fwww.google.com%252F)

[1]: https://www.ti.com/lit/ds/symlink/lp55231.pdf?ts=1607053477451&ref_url=https%253A%252F%252Fwww.google.com%252F "Texas Instruments LP55231 - Datasheet."
