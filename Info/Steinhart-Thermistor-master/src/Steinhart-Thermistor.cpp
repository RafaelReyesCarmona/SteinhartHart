#include "Steinhart-Thermistor.h"
#include "math.h"

// TURN DEBUG ON?
#define MYDEBUG FALSE

int Thermistor::getAdc(int numsamples) {
    delay(10);
    // Initialise vars
    int total = 0;
    int temp = 0;

    // After looking at all kinds of fancy median libraries etc, a simple average on a small set (3) works well
    // The real secret is to get your probe returning sensible avals that don't vary much
    for(int i = 0; i < numsamples; i++) {
        // Read the pin
        temp = analogRead(_pin);
        // Show some debug output if really required
        if (MYDEBUG) {
            Serial.print("pin: ");
            Serial.print(_pin);
            Serial.print(" temp: ");
            Serial.println(temp);
        }
        // Add to total
        total += temp;
        // Wait a while
        delay(100);
    }
    // Calculate average
    _aval = (double) total / (double) numsamples;
    // Debug output
    if (MYDEBUG) {
        Serial.print("getADC: ");
        Serial.println(_aval, 4);
    }
    return _aval;
}

Thermistor::Thermistor(int _pin, int _RESISTOR, double _A1, double _B1, double _C1, double _D1, float _VREF) {
    this->_pin = _pin;
    this->_RESISTOR = _RESISTOR;
    this->_VREF = _VREF;
    this->_A1 = _A1;
    this->_B1 = _B1;
    this->_C1 = _C1;
    this->_D1 = _D1;
    pinMode(_pin, INPUT);
}

double Thermistor::calcResistance(int numsamples) {
    // From memory the -1 was part of the voltage dividor calc, not a mistake from the 4096 - 1 typical process
    // Also you divide if its pullup vs pulldown
    _resistance = _RESISTOR / ((float) _ADC / getAdc(numsamples) - 1.0f);

    // Get the current voltage, its nice to know
    calcVolts();

    return _resistance;
}

double Thermistor::getResistance() {
    return _resistance;
}

double Thermistor::calcVolts() {
    // Better to calculate observed volts from known relationship between aval, ADC and reference voltage rather than calculated resistance
    _volts = (_aval / (float) _ADC) * _VREF;
    return _volts;
}

double Thermistor::getVolts() {
    return _volts;
}
double Thermistor::getAval() {
    return _aval;
}

double Thermistor::getTempK() {
    // Nice to cache the log R value
    double R = log(_resistance);
    // Slightly optimised 4 part Steinhart Hart
    _temp_k = 1.0f / (_A1 + (_B1 + _C1 * R + _D1 * R * R) * R);
    return _temp_k;
}

double Thermistor::getTempC() {
    // Standard Kelvin calc
    _temp_c = getTempK() - 273.15f;
    // If the probe is not plugged in, it will return negative values
    if (_temp_c < 0){
        // Return 0
        _temp_c = 0;
    }
    return _temp_c;
}

double Thermistor::getTempF() {
    // Standard Fahrenheit calc, it inherits the 0 degrees celsius minimum, ie 32.
    _temp_f = getTempC() * 9 / 5.0 + 32;
    // Note, if the temp was 32 then its fair to assume it was a 'null' reading
    return _temp_f;
}
