
//Class voor het initieren van een ultrasoon sensor
class Ultrasoon{
    private:
        int trigPin;    //bevat op welke pin de triggerpin van de ultrasoon is aangesloten
        int echoPin;    //bevat op welke pin de echopin is aangesloten van de ultrasoon
    public:


        //constructor voor de ultrasoon sensor, Deze deze de juiste pinnummers in het geheugen en det de pinnen in de juiste pinmode
        Ultrasoon(int TrigPin, int EchoPin){
            trigPin = TrigPin;
            echoPin = EchoPin;
            pinMode(trigPin, OUTPUT);
            pinMode(echoPin, INPUT);
        }

        //functie voor het uitlezen van van de afstand die de ultrasoon leest
       long int read(){
            digitalWrite(trigPin, LOW); 
            delayMicroseconds(2); 
            digitalWrite(trigPin, HIGH); 
            delayMicroseconds(10); 
            digitalWrite(trigPin, LOW); 
            long int dur = pulseIn(echoPin, HIGH); 
            long int dist = dur / 58.2; 
            
             Serial.println(dist);
            return dist;
           

        }




};


//Class voor het initieren van een hallsensor
class HallSensor{
    private:
        int sensorpin; //bevat de pin waarop de hallsensor op aangesloten is

    public:
        //constructor voor de Hallsensor, deze zet de sensorpin in het geheugen en zet de pin in de juiste modus
        HallSensor(int Sensorpin){
            sensorpin = Sensorpin;

            pinMode(sensorpin, INPUT);
        }

    	//functie voor het uitlezen van de hallsensor
        boolean read(){
            int waarde = digitalRead(sensorpin);
            return waarde;
        }


};
//Class voor het initieren van een IRsensor
class IRSensor{
    private:
        int sensorpin;  //bevat de pin waarop de IRsensor op aangesloten is

    public:
        //constructor voor de IRsensor, deze zet de sensorpin in het geheugen en zet de pin in de juiste modus
        IRSensor(int Sensorpin){
            sensorpin = Sensorpin;
            pinMode(sensorpin, INPUT);

    }

    //functie voor het uitlezen van de IRsensor
    boolean read(){
        int waarde = digitalRead(sensorpin);
        return waarde;


    }



};
