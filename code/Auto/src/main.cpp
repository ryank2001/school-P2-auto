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
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  }


 void opdracht(){
  if (SerialBT.available()) {
    char handeling = SerialBT.read();

  switch (handeling){
  case '1':
 break;

 case '2':
  car.DriveForward();
  car.SteeringWheelAngle(90);  
  break;

  case '3':
  car.DriveForward();
  car.SteeringWheelAngle(45);   
  break;

  case '4':
  car.DriveForward();
  car.SteeringWheelAngle(135);
  break;

  case '5':
  car.DriveBackwards();
  car.SteeringWheelAngle(90);  
  break;

  case '6':
  car.DriveBackwards();
  car.SteeringWheelAngle(45);
  break;
  
  case '7':
  car.DriveBackwards();
  car.SteeringWheelAngle(135);
  break;
  }
  }
  
  
  
  
 
 }
  void loop(){
  opdracht();
  }
  
  
  