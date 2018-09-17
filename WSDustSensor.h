#ifndef WSDustSensor_H
#define WSDustSensor_H
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#define        COV_RATIO                       0.2            //ug/mmm / mv
#define        NO_DUST_VOLTAGE                 400            //mv
#define        SYS_VOLTAGE                     5000           

class WSDustSensor {
 private:
    uint8_t _analogOutputPin;
    uint8_t _ledInputPin;
    float _density;
    float _voltage;
    int _adcvalue;
    int _filter(int m);

  public:
    WSDustSensor(uint8_t analogOutputPin, uint8_t ledInputPin);
    void begin();
    float readDustLevel();
};
#endif
