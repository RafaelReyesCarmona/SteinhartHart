#include "application.h"

class Thermistor {
    private:
        int _ADC = 4095;
        int _pin;
        int _RESISTOR;
        int getAdc(int numsamples);
        double _aval;
        double _A1;
        double _B1;
        double _C1;
        double _D1;
        double _resistance;
        double _volts;
        double calcVolts();
        float _VREF;
    public:
        double _temp_k;
        double _temp_c;
        double _temp_f;
        //Maverick ET-72: Thermistor(int _pin, int _RESISTOR = 19870, float _VREF = 3.3200, double _A1 = 2.4723753e-4, double _B1 = 2.3402251e-4, double _C1 = 0, double _D1 = 1.3879768e-7);
        Thermistor(int _pin, int _RESISTOR = 47500, double _A1 = 5.36924e-4, double _B1 = 1.91396e-4, double _C1 = 0, double _D1 = 6.60399e-8, float _VREF = 3.3200);
        double calcResistance(int numsamples = 3);
        double getAval();
        double getResistance();
        double getTempF();
        double getTempC();
        double getTempK();
        double getVolts();
};
