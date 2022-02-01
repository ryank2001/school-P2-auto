#include <car.h>
#include <sensoren.h>

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
        }

        if( LineTracking == "links"){
            LineTracking = "rechts";
        }
    }
}


void LijnDetectie(){
if(LineTracking == "rechts"){
    for (int i = 0; i < 10; i++)
    {
        if(IRSensorlinks.read()){
            car.turnright();
        }
        else if(IRSensorrechts.read()){
            car.turnleft();
        }
        else{
            car.driveForward();
        }
        delay(100);
    }
    for (int i = 0; i < 10; i++)
    {
        if(IRSensorlinks.read()){
            car.turnright();
        }
        else if(IRSensorrechts.read()){
            car.turnleft();
        }
        else{
            car.turnright();
        }
        delay(100);
    }

   


}
}





