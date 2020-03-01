#include <Servo.h>

#define PWMA 10
#define AIN2 4
#define AIN1 5
#define PWMB 9
#define BIN2 8
#define BIN1 7
#define TURBINA 3


int Vel_turbina = 90;

Servo myservo;

void setup() {
  
  pinMode(PWMA,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  delay(1000);
  myservo.attach(TURBINA);
  for (int i = 0;i <= Vel_turbina;i++){
    myservo.write(i);
    delay(200);
  }
}

void loop() {
  
  //Pruebas de motores solos

  analogWrite(PWMA,40);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(AIN1,LOW);
  analogWrite(PWMB,0);

  delay(1000);

  analogWrite(PWMA,0);
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(AIN1,LOW);
  analogWrite(PWMB,40);

}
