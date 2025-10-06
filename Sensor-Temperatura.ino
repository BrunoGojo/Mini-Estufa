#include <Servo.h>

Servo servo;
Servo servo1;

int buzzer = 3;

void setup() {
  Serial.begin(9600);
  servo.attach(8);
  servo1.attach(7);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(buzzer, OUTPUT); // <<< adicionando buzzer

  digitalWrite(6, HIGH);
}

void loop() {
  LDR(); 
  UMI();
  TMP36();
}

void LDR(){
  int leitura = analogRead(A0);
  if (leitura >= 250) {
    servo.write(180);
    tone(buzzer, 1000, 300); // som curto
  } else {
    servo.write(0);
  }
  Serial.print("A leitura analogica do ldr e de: ");
  Serial.println(analogRead(A0));
  delay(1000);
}

void UMI(){
  float umidade = analogRead(A1);
  umidade = map(umidade, 0, 1023, 0, 100);
  
  if (umidade < 40){
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    tone(buzzer, 500, 400); // aviso solo seco
  } else if (umidade > 80){
    digitalWrite(9, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    noTone(buzzer); // solo muito úmido, sem som
  } else {
    digitalWrite(9, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
  }

  if (umidade < 30) {
    servo1.write(180);
  } else if (umidade > 80) {
    servo1.write(90);
    delay(2000);
  } else {
    servo1.write(180);
  }

  Serial.print("O solo esta ");
  Serial.print(umidade);
  Serial.println("% umido");
  delay(1000);
}

void TMP36(){
  float temperatura = analogRead(A2);
  temperatura = map(temperatura, 20, 358, -40, 125);
  
  if (temperatura < 13) {
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(12, LOW);
  }

  if (temperatura > 26) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    tone(buzzer, 1500, 500); // alerta de temperatura alta
  } else {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }

  Serial.print("Leitura do TMP36: ");
  Serial.println(analogRead(A2));
  Serial.print("Temperatura atual: ");
  Serial.print(temperatura);
  Serial.println(" °C");
  Serial.println("");
  delay(1000);
}
