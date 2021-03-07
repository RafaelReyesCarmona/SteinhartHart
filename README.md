# SteinhartHart library #

Library to used to derive a precise temperature of a thermistor, fastest Calc. 

## Introduction ##

The Steinhart-Hart equation is the most widely used tool to interpolate 
the NTC thermistor resistance/temperature curve. It is a third order
polynomial ecuation which provides very good curve fitting.

	1                              2                3
	- = A + B * ln (R/NTC) + C * ln (R/NTC) + D * ln (R/NTC)
	T

In the standard Steinhart-Hart equation the C parameter is set to zero.
However, some manufacturers use all 4 coefficients. So we can use standard Steinhart-Hart
ecuation with 3 coefficients. 
 
	1                          3
	- = A + B * ln (R) + C * ln (R)
	T
 
where:
* **T** is the temperature (in kelvins),
* **R** is the resistance at T (in ohms),
* **A**, **B**, and **C** are the Steinhart–Hart coefficients, which vary depending on the type and model of thermistor and the temperature range of interest. 
These can usually be found in the data sheet.

## Other expressions ##

Other form of the equation is the use of B (beta) parameter 

	           (beta *(1/T - 1/298.15))
	R = NTC * e

where:
* **T** is the temperature (in kelvins),
* **R** is the resistance at T (in ohms),
* **NTC** is the resistence of thermistor at 298'15 ºK (25 ºC) 
* **beta** are the Steinhart-Hart beta coefficient that vary depending on the type and model of Thermistor. 
These can usually be found in the data sheet.

## More Information ##

[Thermistor](https://en.wikipedia.org/wiki/Thermistor?wprov=sfla1) is the principal element of temperature sensor.

[Look here](https://en.wikipedia.org/wiki/Steinhart–Hart_equation?wprov=sfla1) for more information about Steinhart-Hart ecuations. 

You can learn more about [temperature coefficient here](https://en.wikipedia.org/wiki/Temperature_coefficient?wprov=sfla1). 

More information:
* [Arrhenius equation](https://en.wikipedia.org/wiki/Arrhenius_equation?wprov=sfla1). 
* [Q10 temperature coefficient](https://en.wikipedia.org/wiki/Q10_%28temperature_coefficient%29). 

## Fast Calc ##

In this library, it is take the beta ecuation and calculate temperature of the thermistor from it. 

	 R     (beta/T - beta/298,15)                  beta   beta        ln(R/NTC)   1     1
	--- = e                         ,, ln(R/NTC) = ---- - ------  ,,  --------- = - - ------- ,,
	NTC                                             T     298,15        beta      T   298,15
 
	1      1     ln(R) - ln(NTC)        1     ln(R/NTC)     beta + 298,15 * ln(R/NTC)
	- = ------ + ---------------  =  ------ + ---------  =  -------------------------
	T   298,15        beta           298,15     beta             beta * 298,15

So we can solve using this formula:

	          beta * T0
	T = ----------------------
	     beta + T0 * ln(R/NTC)
	
	(T0 = 298,15)

The library is 26~18% faster than others libraries to
get temperature from Thermistor. Use example for test. 

Using the [Thermistor Calculator V1.1](https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html) 
you can de termine the unknowns parameters of a thermistor. 

## How to use Thermistor as temperature sensor ##

Thermistor values denote their resistance at 25°C. A popular type would
be an NTC 10K which would give roughly 10 kOhms at that temperature point.

Although there are ways to calculate the coefficients yourself experimentally
it might be cheaper and easier to just buy a thermistor with known specs. This page 
can help to calculate thats coefficients. 

To get readings from a thermistor into your Arduino you will have to use
a conventional voltage divider circuit.

	              ____         ____
	VCC +5 o-----|____|---+---|____|---o GND
	            NTC 10K   |     10K
	                      | 
	PIN A0 o--------------+


## INSTALLATION ##

For a tutorial on how to install new libraries for use with the Arduino
development environment please refer to the following website:
http://www.arduino.cc/en/Reference/Libraries


