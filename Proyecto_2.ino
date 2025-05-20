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
const int botonC = 8;
const int botonD = 7;
const int botonE = 4;
const int botonF = 2;
const int palanca = 1;
bool cero;
bool treintaiseis;
bool setentaidos;
bool cientoocho;
bool cientocuarentaicuatro;
bool cientoochenta;
bool estado;
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
  pinMode(botonC, INPUT);
  pinMode(botonD, INPUT);
  pinMode(botonE, INPUT);
  pinMode(botonF, INPUT);
  pinMode(palanca, INPUT);

  moverNangulo(0);  

  Serial.begin(9600); //Inicial serialización
}

void loop() {
while(estado == HIGH){
cero = digitalRead(botonA);
treintaiseis = digitalRead(botonB);
setentaidos = digitalRead(botonC);
cientoocho = digitalRead(botonD);
cientocuarentaicuatro = digitalRead(botonE);
cientoochenta = digitalRead(botonF);
estado = digitalRead(palanca);
  if (cero == HIGH) {
    moverNangulo(0);
  }
  if (treintaiseis == HIGH) {
    moverNangulo(36);
  }
  if (setentaidos == HIGH){
    moverNangulo(72);
  }
  if (cientoocho == HIGH){
    moverNangulo(108);
  }
  if (cientocuarentaicuatro == HIGH){
  moverNangulo(144);
  }
  if (cientoochenta == HIGH){
  moverNangulo(180);
  }
  unsigned long completeMillis = millis();
  if (completeMillis - previousMillis >= intervalc) {
    previousMillis = completeMillis;
  }
}
while(estado == LOW){
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
