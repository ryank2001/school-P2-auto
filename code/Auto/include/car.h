#include <Arduino.h>



class Car {
    private:
        int DCmotorpinL1;    //eerste pin waaraan de DCmotoren van de linker kant op worden aangestuurd.
        int DCmotorpinL2;    //eerste pin waaraan de DCmotoren van de linker kant op worden aangestuurd.
        int DCmotorpinR1;    //eerste pin waaraan de DCmotoren van de rechter kant op worden aangestuurd.
        int DCmotorpinR2;    //eerste pin waaraan de DCmotoren van de rechter kant op worden aangestuurd.
        
        int DCMotorspeedpin;//Pin waarmee de snelheid van de dc motoren word geregeld
        
        

    public:
        
        Car(int DCMotorpinL1, int DCMotorpinL2, int DCMotorpinR1 ,int DCMotorpinR2){
            DCmotorpinL1 = DCMotorpinL1;
            DCmotorpinL2 = DCMotorpinL2;
            DCmotorpinR1 = DCMotorpinR1;
            DCmotorpinR2 = DCMotorpinR2;
            
            //De pinnen van de motoren op output zetten.
            pinMode(DCmotorpinL1, OUTPUT);
            pinMode(DCmotorpinL2, OUTPUT);
            pinMode(DCmotorpinR1, OUTPUT);
            pinMode(DCmotorpinR2, OUTPUT);

        
        }

        void driveForward(){
            digitalWrite(DCmotorpinL1, HIGH);
            digitalWrite(DCmotorpinR1, LOW);
            digitalWrite(DCmotorpinL2, HIGH);
            digitalWrite(DCmotorpinR2, LOW);
        }

        void drivebackward(){
            digitalWrite(DCmotorpinL1, LOW);
            digitalWrite(DCmotorpinR1, HIGH);
            digitalWrite(DCmotorpinL2, LOW);
            digitalWrite(DCmotorpinR2, HIGH);
        }

        void turnright(){
            digitalWrite(DCmotorpinL1, LOW);
            digitalWrite(DCmotorpinR1, HIGH);
            digitalWrite(DCmotorpinL2, HIGH);
            digitalWrite(DCmotorpinR2, LOW);
        }

        void turnleft(){
            digitalWrite(DCmotorpinL1, HIGH);
            digitalWrite(DCmotorpinR1, LOW);
            digitalWrite(DCmotorpinL2, LOW);
            digitalWrite(DCmotorpinR2, HIGH);
        }

        void standStill(){
            digitalWrite(DCmotorpinL1, LOW);
            digitalWrite(DCmotorpinR1, LOW);
            digitalWrite(DCmotorpinL2, LOW);
            digitalWrite(DCmotorpinR2, LOW);
        }


        
        
};


