#include <car.h>
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

  delay(1000)
 Serial.println("Kies hier welke handeling u wilt uitvoeren:0- automatic 
  1 - sta still
  2- rij recht naar voren
  3- rij naar voren/stuur links
  4- rij naar voren/ stuur rechts
  5- rij recht naar achter
  6- rij naar achter/stuur links
  7- rij naar achter/ stuur rechts");
  while(Serial.available() == 0)
  


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

  
  int handeling = Serial.readString();
Switch (handeling){
 Case 1:
 Break;

 Case 2:
  car.DriveForward();
  Break;

  Case 3:
  car.DriveForward();
  car.SteeringWheelAngle(45);   
  Break;

  Case 4:
  car.DriveForward();
  car.SteeringWheelAngle(135);
  Break;

  Case 5:
  car.DriveBackwards();
  Break;

  Case 6:
  car.DriveBackwards();
  car.SteeringWheelAngle(45);
  Break;

  Case 7:
  car.DriveBackwards();
  car.SteeringWheelAngle(135);
  Break;
}
  

  
}
  void loop(){
  handeling();
  }