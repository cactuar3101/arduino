#include <ESP32Servo.h>



Servo myservo;  
int pos = 0;    
#if defined(ARDUINO_ESP32S2_DEV)
int servoPin = 17;
#else
int servoPin = 18;
#endif

const byte cut = 0;

void setup() {
  pinMode(cut, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(cut), rotate, CHANGE);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);
  myservo.attach(servoPin, 1000, 2000);  
}

void loop() {

    myservo.write(pos);              
    delay(15);                     
  
}

void rotate(){
  pos = pos + 30;
  if(pos >= 180)
    pos = 0;
}
