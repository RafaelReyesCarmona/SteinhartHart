/*
SteinhartHart.cpp - Library to used to derive a precise temperature of a thermistor, 
fastest Calc (26~18% faster)
v0.1

Copyright © 2021 Francisco Rafael Reyes Carmona. 
All rights reserved. 

rafael.reyes.carmona@gmail.com 


  This file is part of SteinhartHart. 

  SteinhartHart is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  SteinhartHart is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with SteinhartHart.  If not, see <https://www.gnu.org/licenses/>.

*/

/**
 * Example sketch for the SteinhartHart library.
 */

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
unsigned long time0;
unsigned long time1;
unsigned long curtime;

void setup(void)
{
	Serial.begin(9600);
}


void loop(void) 
{
  time0 = micros();
  double sensor0 = thermistor0.getTempCelsius();
  time1 = micros();
  double sensor1 = thermistor1.fastTempCelsius();
  curtime = micros();
	
  Serial.print("Sensor0(°C): ");
  Serial.print(sensor0);
  Serial.print(" calculated in (microsecs): ");
  Serial.println(time1-time0);
	
  Serial.print("Sensor1(°C): ");
  Serial.print(sensor1);
  Serial.print(" calculated in (microsecs): ");
  Serial.println(curtime-time1);
  
	delay(1000);
}
