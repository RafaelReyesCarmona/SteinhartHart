Steinhart-Thermistor v2
=======================

4 coefficients Steinhart version of Thermistor library.

1/T = A + B\*log(R/Rt) + C\*log(R/Rt)^2 + D\*log(R/Rt)^3

In the standard Steinhart-Hart equation the C parameter is set to zero.
However, some manufacturers use all 4 coefficients.

## Typical usage

Connect a Thermistor to an Analog pin and use the library to get the temperature.

```
#include "Steinhart-Thermistor.h"

Thermistor Thermistor(A0);

void setup() {
	Serial.begin(9600);
}

void loop() {
	//Always call calcResistance() first.
	//It's the only function that read the ADC value.
	//Otherwise you could get a different value for each temperature unit.
	//You can specify a number of samples. Default = 1.
	Thermistor.calcResistance();
	Serial.print("Thermistor resistance: ");
	Serial.println(Thermistor.getResistance());
	Serial.print("Volts: ");
	Serial.println(Thermistor.getVolts());
	Serial.print("Analog value at pin: ");
	Serial.println(Thermistor.getAval());	
	Serial.print("Kelvin: ");
	Serial.println(Thermistor.getTempK());
	Serial.print("Celsius: ");
	Serial.println(Thermistor.getTempC());
	Serial.print("Fahrenheit: ");
	Serial.println(Thermistor.getTempF());
	delay(1000);
}
```

## Reference

### `Thermistor`

```
int pin = A0;
int resistor = 47500;
double a1 = 5.36924e-4;
double b1 = 1.91396e-4;
double c1 = 0;
double d1 = 6.60399e-8;
float vref = 3.32;

Thermistor Thermistor(pin, resistor, a1, b1, c1, d1, vref);
```

Creates an object to interact with the thermistor.

pin is the analog pin number your thermistor is connected to.
resistor is the fixed resistor value, for better precision used a multimeter/ohmmeter to mesure the value of the fixed resistor.
a1 is the coefficient A (K^0), from the thermistor datasheet.
b1 is the coefficient B (K^1), from the thermistor datasheet.
c1 is the coefficient C (K^2), usually 0 from the thermistor datasheet.
d1 is the coefficient D (K^3), from the thermistor datasheet.
vref is the voltage reference, for better precision used a multimeter/voltmeter to mesure voltage pin 3V3 for a Core/Photon/Electron, pin AREF for a Arduino.

### `calcResistance`

`Thermistor.calcResistance();`

Always call calcResistance() first. 
It's the only function that read the ADC value.
Otherwise you would get a different value for each temperature unit.
You can specify a number of samples. Default = 3.

### `getAval`

`Thermistor.getAval();`

Return the calculated average Analog value of ADC pin.

### `getResistance`

`Thermistor.getResistance();`

Return the calculated average resistance of the thermistor.

### `getTempF`

`Thermistor.getTempF();`

Return the calculated temperature in Fahrenheit.

### `getTempC`

`Thermistor.getTempC();`

Return the calculated temperature in Celcius.

### `getTempK`

`Thermistor.getTempK();`

Return the calculated temperature in Kelvin.

### `getVolts`

`Thermistor.getVolts();`

Return the average calculated volts value of ADC pin.

## Resource Utilization

Analog pin of your choice.

## License

GPL
