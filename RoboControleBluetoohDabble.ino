//Modulo Bluetooth - Arduino 14 está funcionando

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define echoPin 0
#define trigPin 1
#define MDn 4
#define MDp 5
#define MEp 6
#define MEn 7
long duration;
int distance;
#include <Dabble.h>

int speed = 100,PWMspeed;

void setup() {
  Serial.begin(250000);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600);
  pinMode(MDn,OUTPUT);
  pinMode(MDp,OUTPUT);
  pinMode(MEp,OUTPUT);
  pinMode(MEn,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  PWMspeed = map(speed,0,100,0,1023);
}

void loop() {
  Dabble.processInput();
  Move();
}

void Move(){
 
  if (GamePad.isUpPressed())
  {
    digitalWrite(MDp,LOW);
    digitalWrite(MEp,LOW);
    digitalWrite(MEn,HIGH);
    digitalWrite(MDn,HIGH);
    echo();
  }
  else if (GamePad.isDownPressed())
  {
    digitalWrite(MDp,HIGH);
    digitalWrite(MEp,HIGH);
    digitalWrite(MEn,LOW);
    digitalWrite(MDn,LOW);
    echo();
  }
  else if (GamePad.isLeftPressed())
  {
    digitalWrite(MDp,HIGH);
    digitalWrite(MEp,LOW);
    digitalWrite(MEn,HIGH);
    digitalWrite(MDn,LOW);
    echo();
  }
  else if (GamePad.isRightPressed())
  {
    digitalWrite(MDp,LOW);
    digitalWrite(MEp,HIGH);
    digitalWrite(MEn,LOW);
    digitalWrite(MDn,HIGH);
    echo();
  }
  else{
    digitalWrite(MDp,LOW);
    digitalWrite(MEp,LOW);
    digitalWrite(MEn,LOW);
    digitalWrite(MDn,LOW);
    echo();
  }
}

void echo(){
  //Emitir pulso 10us no trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Mede o tempo de duração do pulso de eco
  duration = pulseIn(echoPin, HIGH);
 
  // Calcula a distância em centímetros
  distance = duration * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance < 15){
    digitalWrite(MDp,LOW);
    digitalWrite(MEp,LOW);
    digitalWrite(MEn,LOW);
    digitalWrite(MDn,LOW);
  }
}