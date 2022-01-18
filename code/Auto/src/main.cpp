#include <car.h>
#include <sensoren.h>
#include <Wifiserver.h>
#include <automaticdriving.h>


#define motorpinL1 33
#define motorpinL2 23
#define motorpinR1 32
#define motorpinR2 22


Car car = Car(motorpinL1,motorpinL2, motorpinR1, motorpinR2);
Ultrasoon ultrasoonlinks = Ultrasoon(26,25);
Ultrasoon ultrasoonrechts = Ultrasoon(19,18);
Ultrasoon ultrasoonvoor = Ultrasoon(5,17);
HallSensor HallSensorl = HallSensor(36);


void manualdriving(){
  if(manualactionstate == "stopped"){
    car.standStill();
  }
  else if(manualactionstate == "forward"){
    car.driveForward();
  } 
  else if(manualactionstate == "backward"){
    car.drivebackward();
  }
  else if(manualactionstate == "left"){
    car.turnleft();
  }
  else if(manualactionstate == "right"){
    car.turnright();
  }
}


void automaticDriving(){
  if (ultrasoonvoor.read() <=35 ){
    car.turnright();
    delay(1150);
    

  }
  if(ultrasoonlinks.read() <= 15){

    car.turnright();
    delay(1150);
  }
  if(ultrasoonrechts.read() <=15){
    car.turnleft();
    delay(1150);
  }
  else{
    car.driveForward();
  }
}


void setup(){
  Serial.begin(115200);
  serverSetup();
}



void loop(){
 webserver();
 
 if (drivestate == "manual"){
   manualdriving();
 }
 else{
   automaticDriving();
 }
 
}
  
  
  