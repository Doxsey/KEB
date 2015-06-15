//%box%[@
#include <math.h>

int resistorCase;
int var;

double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
//         =log(10000.0/(1024.0/RawADC-1)) // for pull-up configuration
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;            // Convert Kelvin to Celcius
 //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
 return Temp;
}

int resitorPin = 6;
int topFan = 5;


void setup() {
 Serial.begin(115200);
 pinMode(6, OUTPUT);
 resistorCase = 0;
}

void loop() {
Serial.print((char)27); // ESC
Serial.print("[2J"); // clear screen
Serial.print((char)27); // ESC
Serial.print("[H"); // cursor to home
Serial.println(int(Thermistor(analogRead(0))));  // display Fahrenheit
Serial.println(analogRead(0));

 
 
  if (int(Thermistor(analogRead(0))) > 45)
    {
      resistorCase = 1; //Hotter than 45 degrees
    }
 
  else if (int(Thermistor(analogRead(0))) == 45)
    {
      resistorCase = 2; //Temp is 45
    }
  else if (int(Thermistor(analogRead(0))) < 43)
    {
      resistorCase = 3; //Temp less than 43
    }
 
  else
    {
      resistorCase = 4;
    }
    
Serial.print("Case: "); 
Serial.println(resistorCase);
  
  
  switch (resistorCase) {
    case 1:
      digitalWrite(resitorPin, LOW); 
      digitalWrite(topFan, HIGH);
      break;
    case 2:
      digitalWrite(resitorPin, LOW); 
      digitalWrite(topFan, LOW);
      break;
    case 3:
      digitalWrite(resitorPin, HIGH); 
      digitalWrite(topFan, LOW);
      break;
    case 4:
      digitalWrite(resitorPin, LOW); 
      digitalWrite(topFan, LOW);
      break;
      
  }
  
  
delay(1000);
}
