#include <car.h>
#include <sensoren.h>
#include <Wifiserver.h>
#include <automaticdriving.h>


#define motorpinL1 26
#define motorpinL2 27
#define motorpinR1 14
#define motorpinR2 12
Car car = Car(motorpinL1,motorpinL2, motorpinR1, motorpinR2);


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
  
  
  