//%box%[@
#include <math.h>

int resistorCase;
int var;
int variableDelay;
float avgTemp;
boolean toggle1 = 0;
int sampleCount;
float storeAvg;
unsigned int constantCount;
float constantSum;
float movingAvg;
float movingSum;


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
  cli();//stop interrupts
 Serial.begin(115200);
 pinMode(6, OUTPUT);
 resistorCase = 0;
 variableDelay = 1000;
 sampleCount=0;
 movingAvg = 0;
 movingSum = 1;
 //constantAvg = 0;
constantCount = 0;
constantSum = 0;
 avgTemp = 0;
resistorCase = 4;
//var = 0;
//while(var < 40)  
//  {
//   avgTemp = avgTemp + float(Thermistor(analogRead(0)));
//
//    var++;
//    delay(5);
//  }
//
//avgTemp = avgTemp / 40;
// 
 //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
 sei();//allow interrupts
}

void loop() {

Display_Data();
Choose_Case();
caseStatements();  


delay(1000);
}

void Display_Data()
  {
    Serial.print((char)27); // ESC
    Serial.print("[2J"); // clear screen
    Serial.print((char)27); // ESC
    Serial.print("[H"); // cursor to home
    Serial.print("Current Temp: ");
    Serial.println(movingAvg);  // display Celcius
    Serial.print("Case: "); 
    Serial.println(resistorCase);
//    Serial.print("Running Average: "); 
//    Serial.println(constantAvg);
//    Serial.print("Running Average Data Points: "); 
//    Serial.println(constantCount);
  }
  
void caseStatements()
  {
    switch (resistorCase) {
    case 1:
      digitalWrite(resitorPin, LOW); 
      digitalWrite(topFan, HIGH);
      Serial.println("Fan On, Resistor Off");
      variableDelay = 500; 
      break;
    case 2:
      digitalWrite(resitorPin, LOW); 
      digitalWrite(topFan, LOW);
      Serial.println("Fan Off, Resistor Off");
      variableDelay = 5000;
      break;
    case 3:
      digitalWrite(resitorPin, HIGH); 
      digitalWrite(topFan, LOW);
      Serial.println("Fan Off, Resistor On");
      variableDelay = 1000;
      break;
    case 4:
      digitalWrite(resitorPin, LOW); 
      digitalWrite(topFan, LOW);
      Serial.println("Fan Off, Resistor Off");
      variableDelay = 5000;
      break;
    }
  }

void Choose_Case()
  {
    if (movingAvg > 45.7)
    {
      resistorCase = 1; //Hotter than 45 degrees
    }
 
  else if (movingAvg == 45)
    {
      resistorCase = 2; //Temp is 45
    }
  else if (movingAvg < 44.5)
    {
     resistorCase = 3; //Temp less than 44.5
    }
 
  else
    {
      resistorCase = 4;
    }
  }

ISR(TIMER1_COMPA_vect)  //timer1 interrupt 1Hz toggles pin 13 (LED)
  {
    var = 0;
    movingSum = 0;
    movingAvg = 0;
    while (var < 200)
      {
      movingSum = movingSum + float(Thermistor(analogRead(0)));
      movingAvg = movingSum / 200;
      
      var++; 
      }
    
    
//    constantSum = constantSum + float(Thermistor(analogRead(0)));
//    constantCount++;
//    constantAvg = constantSum / constantCount;
    
//  if (sampleCount < 5)
//    {
//      movingSum = movingSum + float(Thermistor(analogRead(0)));
//      sampleCount++;
//    }
//  else if (sampleCount == 5)
//    {
//      movingSum = movingSum + float(Thermistor(analogRead(0)));
//      movingAvg = movingSum / 5;
//      movingSum = 0; 
//      sampleCount = 1;  
//    }
  
  }


