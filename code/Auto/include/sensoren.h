

class Ultrasoon{
    private:
        int trigPin;
        int echoPin;
    public:

        Ultrasoon(int TrigPin, int EchoPin){
            trigPin = TrigPin;
            echoPin = EchoPin;
            pinMode(trigPin, OUTPUT);
            pinMode(echoPin, INPUT);
        }

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

class HallSensor{
    private:
        int sensorpin;

    public:
        HallSensor(int Sensorpin){
            sensorpin = Sensorpin;

            pinMode(sensorpin, INPUT);
        }

        boolean read(){
            int waarde = digitalRead(sensorpin);
           
            
            return waarde;
        }


};

class IRSensor{
    private:
        int sensorpin;

    public:
        IRSensor(int Sensorpin){
            sensorpin = Sensorpin;
            pinMode(sensorpin, INPUT);

    }

  boolean read(){
        int waarde = digitalRead(sensorpin);
        Serial.print(waarde);
        return waarde;


    }



};
