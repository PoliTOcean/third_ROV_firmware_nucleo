#include <Servo.h>

byte servoPin[7] = {A0, A2, D10, A4, A3, D9, D6};

byte servoPinA7 = PA2;

Servo servoA7;
Servo servo[7];

int i=0;
int valA7;
int val[7] = {1600, 1600, 1600, 1600, 1600, 1600, 1600};



int salita = 1;
int salitaA0 = 0;
void setup() {
  
 Serial.begin(9600);

 for(int n= 0; n<7; n++){
  servo[n].attach(servoPin[n]);
  servo[n].writeMicroseconds(1500); // send "stop" signal to ESC.
 }

 servoA7.attach(servoPinA7);
 servoA7.writeMicroseconds(1500);
 


 delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  
  Serial.println("Enter PWM signal value 1100 to 1900, 1500 to stop");
  
  //while (Serial.available() == 0);
  
  //Serial.parseInt(); 
  
  for(int n=0; n<7; n++){
    setPWM_Motor(servo[n], val[n], i);
  }
  setPWM_Motor(servoA7, valA7, i);
  delay(30);
}


int setPWM_Motor(Servo servo, int val, int i){
  /*
  if(i==1){
    
    val = 1100;
  }
  if(i>1 && val <= 1900 && salita == 1){
    val +=5;  
    if(val >= 1900){
      salita = 0;
    }
  }
  else if(val >= 1100 && i>1 && salita ==0){
    val -=5;  
    if(val <= 1100){
      salita = 1;
    }
  }
  
  */
  
  
  if(val < 1100 || val > 1900)
  {
    Serial.println(val);
    Serial.println("not valid");
  }
  else
  {
    servo.writeMicroseconds(val); // Send signal to ESC.
  }



  
  i++;

  return i;
}
