/*
SteinhartHart.h - Library to used to derive a precise temperature of a thermistor, fastest Calc (26~18% faster)
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

#if ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


#ifndef SteinhartHart_h
#define SteinhartHart_h

#include <inttypes.h>

#define V_IN 5.0	// Input voltage
#define K 9.5		// Dissipation factor (mW/°C)


class SteinhartHart {
	public:	
		/**
		 * The reading pin has to be specified.
		 * If no other parameters are given default values will be used.
		 * These values are for a NTC 10k thermistor with a 10k resistor
		 * put in parallel.
		 */
		SteinhartHart(
			uint8_t reading_pin, 
			double resistance = 10000.0, 
			double a = 1.129148e-3, 
			double b = 2.34125e-4, 
			double c = 8.76741e-8) : 
			_reading_pin(reading_pin), 
			_resistance(resistance), 
			_a(a), _b(b), _c(c) {};

		double getTempKelvin();
		double getTempCelsius();
		double getTempFahrenheit();
		
	private:
		double steinhartHart(double);
		
		// Value of the resistor put in parallel
		double _resistance;	

		uint8_t _reading_pin;

		// Manufacturing constants
		double _a;
		double _b;
		double _c;
};

class Thermistor {
    private:
        int _ADC = 1023;
        int _pin;
        unsigned int _RESISTOR = 10000;
        double _aval;
        double _A1;
        double _B1;
        double _C1;
        double _D1;
        double _BETA;
        double _resistance;
        double _volts;
        double calcVolts();
        float _VREF;
        double calcResistance(int numsamples = 15);
        double getAval();
        double getResistance();
        int getAdc(int numsamples = 15);
    public:
        double _temp_k;
        double _temp_c;
        double _temp_f;

        Thermistor() = delete;
        Thermistor(int, unsigned int, double, double, double, double, float); // Constructor para 4 parametros (A,B,C,D).
//Thermistor(int pin, unsigned int RESISTOR, double A1, double B1, double C1, double D1, float VREF):_pin(pin), _RESISTOR(RESISTOR), _A1(A1), _B1(B1), _C1(C1), _D1(D1), _VREF(VREF){};
        Thermistor(int, unsigned int, double, double, double, float); // Constructor para 3 parametros (A,B,D.. C = 0).
        Thermistor(int, unsigned int, double, float); // Constructor para parametro BETA del termistor.
        Thermistor(const Thermistor&); // Constructor de copia.
        
        void setADC(int ADC):ADC(_ADC){};
        double getTempF();
        double getTempC();
        double getTempK();
        double getVolts();
};

#endif