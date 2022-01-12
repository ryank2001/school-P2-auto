#include <car.h>
#include <sensoren.h>
#include <Wifiserver.h>
#include <automaticdriving.h>


#define motorpinL1 26
#define motorpinL2 27
#define motorpinR1 14
#define motorpinR2 12


Car car = Car(motorpinL1,motorpinL2, motorpinR1, motorpinR2);
Ultrasoon ultrasoonlinks = Ultrasoon(25,33);
Ultrasoon ultrasoonrechts = Ultrasoon(19,18);
Ultrasoon ultrasoonvoor = Ultrasoon(5,17);


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
    delay(1000);
    

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
 if (drivestate == "DONT FORGET"){
   manualdriving();
 }
 else{
   automaticDriving();
 }
 
}
  
  
  