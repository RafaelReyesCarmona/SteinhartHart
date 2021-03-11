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

#include "SteinhartHart.h"
#include <math.h>	

// Constructor para 4 parametros (A,B,C,D).	
Thermistor::Thermistor(int PIN, 
                       long RESISTOR, 
                       long NTC_25C,
                       double A, 
                       double B, 
                       double C, 
                       double D, 
                       float VREF){
  _PIN = PIN;
  _RESISTOR = RESISTOR;
  _NTC_25C = NTC_25C;
  _A = A;
  _B = B;
  _C = C;
  _D = D;
  _VREF = VREF;

  pinMode(_PIN, INPUT);
}

// Constructor para 3 parametros (A,B,D.. C = 0).
Thermistor::Thermistor(int PIN, 
                       long RESISTOR, 
                       long NTC_25C,
                       double A, 
                       double B, 
                       double D, 
                       float VREF){
  _PIN = PIN;
  _RESISTOR = RESISTOR;
  _NTC_25C = NTC_25C;
  _A = A;
  _B = B;
  _D = D;
  _VREF = VREF;

  pinMode(_PIN, INPUT);
}

// Constructor para parametro BETA del termistor.
Thermistor::Thermistor(int PIN, 
                       long RESISTOR, 
                       long NTC_25C,
                       double BETA,
                       float VREF){
  _PIN = PIN;
  _RESISTOR = RESISTOR;
  _NTC_25C = NTC_25C;
  _BETA = BETA;
  _VREF = VREF;

  pinMode(_PIN, INPUT);
}


void Thermistor::SteinhartHart(){
  float E = log(calcNTC()/(float)_NTC_25C);
  _temp_k = _A + (_B*E) + (_C*(E*E)) + (_D*(E*E*E));
  _temp_k = 1.0 / _temp_k;
  _temp_c = _temp_k - 273.15;
}


void Thermistor::SteinhartHart_beta(){
  _temp_k = log(calcNTC()/(float)_NTC_25C);
  _temp_k /= _BETA;
  _temp_k += 1.0 / 298.15;
  _temp_k = 1.0 / _temp_k;
  _temp_c = _temp_k - 273.15;
}


void Thermistor::SteinhartHart_fast(){
  _temp_k = log(calcNTC()/(float)_NTC_25C);
  _temp_k *= 298.15;
  _temp_k += _BETA;
  _temp_k = (_BETA * 298.15) / _temp_k;
  _temp_c = _temp_k - 273.15; 
}


double Thermistor::getTempKelvin() {
  _BETA > 0.0 ? SteinhartHart_beta() : SteinhartHart();
  return _temp_k;
}


double Thermistor::getTempCelsius() {
  _BETA > 0.0 ? SteinhartHart_beta() : SteinhartHart();
  return _temp_c;
}


double Thermistor::getTempFahrenheit(){
  return getTempCelsius() * 9/5 + 32;
}


double Thermistor::fastTempKelvin() {
  _BETA > 0.0 ? SteinhartHart_fast() : SteinhartHart();
  return _temp_k;
}


double Thermistor::fastTempCelsius() {
  _BETA > 0.0 ? SteinhartHart_fast() : SteinhartHart();
  return _temp_c;
}


double Thermistor::fastTempFahrenheit(){
  return fastTempCelsius() * 9/5 + 32;
}


float Thermistor::getADC(int numsamples = 15){
  float EMA_LOW;

  EMA_LOW = analogRead(_PIN);

  for (byte i = numsamples; i—; ){
    delayMicroseconds(120);
    EMA_LOW = (_alphaEMA_LOW * (float)analogRead(_PIN)) + (1.0 - _alphaEMA_LOW) * EMA_LOW);
  }

  return EMA_LOW;
}


double Thermistor::calcNTC(Thermistor_connection ConType){
  double NTC;
  float ADC = getADC();
  if (ConType == VCC){
    NTC = (float)_ADC_MAX * (float)_RESISTOR;
    NTC -= ADC * (float)_RESISTOR;
    NTC /= ADC;
    return NTC;
  }
    NTC = ADC * _VREF / (float)_ADC_MAX;
    NTC /= (_VREF - NTC);
    NTC *= (float)_RESISTOR;
    return NTC;
}


void Thermistor::calcBETA(float T1, long RT1, float T2, long RT2){
  _BETA = log(RT1/RT2);
  _BETA /= ((T2 - T1) / (T1 * T2)); // _BETA /= (1/T1) - (1/T2);
}