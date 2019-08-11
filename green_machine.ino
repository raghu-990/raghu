#include <Wire.h>
float temp;
int SENSE= A0; // Soil Sensor input at Analog PIN A0
int value= 0;
#define LIGHT 2 // define pint 2 for sensor
#define RELAY 9 // define pin 9 as for relay
#include "DHT.h"           // Including DHT22 library
#include "LiquidCrystal.h" // Including LCD library
#define DHTPIN 6      // Declaring pin 6 for communicating to DHT22 sensor
#define DHTTYPE DHT22 // Declaring the type of DHT sensor we are using (DHT22 or DHT11)
DHT dht(DHTPIN, DHTTYPE);          // Declaring DHT connection and type
int Motor_Pin1 = 4;  // pin 2 on L293D
int Motor_Pin2 = 3;  // pin 7 on L293D
int Enable = 5;      // pin 1 on L293D
void setup() {
Serial.begin(9600);
pinMode(7, OUTPUT);     
Serial.begin(9600);// setup Serial Monitor to display information
pinMode(LIGHT, INPUT_PULLUP);// define pin as Input  sensor
pinMode(RELAY, OUTPUT);// define pin as OUTPUT for relay
pinMode(Motor_Pin1, OUTPUT);  
pinMode(Motor_Pin2, OUTPUT);
pinMode(Enable, OUTPUT);
dht.begin();     // Initializes DHT sensor
}

void loop() {
   // Light LDR Sensor Code by Robojax.com 20180210
  int L =digitalRead(LIGHT);// read the sensor 
  
      if(L == 1){
    Serial.println(" light is ON");
    digitalWrite(RELAY,LOW);// turn the relay ON
  }else{

     Serial.println("  === light is OFF");
     digitalWrite(RELAY,HIGH);// turn the relay OFF
  }
  delay(500);
 // Light LDR Sensor Code by Robojax.com 20180210
 float temp = dht.readTemperature(); // Reading the temperature in Celsius

  if (isnan(temp)) {                  // Validating received data
    delay(1000);
    return;
  }

  

  if(temp <25 ) {                 // If the temperature less than 25
    analogWrite(Enable,0);        // 0% PWM duty cycle      
    delay(100);
  }
  else if(temp>=25 & temp<30) {      // If the temperature is between 25 & 30
    analogWrite(Enable, 77);         // 30% of maximum duty cycle value (255). 
    delay(100);
  }
  else if(temp>=30 & temp<35) {      // If the temperature is between 30 & 35
    analogWrite(Enable, 153);        // 60% of maximum duty cycle value (255).
    delay(100);
  }
  else if(temp>=35) {                // If the temperature is above 35
    analogWrite(Enable, 255);        // 100% duty cycle
    delay(100);
  }

  digitalWrite(Motor_Pin1, LOW);  // To drive the motor in a particular direction
  digitalWrite(Motor_Pin2, HIGH); // To drive the motor in a particular direction

  delay(500); // 2 seconds delay
  value= analogRead(A0);
value= value/10;


   
if(value<50)
{
digitalWrite(7,HIGH);      

 Serial.println(" motor is ON");
}
   
else
{       
digitalWrite(7,LOW);     
 Serial.println(" motor is off");
}
}
