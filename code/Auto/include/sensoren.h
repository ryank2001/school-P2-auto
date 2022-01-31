#include <Arduino.h>

class Ultrasoon {
    private:
        int echopin;
        int triggerpin;

    public:

        Ultrasoon(int Echopin, int Triggerpin){
            echopin = Echopin;
            triggerpin = Triggerpin;
            pinMode(triggerpin, OUTPUT); // Sets the trigPin as an OUTPUT
            pinMode(echopin, INPUT); // Sets the echoPin as an INPUT

        }

        int readultrasoon(){
            long duration; // variable for the duration of sound wave travel
            int distance;
             // Clears the trigPin condition
            digitalWrite(triggerpin, LOW);
            delayMicroseconds(2);
            // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
            digitalWrite(triggerpin, HIGH);
            delayMicroseconds(10);
            digitalWrite(triggerpin, LOW);
            // Reads the echoPin, returns the sound wave travel time in microseconds
            duration = pulseIn(echopin, HIGH);
            // Calculating the distance
            distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
            
            return distance;
        }
};