#include <Arduino.h>

class sensor{
    private:
        int sensorpin;

    public:
        sensor(int Sensorpin){
            sensorpin = Sensorpin;
            pinMode(sensorpin, OUTPUT);
        } 
    
        boolean readsensor(){
           return digitalRead(sensorpin);

        }

};
