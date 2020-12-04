
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

# Master Fader

# Diagnostics

# Programmable Memory - Lighting Sequences

# Altium PCB Design

# References
1. [Texas Instruments LP55231 - Datasheet](https://www.ti.com/lit/ds/symlink/lp55231.pdf?ts=1607053477451&ref_url=https%253A%252F%252Fwww.google.com%252F)

[1]: https://www.ti.com/lit/ds/symlink/lp55231.pdf?ts=1607053477451&ref_url=https%253A%252F%252Fwww.google.com%252F "Texas Instruments LP55231 - Datasheet."
