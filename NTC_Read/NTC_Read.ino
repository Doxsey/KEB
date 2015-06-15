//%box%[@
#include <math.h>



double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
//         =log(10000.0/(1024.0/RawADC-1)) // for pull-up configuration
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;            // Convert Kelvin to Celcius
 //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
 return Temp;
}

void setup() {
 Serial.begin(115200);
 pinMode(6, OUTPUT);
}

void loop() {
  Serial.print((char)27); // ESC
Serial.print("[2J"); // clear screen
Serial.print((char)27); // ESC
Serial.print("[H"); // cursor to home
 Serial.println(int(Thermistor(analogRead(0))));  // display Fahrenheit
 Serial.println(analogRead(0));
 digitalWrite(6, !digitalRead(6));
 Serial.println(digitalRead(6));
 delay(100);
 
}
