#define PWMA 10
#define AIN2 4
#define AIN1 5
#define PWMB 9
#define BIN2 8
#define BIN1 7


void setup() {
  pinMode(PWMA,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
}

void loop() {

  //Prueba hacia adelante
  for (int i = 5;i < 100; i++){
      analogWrite(PWMA,i);
      digitalWrite(AIN1,HIGH);
      digitalWrite(AIN2,LOW);
      digitalWrite(BIN1,HIGH);
      digitalWrite(AIN1,LOW);
      analogWrite(PWMB,i);
  }

  delay(1000);

  //Prueba hacia atras
  for (int i = 5;i < 100; i++){
      analogWrite(PWMA,i);
      digitalWrite(AIN1,LOW);
      digitalWrite(AIN2,HIGH);
      digitalWrite(BIN1,LOW);
      digitalWrite(AIN1,HIGH);
      analogWrite(PWMB,i);
  }

  delay(1000);

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
