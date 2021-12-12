#include <Arduino.h>



class Car {
    private:
        int DCmotorpin1;    //eerste pin waaraan de DCmotoren worden aangestuurd.
        int DCmotorpin2;    //tweede pin waaraan de DCmotoren worden aangesloten.
        int DCMotorspeedpin;//Pin waarmee de snelheid van de dc motoren word geregeld
        int servopin;

        int speed;          //waarde die de sneheid representeerd, kan tussen 0-255.
        int steeringangle;  //waarde die de posititie van de wielen representeerd.

        

    public:
        
        Car(int DCMotorpin1, int DCMotorpin2, int DCMotorspeedpin ,int Servopin){
            //het opgeven van de juiste pinnen voor de motoren en het op 90 graden zetten van de steerangle.
            DCmotorpin1 = DCMotorpin1;
            DCmotorpin2 = DCMotorpin2;
            DCMotorspeedpin = DCMotorspeedpin;
            servopin = Servopin;
            steeringangle = 90;

            //De pinnen van de motoren op output zetten.
            pinMode(DCmotorpin1, OUTPUT);
            pinMode(DCmotorpin2, OUTPUT);
            pinMode(DCMotorspeedpin, OUTPUT);
            pinMode(servopin, OUTPUT);

            


        }

        //Methode voor het veranderen van de snelheid van de auto, de waarde mag maximaal 255 zijn.
        void SetCarSpeed(int Speed){
            if (speed > 255){
                Serial.println("invalid input");
            }
            else{
            speed = Speed;
            analogWrite(DCMotorspeedpin, speed);
            }
        }

        //methode voor het vooruit laten rijden van de auto.
        void DriveForward(){
            digitalWrite(DCmotorpin1, HIGH);
            digitalWrite(DCmotorpin2, LOW);
        }
        
        //Methode voor het achteruit laten rijden van de auto.
        void DriveBackwards(){
            digitalWrite(DCmotorpin1, LOW);
            digitalWrite(DCmotorpin2, HIGH);
        }

        //methode voor het laten stoppen van de auto.
        void StopDriving(){
            digitalWrite(DCmotorpin1, LOW);
            digitalWrite(DCmotorpin2, LOW);
        }



        //methode voor het instellen van de wielen in een opgegeven hoek.
        void SteeringWheelAngle(int angle){
            long int pwm = (angle*10.6) + 460;      // Convert angle to microseconds
            for (angle = 0; angle <= 5; angle += 1)  {
                digitalWrite(servopin, HIGH);
                delayMicroseconds(pwm);
                digitalWrite(servopin, LOW);
                delay(40);                   // Refresh cycle of servo
            }
            steeringangle = angle;
        }

        //methode om de servo 1 graden naar rechts te laten draaien.
        void SteerRight(){
            SteeringWheelAngle(++steeringangle);
        }

        //methode om de servo 1 graden naar links te laten draaien.
        void SteerLeft(){
            SteeringWheelAngle(--steeringangle);
        }
};
