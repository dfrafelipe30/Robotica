#include <QTRSensors.h>
#define PWMA  3
#define AIN2  4
#define AIN1  5
#define STBY  6
#define BIN1  7
#define BIN2  8
#define PWMB  9
#define START  12
// #define BOTON 12
#define LED     13
#define NUM_SENSORS   8

int P = 0;
int I = 0;
int D = 0;
int LAST = 0;
float vel;
float VelDer = 0;
float VelIzq = 0;
//////////////////////////////////////////////////////////////////////////////////////////
//
int Error = 3500;
// Constantes para PID
float Kp = 1.3;//0.02
float Kd = 13;//4.8;//1.71
float Ki = 0.8;// 0.0054
int VelMax = 210;
int frente = 130;
int reversa = 120;
QTRSensorsAnalog qtra((unsigned char[]) {
  A0, A1, A2, A3, A4, A5, A6, A7
},
NUM_SENSORS);
unsigned int sensorValues[NUM_SENSORS];
unsigned int position = 0;

void setup()
{
  //pinMode(BOTON, INPUT_PULLUP);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(START, INPUT);

  //while (digitalRead(BOTON) == 1)//espera de calibracion
  //{
    //digitalWrite(LED, HIGH);
    //digitalRead(BOTON);
  //}
  delay(3000);

  for (int j = 0; j < 70; j++)
  {
    digitalWrite(LED, HIGH);
    delay(20);
    qtra.calibrate();
    digitalWrite(LED, LOW);
    delay(20);
  }

  while (digitalRead(START) == 0 )//arranque
  {
    digitalWrite(LED, LOW);
    digitalRead(START);
  }

  digitalWrite(LED, HIGH);
  //delay(200);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, 255);
  analogWrite(PWMB, 255);
  digitalWrite(STBY, HIGH);
}
void loop()
{
  if (digitalRead(START) == 0)
  {
    digitalWrite(AIN1, 1);
    digitalWrite(AIN2, 1);
    digitalWrite(BIN1, 1);
    digitalWrite(BIN2, 1);
    analogWrite(PWMA, 0);
    analogWrite(PWMB, 0);
  }
  else {
    //LEEMOS LA SEÑAL DE LOS SENSORES
    qtra.read(sensorValues);
    position = qtra.readLine(sensorValues, QTR_EMITTERS_ON, 0);//cambiar 1 por 0 dependiendo la pista, hacer pruebas

    P = ((position) - (Error)); /// ERROR
    /////FRENOS////
    if (P < (-Error + 0.001)) {
      analogWrite(PWMA, frente); // VELOCIDAD PARA EL MOTOR DERECHO
      analogWrite(PWMB, reversa); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
      digitalWrite(AIN1, 1);  ///FRENTE
      digitalWrite(AIN2, 0);
      digitalWrite(BIN1, 0); ///RETROCEDE
      digitalWrite(BIN2, 1);

    } else if (P > (Error - 0.001)) {
      analogWrite(PWMA, reversa); // VELOCIDAD PARA EL MOTOR DERECHO
      analogWrite(PWMB, frente); //  VELOCIDAD PARA EL MOTOR IZQUIERDO
      digitalWrite(AIN1, 0);  ///RETROCEDE
      digitalWrite(AIN2, 1);
      digitalWrite(BIN1, 1); ///FRENTE
      digitalWrite(BIN2, 0);
    }
    /////////////////////////
    else {
      D = (P - LAST); /// ERROR MENOS EL ERROR ANTERIOR , DERIVATIVO
      I = (P + LAST); //INTEGRAL

      vel = (P * Kp) + (D * Kd) + (I * Ki);

      ///VELOCIDAMAX =VELOCIDAD PUNTA , V

      if (vel > VelMax)
      {
        vel = VelMax;
      }
      if (vel < -VelMax)
      {
        vel = -VelMax;
      }

      VelIzq = (VelMax + vel);
      VelDer = (VelMax - vel);

      if (VelIzq > 255)
      {
        VelIzq = 255;
      }
      else if (VelDer > 255)
      {
        VelDer = 255;
      }

      analogWrite(PWMA, VelDer); // VELOCIDAD PARA EL MOTOR DERECHO
      analogWrite(PWMB, VelIzq); //  VELOCIDAD PARA EL MOTOR IZQUIERDO

      digitalWrite(AIN1, HIGH);  ///FRENTE
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH); ///FRENTE
      digitalWrite(BIN2, LOW);

      LAST = P;
    }
  }
}
