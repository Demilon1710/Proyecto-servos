#include <Servo.h>          // Incluye la librería Servo

Servo myservoa;
Servo myservob;
Servo myservoc;
Servo myservod;
int potaPin = A0; //Pin al que se conecta el potenciómetro
int potbPin = A1;
int potcPin = A3;
int potdPin = A5; 
int pota = 0;
int potb = 0;
int potc = 0;
int potd = 0; //Contador del valor en el potenciómetro
const int botonA = 12;
const int botonB = 10;
const int palanca = 6;
bool adelante;
bool atras;
bool estado;
int current = 0;
int next = 0;

void moverNangulo(int angulo);

const long intervalc = 500; //Variable para el intervalo que indica cuánto tardará el cambio de estado en milisegundos
unsigned long previousMillis = 0; //Variable para reiniciar el contador de tiempo

void setup() {
  myservoa.attach(3);
  myservob.attach(9);
  myservoc.attach(5);
  myservod.attach(11);

  pinMode(botonA, INPUT);
  pinMode(botonB, INPUT);
  pinMode(palanca, INPUT);

  moverNangulo(0);  

  Serial.begin(9600); //Inicial serialización
}

void loop() {
estado = digitalRead(palanca);
if(estado == HIGH){
adelante = digitalRead(botonA);
atras = digitalRead(botonB);
Serial.println(next);
Serial.println(current);
  switch(current){
    //Condiciones de cambio desde el estado 0
    case 0:
    if (adelante == HIGH)
      next = 1;
    else
      next = 0;
    break;
    //Condiciones de cambio desde el estado 1
    case 1:
    if (adelante == HIGH)
      next = 2;
    else 
    if (atras == HIGH)
      next = 0;
    else
      next = 1;
    break;
    //Condiciones de cambio desde el estado 2
    case 2:
    if (adelante == HIGH)
      next = 3;
    else
    if (atras == HIGH)
      next = 1;
    else
      next = 2;
    break;
    //Condiciones de cambio desde el estado 3
    case 3:
    if (adelante == HIGH)
      next = 4;
    else
    if (atras == HIGH)
      next = 2;
    else
      next = 3;
    break;
    case 4:
    if (adelante == HIGH)
      next = 5;
    else
    if (atras == HIGH)
      next = 3;
    else
      next = 4;
    break;
    case 5:
    if (atras == HIGH)
      next = 4;
    else
      next = 5;
    break;
  }
  //Bloque para indicar las acciones que el sistema toma en cada estado
  switch(current){
    //Señales enviadas durante el estado 0
    case 0:
      moverNangulo(0);
    break;
    //Señales enviadas durante el estado 1
    case 1:
      moverNangulo(36);
    break;
    //Señales enviadas durante el estado 2
    case 2:
      moverNangulo(72);
    break;
    //Señales enviadas durante el estado 3
    case 3:
      moverNangulo(108);
    break;
    case 4:
      moverNangulo(144);
    break;
    case 5:
      moverNangulo(180);
    break;
}
  unsigned long completeMillis = millis();
  if (completeMillis - previousMillis >= intervalc) {
    current = next;
    previousMillis = completeMillis;
  }
}
if(estado == LOW){
  pota = analogRead(potaPin); //El contador cambiará de acuerdo a la lectura del potenciómetro en el pin A3
  potb = analogRead(potbPin);
  potc = analogRead(potcPin);
  potd = analogRead(potdPin);
  estado = digitalRead(palanca);
  int potenciasa = map(pota, 0, 1023, 0, 180); //Mapeo desde 0 a 1024 para 0 a 180
  int potenciasb = map(potb, 0, 1023, 0, 180);
  int potenciasc = map(potc, 0, 1023, 0, 180);
  int potenciasd = map(potd, 0, 1023, 0, 180);
  Serial.println("Potenciómetro A: ");
  Serial.println(potenciasa); //Escribir el valor actual del potenciómetro mapeado
  Serial.println("Potenciómetro B: ");
  Serial.println(potenciasb);
  Serial.println("Potenciómetro C: ");
  Serial.println(potenciasc);
  Serial.println("Potenciómetro D: ");
  Serial.println(potenciasd);
  myservoa.write(potenciasa); //Desde el pin del servo, se mandará el valor mapeado del potenciómetro
  myservob.write(potenciasb);
  myservoc.write(potenciasc);
  myservod.write(potenciasd);
}
delay(1);
}

void moverNangulo(int angulo){
  myservoa.write(angulo);
  myservob.write(angulo);
  myservoc.write(angulo);
  myservod.write(angulo);
}
