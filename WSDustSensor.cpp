#include "WSDustSensor.h"

WSDustSensor::WSDustSensor(uint8_t analogOutputPin, uint8_t ledInputPin){
  _analogOutputPin = analogOutputPin;
  _ledInputPin = ledInputPin;
}

void WSDustSensor::begin(){
  pinMode(_ledInputPin, OUTPUT);
  digitalWrite(_ledInputPin, LOW);
}

float WSDustSensor::readDustLevel(){
  /*
  get _adcvalue
  */
  digitalWrite(_ledInputPin, HIGH);
  delayMicroseconds(280);
  _adcvalue = analogRead(_analogOutputPin);
  digitalWrite(_ledInputPin, LOW);
  
  _adcvalue = _filter(_adcvalue);
  
  /*
  covert voltage (mv)
  */
  _voltage = (SYS_VOLTAGE / 1024.0) * _adcvalue * 11;
  
  /*
  voltage to density
  */
  if(_voltage >= NO_DUST_VOLTAGE)
  {
    _voltage -= NO_DUST_VOLTAGE;
    _density = _voltage * COV_RATIO;
  }
  else
    _density = 0;
  return _density;
}

/*
private function
*/
int WSDustSensor::_filter(int m)
{
  static int flag_first = 0, _buff[10], sum;
  const int _buff_max = 10;
  int i;
  
  if(flag_first == 0)
  {
    flag_first = 1;

    for(i = 0, sum = 0; i < _buff_max; i++)
    {
      _buff[i] = m;
      sum += _buff[i];
    }
    return m;
  }
  else
  {
    sum -= _buff[0];
    for(i = 0; i < (_buff_max - 1); i++)
    {
      _buff[i] = _buff[i + 1];
    }
    _buff[9] = m;
    sum += _buff[9];
    
    i = sum / 10.0;
    return i;
  }
}

















