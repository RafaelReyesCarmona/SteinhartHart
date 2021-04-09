<img src="img/celsius.png" width=48 height=48 align=right>

# SteinhartHart library #

[![Arduino ©: SteinhartHart](https://img.shields.io/badge/Arduino©-SteinhartHart-red?style=for-the-badge&logo=arduino)](README.md)

This is a fork of SteinhartHart work by [Andreas Tacke](https://github.com/fiendie/). If you want to know more about this work, visit the [Github page](https://github.com/fiendie/SteinhartHart).

I have introduce so much changes in the code, so this work keep on [ThermistorNTC library](https://github.com/RafaelReyesCarmona/ThermistorNTC).

Library to used to derive a precise temperature of a thermistor, fastest Calc. (14~29% faster than others)

## Information ##

All the work have been moved to [ThermistorNTC library](https://github.com/RafaelReyesCarmona/ThermistorNTC).

## How to use Thermistor as temperature sensor ##

Thermistor values denote their resistance at 25°C. A popular type would
be an NTC 10K which would give roughly 10 kOhms at that temperature point.

Although there are ways to calculate the coefficients yourself experimentally
it might be cheaper and easier to just buy a thermistor with known specs. This page
can help to calculate thats coefficients. [Thermistor Calculator V1.1](https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html).

To get readings from a thermistor into your Arduino you will have to use
a conventional voltage divider circuit. It can used two forms of configurations.

*Connecting NTC thermistor to VCC:*

	              ____         ____
	VCC +5 o-----|____|---+---|____|---o GND
	            NTC 10K   |     10K
	                      |
	PIN A0 o--------------+

*Or connecting NTC thermistor to GND:*

	              ____         ____
	VCC +5 o-----|____|---+---|____|---o GND
	              10K     |   NTC 10K
	                      |
	PIN A0 o--------------+


## Installation ##

For a tutorial on how to install new libraries for use with the Arduino
development environment please refer to the following website:
http://www.arduino.cc/en/Reference/Libraries

## How to use the library ##
The library implement the type:
```c++
enum Thermistor_connection {
  VCC,
  GND
  };
```
Usage:
```c++
// VCC or GND where thermistor configuration.
//   If no value, use VCC as default.
//
double sensor0 = thermistor0.getTempCelsius(VCC);
//double sensor0 = thermistor0.getTempCelsius(GND);
//double sensor0 = thermistor0.getTempCelsius();  /* VCC as default. */
```
### Constructors ###
```c++
// Constructor for thermistor 4 coefficients Steinhart-Hart equation.
Thermistor::Thermistor(int PIN,
                       long RESISTOR,
                       long NTC_25C,
                       double A,
                       double B,
                       double C,
                       double D,
                       float VREF)

// Constructor for thermistor 3 coefficients Steinhart-Hart equation.
//   Some manufacturers use C coefficient equal to 0 for simplicity.
Thermistor::Thermistor(int PIN,
                       long RESISTOR,
                       long NTC_25C,
                       double A,
                       double B,
                       double D,
                       float VREF)

// Constructor for thermistor beta equation.
Thermistor::Thermistor(int PIN,
                       long RESISTOR,
                       long NTC_25C,
                       float BETA,
                       float VREF){
```
Where:
* **PIN** - Analog port for get ADC (analogRead() function)
* **RESISTOR** - Value in ohms of resistor in voltage divisor.
* **NTC_25C** - Resistence value of NTC thermistor at 298.15ºK (25ºC)
* **A**, **B**, **C**, **D** - NTC Thermistor coefficients
* **BETA** - Beta coefficient of NTC thermistor.
* **VREF** - Voltage aplied to voltage divisor (usually VCC.)

### Functions implamented ###

```c++
void setADC(int);
void setEMA(float);

double getTempKelvin(Thermistor_connection ConType);
double getTempCelsius(Thermistor_connection ConType);
double getTempFahrenheit(Thermistor_connection ConType);

double fastTempKelvin(Thermistor_connection ConType);
double fastTempCelsius(Thermistor_connection ConType);
double fastTempFahrenheit(Thermistor_connection ConType);
```

### Simple Example ###

```c++
#include <SteinhartHart.h>

Thermistor thermistor0(/* PIN */       A0,
                      /* RESISTOR */  21900L,
                      /* NTC 25ºC */  9950L,
                      /* A */         3354016e-9,
                      /* B */         2569850e-10,
                      /* C */         2620131e-12,
                      /* D */         6383091e-14,
                      /* Vref */      5.03);

Thermistor thermistor1(/* PIN */       A1,
                      /* RESISTOR */  21900L,
                      /* NTC 25ºC */  9950L,
                      /* BETA */      4190.0,
                      /* Vref */      5.03);

void setup(void)
{
  Serial.begin(57600);
}


void loop(void)
{
  double sensor0 = thermistor0.getTempCelsius(VCC);
  Serial.print("Sensor0 - Temp(ºC): ");
  Serial.println(sensor0);

  double sensor1 = thermistor1.getTempCelsius();
  Serial.print("Sensor1 - Temp(ºC): ");
  Serial.println(sensor1);

  double sensor1_fast = thermistor1.fastTempCelsius();
  Serial.print("Sensor1 fast calc - Temp(ºC): ");
  Serial.println(sensor1_fast);

  delay(1000);
}
```

## License ##

This file is part of SteinhartHart Library.

SteinhartHart Library is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

SteinhartHart lLibrary is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with SteinhartHart Library.  If not, see <https://www.gnu.org/licenses/>.

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE)

## Authors ##

Copyright © 2021 Francisco Rafael Reyes Carmona.
Contact me: rafael.reyes.carmona@gmail.com

This is a fork of SteinhartHart work by [Andreas Tacke](https://github.com/fiendie/). If you want to know more about this work, visit the [Github page](https://github.com/fiendie/SteinhartHart).

## Credits ##

Celsius icon at the beginning is from [Flaticon.es](https://www.flaticon.es) designed by [Those Icons](https://www.flaticon.es/autores/those-icons)
and licensed by [free license](img/licencia-37862535.pdf).
