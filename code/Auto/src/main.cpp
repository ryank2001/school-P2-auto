#include <car.h>        //Header file met daarin de Car class
#include <sensoren.h>   //Header file met daarin de classes van de sensoren
#include <Wifiserver.h> //Header file met daarin de code van de webserver




#define motorpinL1 33 //motorpin 1 voor de linker motors
#define motorpinL2 23 //Mortorpin 2 voor de linker motors
#define motorpinR1 32 //Motorpin 1 voor de rechter motors
#define motorpinR2 22 //motorpin 2 voor de rechter motor



Car car = Car(motorpinL1,motorpinL2, motorpinR1, motorpinR2); //Aanmaken van De car object met de juiste pinnen
Ultrasoon ultrasoonlinks = Ultrasoon(26,25);                  //Aanmaken van de Ultrasoon object voor de linker ultrasoon
Ultrasoon ultrasoonrechts = Ultrasoon(19,18);                 //Aanmaken van de Ultrasoon object voor de rechter ultrasoon
Ultrasoon ultrasoonvoor = Ultrasoon(5,17);                    //Aanmaken van de Ultrasoon object voor de voorste ultrasoon
HallSensor HallSensorLinks = HallSensor(36);                  //aanmaken van de hallsensor object voor de linker hallsensor
//HallSensor HallSensorRechts = HallSensor();                 //Aanmaken van de hallsensor object van de rechter hallsensor
IRSensor IRSensorlinks = IRSensor(14);                        //Aanmaken van de IRsensor object voor de linker Irsensor
IRSensor IRSensorrechts = IRSensor(12);                       //Aanmaken van de IRsensor object voor de rechter IRsensor



//functie voor het besturen van de auto door middel van de webserver.
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


//Dit is de functie voor het detecteren van het magnetische veld, als deze gedecteerd wordt stop de ACM.
void MagneetDetectie(){
    if(HallSensorLinks.read()){
        car.standStill();
        delay(3500);
        
    }
}


//Functie voor het detecteren van objecten door middel van de voorste ultrasoon
void ObstakelDetectie(){
  /*Als de voorste ultrasoon een object ziet binnen 20 cm afstand zal voor een halve seconde naar links draaien 
  en vervolgens een stuk vooruit rijden. Als de ACM hiermee het object heeft ontweken zullen de sensoren aan de zijkant zorgen dat hij er niet meer in rijd*/
    if(ultrasoonvoor.read() <= 20){
            car.turnleft();
            delay(500);
            car.driveForward();
            delay(500);
    }
}


//Functie voor het detecteren en de handeling van de lijnen.
void LijnDetectie(){
    //de auto zal voor een tijd van 1 seconde voor uit willen rijden, 
    //deze periode bestaat uit 200 periodes van 5 ms waarin de auto blijft checken of deze een lijn paseert.
    for (int i = 0; i < 200; i++)
    {   

        //Als de rechter IR een lijn detecteerd zal de ACM naar links sturen.
        if(IRSensorrechts.read()){
            car.turnleft(); 
        }
        //Als de linker IR een lijn detecteerd zal de ACM maar rechts sturen.
        else if(IRSensorlinks.read()){
            car.turnright();
        }
        //Als dit beide niet het geval is zal de ACM vooruit rijden.
        else{
            car.driveForward();
        }
        delay(5);
    }

    //Na de periode van 1 seconde vooruit rijden zal de auto proberen voor 0.25 seconden naar rechts te rijden om de lijn op te zoeken
    //Deze periode bestaat uit 50 periodes van 5 ms waar constand word gechecked of de ir sensor de lijn niet passeert of de ultrasoon een object detecteerd
    for (int i = 0; i < 50; i++){
        
        //Als de rechter IR sensor een lijn detecteerd zal hij stoppen Met proberen om naar rechts te rijden.
        if(IRSensorrechts.read()){
            break;
        }

        //Als de ultrasoon aan de rechter kant een obstakel detecteerd zal de auto naar links sturen.
        else if(ultrasoonrechts.read() <= 5){
            car.driveForward();
            delay(5);
            car.turnleft();
           
        }
        //Als deze beide niet waar zijn zal de auto naar rechts sturen
        else{
            car.turnright();
        }
        delay(5);
    }
}




//Functie die 1 keer word gerunt warneer de ACM gaat opstarten.
void setup(){
  Serial.begin(115200); //Opstarten van de seriele monitor
  serverSetup();        //Opstarten van de webserver
}


//Functie die na dat de setup is uitgevoert constant gaat loopen.
void loop(){
webserver(); //de webserver controlleren of er inputs zijn vanuit de webserver.
 
 //If statement die checked of via de webserver de input van de ACM naar manueel is veranderd
 //Als dit het geval is zal deze de functie gebruiken voor manueele besturen, zo niet zal deze de magneet, obstakel en lijn detectie controlleren.
  if (drivestate == "manual"){
    manualdriving();
  }
  else{
     MagneetDetectie();
    ObstakelDetectie();
    LijnDetectie(); 
  }
 
}
  
  
  