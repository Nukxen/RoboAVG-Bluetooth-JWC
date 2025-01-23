/*
Aqui é onde fazemos as definições dos pinos e variaveis usadas no codigo
*/
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

void Move(){
  //Move é a função de movimento, ela usa o GamePad que é um obj vindo do Dabble pra realizar testes nas entradas no aplicativo,
  //fazendo com que ao controlar ele remotamente ele saiba qual tecla esta sendo pressionada
  if (GamePad.isUpPressed())
  {
    digitalWrite(MDp,LOW);
    digitalWrite(MEp,LOW);
    digitalWrite(MEn,HIGH);
    digitalWrite(MDn,HIGH);
  }
  else if (GamePad.isDownPressed())
  {
    digitalWrite(MDp,HIGH);
    digitalWrite(MEp,HIGH);
    digitalWrite(MEn,LOW);
    digitalWrite(MDn,LOW);
  }
  else if (GamePad.isLeftPressed())
  {
    digitalWrite(MDp,HIGH);
    digitalWrite(MEp,LOW);
    digitalWrite(MEn,HIGH);
    digitalWrite(MDn,LOW);
  }
  else if (GamePad.isRightPressed())
  {
    digitalWrite(MDp,LOW);
    digitalWrite(MEp,HIGH);
    digitalWrite(MEn,LOW);
    digitalWrite(MDn,HIGH);
  }
  else{
    digitalWrite(MDp,LOW);
    digitalWrite(MEp,LOW);
    digitalWrite(MEn,LOW);
    digitalWrite(MDn,LOW);
  }
}

void echo(){
  //Echo é a função ligada ao HCSR-04, o qual não é utilizada nesse progama!

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

  //Imprime a diancia no serial
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void setup() {
  // Aqui no setup, temos a parte do codigo que será executado uma unica vez, e ela é responsavel por inicializar certos parametros do codigo pra que o progama os acesse conforme a necessidade
  Serial.begin(250000);      
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
  //Loop é a parte do codigo que ficara em execução constante
  Dabble.processInput();
  Move();
}

