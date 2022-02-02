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
  
       
   
   
   // Hierin staat aan welke kant de ACM standaard rijdt, zodra deze een obstakel detecteert gaat hij naar de andere kant en rijdt verder.
    if(ultrasoonvoor.read() <= 20){
            car.turnleft();
            delay(500);
            car.driveForward();
            delay(800);
        }

        
    }



void LijnDetectie(){
if(LineTracking == "rechts"){
    for (int i = 0; i < 90; i++)
    {   
      
        if(IRSensorrechts.read()){
            car.turnleft();
            delay(40);
        }
        else if(IRSensorlinks.read()){
            car.turnright();
            delay(50);
        }
        else if(ultrasoonrechts.read() <= 5){
            car.driveForward();
            delay(5);
            car.turnleft();
           
        }
        else if(ultrasoonvoor.read() <= 20){
            car.turnleft();
            delay(700);
            car.driveForward();
            delay(800);
        }
       
        
        else{
            car.driveForward();
        }
        delay(5);
        
    }
    for (int i = 0; i < 20; i++)
    {
        
        if(IRSensorrechts.read()){
            break;
        }

        
        else if(ultrasoonrechts.read() <= 5){
            car.driveForward();
            delay(5);
            car.turnleft();
           
        }
        
        else{
            car.turnright();
        }
        delay(5);
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
   MagneetDetectie();
   
   LijnDetectie(); 
 }
 
}
  
  
  