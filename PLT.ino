#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // CONNECT BT RX PIN TO ARDUINO 11 PIN | CONNECT BT TX PIN TO ARDUINO 10 PIN
int powerPinSensor = 9;
int powerPinBLE = 8;

void setup()
{

  Serial.begin(9600);
  Serial.println("Ready");
  BTSerial.begin(9600);  // HC-05 default speed in AT command more
  pinMode(powerPinSensor, OUTPUT);
  pinMode(powerPinBLE, OUTPUT);

}

String connectState = "D";
String responseState = "N";
char temp;
void loop()
{
  digitalWrite(powerPinBLE, HIGH);
  
  //Wait for connexion
  while (connectState != "C") {

    if (BTSerial.available())
    {

      while (BTSerial.available())
      {
        temp = (char)BTSerial.read();
        connectState = temp;
        Serial.print(connectState);
        delay(5);
      }
    }
    Serial.print("Wait..");
  }
  //Connexion achieve
  Serial.print("Connected");

  
  //Send value
 BTSerial.print(44);

  //Wait response for central
  while (responseState != "Y") { 
    
    if (BTSerial.available())
    {
      
      while (BTSerial.available())
      {
        
        temp = (char)BTSerial.read();
        responseState = temp;
        Serial.print(responseState);
        delay(5);
      }

    }
  }
    Serial.print("Value sent succefully");
    
    
  //Reset state and shut down the module
    connectState = "D";
    responseState = "N";
    digitalWrite(powerPinBLE, LOW);
delay(5000);
    
  }
