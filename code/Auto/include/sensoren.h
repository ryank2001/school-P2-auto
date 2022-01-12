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
            

            return dist;

        }




};