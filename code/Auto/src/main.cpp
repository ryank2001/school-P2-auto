#include <car.h>
#include <sensoren.h>
#include <Wifiserver.h>




#define motorpinL1 33
#define motorpinL2 23
#define motorpinR1 32
#define motorpinR2 22


Car car = Car(motorpinL1,motorpinL2, motorpinR1, motorpinR2);
Ultrasoon ultrasoonlinks = Ultrasoon(26,25);
Ultrasoon ultrasoonrechts = Ultrasoon(19,18);
Ultrasoon ultrasoonvoor = Ultrasoon(5,17);
HallSensor HallSensorLinks = HallSensor(36);
//HallSensor HallSensorRechts = HallSensor();
IRSensor IRSensorlinks = IRSensor(14);
IRSensor IRSensorrechts = IRSensor(12);


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

String LineTracking = "rechts";

//Dit is de functie voor het detecteren van het magnetische veld, als deze gedecteerd wordt stop de ACM.
void MagneetDetectie(){
    if(HallSensorLinks.read()){
        car.standStill();
        delay(3500);
        
    }
}
//Dit is de functie  voor detectie en het registreren en verwerken van tunnels
void ObstakelDetectie(){
   if(ultrasoonlinks.read() <= 20 && ultrasoonrechts.read() <= 20){
       if(ultrasoonlinks.read()<= 5){
           car.turnright();
           delay(500);
       }
        if(ultrasoonrechts.read() <= 5){
            car.turnleft();
            delay(500);
        }
    car.driveForward();
   }
   
   // Hierin staat aan welke kant de ACM standaard rijdt, zodra deze een obstakel detecteert gaat hij naar de andere kant en rijdt verder.
    if(ultrasoonvoor.read() <= 20){
        if( LineTracking == "rechts"){
            LineTracking = "links";
            car.turnleft();
            delay(300);
        }

        if( LineTracking == "links"){
            LineTracking = "rechts";
            car.turnright();
            delay(300);
        }
    }
}


void LijnDetectie(){
if(LineTracking == "rechts"){



      for (int i = 0; i < 15; i++)
      {
        if(IRSensorrechts.read() == 1){
        car.turnright();
        delay(100);   
        }
        else if(IRSensorlinks.read() == 1){
          car.turnleft();
          delay(1000);
        }
        else{
          car.driveForward();
          delay(200);
        }
      }
      for (int i = 0; i < 5; i++){
      }
      if(IRSensorrechts.read() == 1){
        car.turnright();
        delay(100);   
        }
        else{
          car.turnleft();
          delay(200);
        }
    
    
}



if(LineTracking == "links"){
      for (int i = 0; i < 15; i++)
      {
        if(IRSensorlinks.read() == 1){
        car.turnleft();
        delay(100);   
        }
        else if(IRSensorrechts.read() == 1){
          car.turnleft();
          delay(1000);
        }
        else{
          car.driveForward();
          delay(200);
        }
        
    
      }
      if(IRSensorlinks.read() == 0){
      car.turnright();
      delay(200);
      }
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
   
   LijnDetectie(); 
 }
 
}
  
  
  