#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // CONNECT BT RX PIN TO ARDUINO 11 PIN | CONNECT BT TX PIN TO ARDUINO 10 PIN
int powerPinSensor = 9;
int powerPinBLE = 8;

void setup()
{

  Serial.begin(9600);
  Serial.println("Ready");
  BTSerial.begin(9600); 
  pinMode(powerPinSensor, OUTPUT);
  pinMode(powerPinBLE, OUTPUT);

}

String connectState = "D";
String responseState = "N";
char temp;
void loop()
{
  //SENSOR PART
  
  //Activate Sensor
  digitalWrite(powerPinSensor, HIGH);
  delay(100);
  //Get value
  int sensorValue = analogRead(A0);
  int sensorValuePercentage = map(sensorValue, 300, 1000, 100, 0);
  //For log
  Serial.println(sensorValue);
  Serial.println(sensorValuePercentage);
  //Disable sensor
 digitalWrite(powerPinSensor, LOW);



  //BLE PART
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
    //Serial.print("Wait..");
  }
  //Connexion achieve
  Serial.print("Connected");

  
  //Send value
 BTSerial.print(sensorValuePercentage);

  //Wait response for central
  while (responseState != "Y") { 
    
    if (BTSerial.available())
    {
      
      while (BTSerial.available())
      {
        
        temp = (char)BTSerial.read();
        responseState = temp;
        Serial.print(responseState);
        if (responseState == "V")
        {
           BTSerial.print(sensorValuePercentage);
        }
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
