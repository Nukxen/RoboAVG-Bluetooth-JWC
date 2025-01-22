/*
Aqui é onde fazemos as definições dos pinos e variaveis usadas no codigo
*/
#define echoPin 0
#define trigPin 1
#define MDn 4
#define MDp 5
#define MEp 6
#define MEn 7
int speed = 100,PWMspeed,repeat,dist;

void Move(char m){
  //Move é a função de movimento, ela usa o GamePad que é um obj vindo do Dabble pra realizar testes nas entradas no aplicativo,
  //fazendo com que ao controlar ele remotamente ele saiba qual tecla esta sendo pressionada
  if (m=="F" || m=="f")
  {
    digitalWrite(MDp,LOW);
    digitalWrite(MEp,LOW);
    digitalWrite(MEn,HIGH);
    digitalWrite(MDn,HIGH);
  }
  else if (m=="T" || m=="t")
  {
    digitalWrite(MDp,HIGH);
    digitalWrite(MEp,HIGH);
    digitalWrite(MEn,LOW);
    digitalWrite(MDn,LOW);
  }
  else if (m=="L" || m=="l")
  {
    digitalWrite(MDp,HIGH);
    digitalWrite(MEp,LOW);
    digitalWrite(MEn,HIGH);
    digitalWrite(MDn,LOW);
  }
  else if (m=="R" || m=="r")
  {
    digitalWrite(MDp,LOW);
    digitalWrite(MEp,HIGH);
    digitalWrite(MEn,LOW);
    digitalWrite(MDn,HIGH);
  }
  else if (m=="P" || m=="p"){
    digitalWrite(MDp,LOW);
    digitalWrite(MEp,LOW);
    digitalWrite(MEn,LOW);
    digitalWrite(MDn,LOW);
  }
}
int echo(){
  //Echo é a função ligada ao HCSR-04, o qual não é utilizada nesse progama!

  //Define variaveis locais
  long duration;
  int distance;

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

  return distance;
}

void setup() {
  // Aqui no setup, temos a parte do codigo que será executado uma unica vez, e ela é responsavel por inicializar certos parametros do codigo pra que o progama os acesse conforme a necessidade
  Serial.begin(250000);
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
  dist = echo();
  if(dist>=15){
    Move('F');
    delay(1*1000);
  }
  else if(dist<=5){
    Move('P');
    delay(500);
    Move('F');
    delay(1000);
  }
  else{
    Move('R');
    delay(100);
  }
}