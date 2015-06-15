//%box%[@
#include <math.h>

int resistorCase;
int var;
float avgTemp;

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

avgTemp = 0;

var = 0;
while(var < 20)  
  {
   avgTemp = avgTemp + float(Thermistor(analogRead(0)));

    var++;
    delay(5);
  }

avgTemp = avgTemp / 20;

Serial.print((char)27); // ESC
Serial.print("[2J"); // clear screen
Serial.print((char)27); // ESC
Serial.print("[H"); // cursor to home

Serial.println(avgTemp);  // display Fahrenheit
Serial.println(analogRead(0));

 
 
  if (avgTemp > 45.2)
    {
      resistorCase = 1; //Hotter than 45 degrees
    }
 
  else if (avgTemp == 45)
    {
      resistorCase = 2; //Temp is 45
    }
  else if (avgTemp < 44.4)
    {
      resistorCase = 3; //Temp less than 44.4
    }
 
  //else
    //{
      //resistorCase = 4;
    //}
    
Serial.print("Case: "); 
Serial.println(resistorCase);
  
  
  switch (resistorCase) {
    case 1:
      digitalWrite(resitorPin, LOW); 
      digitalWrite(topFan, HIGH);
      Serial.println("Fan On, Resistor Off"); 
      break;
    case 2:
      digitalWrite(resitorPin, LOW); 
      digitalWrite(topFan, LOW);
      Serial.println("Fan Off, Resistor Off");
      break;
    case 3:
      digitalWrite(resitorPin, HIGH); 
      digitalWrite(topFan, LOW);
      Serial.println("Fan Off, Resistor On");
      break;
    case 4:
      digitalWrite(resitorPin, LOW); 
      digitalWrite(topFan, LOW);
      break;
      
  }
  
  
delay(1000);
}
