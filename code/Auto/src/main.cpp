#include "Car.h"
#include <BluetoothSerial.h>

/* Check if Bluetooth configurations are enabled in the SDK */
/* If not, then you have to recompile the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define motorpin1 25
#define motorpin2 26
#define motorspeedpin 34 
#define servopin 27

Car car(motorpin1,motorpin2, motorspeedpin, servopin);

BluetoothSerial SerialBT;

char aan;
char vooruit;
char achteruit;
char links;
char rechts;

void setup() {
  Serial.begin(115200);
  SerialBT.begin();
  Serial.println("Bluetooth Started! Ready to pair...");
 
  


}


void readdata(){
  if (SerialBT.available())
  {
    aan = SerialBT.read();
    vooruit = SerialBT.read();
    achteruit = SerialBT.read();
    links = SerialBT.read();
    rechts = SerialBT.read();
    char dump = SerialBT.read();
    dump = SerialBT.read();
  }
}

void loop() {
  readdata();
 
  if(vooruit == '1'){
    Serial.print("i work");
    car.DriveBackwards();

  }
  else if(achteruit == '1'){
     car.DriveForward();
  }
  else{
    car.StopDriving();
  }
  if (links == '1'){
    car.SteeringWheelAngle(45);
  }
  else if(rechts == '1'){
    car.SteeringWheelAngle(135);
  }
  else{
    car.SteeringWheelAngle(90);
  }
  delay(500);
 
}