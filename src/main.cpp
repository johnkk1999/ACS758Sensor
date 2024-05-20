#include <Arduino.h>
#include "bandpassFilter.h"

#define zeroCurrent 1.66200 // vcc/2
#define sensitivity 12e-3 //10mV/A
#define sampTime 541e-6
bandPassFilter bpFilter;

float getCurrentRms();

void setup() {
 Serial.begin(9600);
 analogReadResolution(16);
 bpFilter.RcFilterInit(sampTime,40.0, 60.0);

}

void loop() {
  // float voltage1 = 3.3 * analogRead(A0) / 65536.0;
  // Serial.print(">unFiltered:");
  // Serial.println(voltage1);
  // Serial.print(">Filtered:");
  // Serial.println(bpFilter.RcFilterUpdate(voltage1) * 6.075);
  // float voltage2 = 3.3 * analogRead(A1) / 65536.0;
  // float current = (voltage1 - zeroCurrent)/sensitivity;
  // Serial.println(current,7);
  Serial.println(getCurrentRms());
  
  
}
float getCurrentRms()

{
  float current = 0;
  int samples = 0;
  float last = millis();
  
  while(millis()-last < 200)
  {
     float voltage1 = 3.3 * analogRead(A0) / 65536.0;
     voltage1 = bpFilter.RcFilterUpdate(voltage1);
     float currentTemp = (voltage1);
     current = current + sq(currentTemp);
     
     samples++;
  }
  
  current = sqrt(current/(float)samples)/ sensitivity;
  return current;
}