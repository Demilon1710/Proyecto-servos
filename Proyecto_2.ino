#include <Servo.h>          // Incluye la librería Servo

Servo myservoa;
Servo myservob;
Servo myservoc;
Servo myservod;

const int botonMover = 2;
const int botonReposo = 4;
const int ledMover = 6;
const int ledReposo = 7;
bool botona;
bool botonoff;

void moverNangulo(int angulo);

const long intervalc = 500; //Variable para el intervalo que indica cuánto tardará el cambio de estado en milisegundos
unsigned long previousMillis = 0; //Variable para reiniciar el contador de tiempo

void setup() {
  myservoa.attach(3);
  myservob.attach(9);
  myservoc.attach(5);
  myservod.attach(11);

  pinMode(botonMover, INPUT);
  pinMode(botonReposo, INPUT);
  pinMode(ledMover, OUTPUT);
  pinMode(ledReposo, OUTPUT);

  moverNangulo(0);  
}

void loop() {
  botona = digitalRead(botonMover);
  botonoff = digitalRead(botonReposo);
  if (botona == HIGH) {
    moverNangulo(36);
    digitalWrite(ledMover, HIGH);
    digitalWrite(ledReposo, LOW);
  }
  if (botonoff == HIGH) {
    moverNangulo(0);
    digitalWrite(ledReposo, HIGH);
    digitalWrite(ledMover, LOW);
  }
  unsigned long completeMillis = millis();
  if (completeMillis - previousMillis >= intervalc) {
    previousMillis = completeMillis;
}
delay(1);
}

void moverNangulo(int angulo){
  myservoa.write(angulo);
  myservob.write(angulo);
  myservoc.write(angulo);
  myservod.write(angulo);
}
