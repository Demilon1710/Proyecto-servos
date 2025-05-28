#include <Servo.h> //Incluir la librería servo

Servo myservoa; //Nombrar variable para el servo
Servo myservob;
Servo myservoc;
Servo myservod;
int potaPin = A0; //Pin analógico al que se conecta el potenciómetro
int potbPin = A1;
int potcPin = A3;
int potdPin = A5; 
int pota = 0; //Valores iniciales del contador de cada potenciómetro
int potb = 0;
int potc = 0;
int potd = 0; 
const int botonA = 12; //Pin digital para los botones
const int botonB = 10;
const int palanca = 6; //Pin digital para el interruptor
const int ledA = 8; //Pin digital para ambos leds
const int ledB = 7;
bool adelante; //Declaración de variables booleanas para los botones
bool atras;
bool estado;
int current = 0; //Contador para el cambio de estados
int next = 0;

void moverNangulo(int angulo); //Declaración de funciones propias
void numerosPot();

const long intervalc = 500; //Variable para el intervalo que indica cuánto tardará el cambio de estado en milisegundos
unsigned long previousMillis = 0; //Variable para reiniciar el contador de tiempo

void setup() {
  myservoa.attach(3); //Configurar la señal que llegará al servomotor desde el pin seleccionado
  myservob.attach(9);
  myservoc.attach(5); 
  myservod.attach(11);

  pinMode(botonA, INPUT); //Configuración de los botones y el interruptor como entradas pulldown
  pinMode(botonB, INPUT);
  pinMode(palanca, INPUT);
  pinMode(ledA, OUTPUT); //Configuración de los leds como salidas
  pinMode(ledB, OUTPUT);

  moverNangulo (0,0,0,0); //Estado inicial de la función propia.

  Serial.begin(9600); //Inicial serialización
}

void loop() {
estado = digitalRead(palanca); //Lectura de la señal proveniente del interruptor
//If que indica lo que sucederá cuando el interruptor esté en la posición que se conectó para que se considere en valor de 1.
if (estado == HIGH){
digitalWrite(ledA, HIGH); 
digitalWrite(ledB, LOW);
adelante = digitalRead(botonA); //Declaración de variables para la lectura de los botones
atras = digitalRead(botonB);
escribePosicion(); //Función para nombrar la posición actual
  //Instrucción para realizar diferentes acciones de acuerdo al estado actual.
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
      moverNangulo(0, 160, 45, 90); //Función original para mover los servos en una posición específica
    break;
    //Señales enviadas durante el estado 1
    case 1:
      moverNangulo(36, 170, 60, 110);
    break;
    //Señales enviadas durante el estado 2
    case 2:
      moverNangulo(72, 180, 50, 100);
    break;
    //Señales enviadas durante el estado 3
    case 3:
      moverNangulo(108, 160, 45, 30);
    break;
    case 4:
      moverNangulo(144, 180, 90, 90);
    break;
    case 5:
      moverNangulo(180, 180, 45, 30);
    break;
}
  unsigned long completeMillis = millis(); //Instrucción millis para indicar el tiempo que se tardan en actuar los botones
  if (completeMillis - previousMillis >= intervalc) {
    current = next;
    previousMillis = completeMillis;
  }
}
//If con las instrucciones cuando el interruptor esté en estado 0.
if (estado == LOW){
  digitalWrite(ledA, LOW); //Indicar el estado de salida que se busca para los leds
  digitalWrite(ledB, HIGH);
  pota = analogRead(potaPin); //El contador cambiará de acuerdo a la lectura del potenciómetro en el pin A3
  potb = analogRead(potbPin);
  potc = analogRead(potcPin);
  potd = analogRead(potdPin);
  int potenciasa = map(pota, 0, 1023, 0, 180); //Mapeo desde 0 a 1024 para 0 a 180
  int potenciasb = map(potb, 0, 1023, 0, 180);
  int potenciasc = map(potc, 0, 1023, 0, 180);
  int potenciasd = map(potd, 0, 1023, 0, 180);
  numerosPot();
  myservoa.write(potenciasa); //Desde el pin del servo, se mandará el valor mapeado del potenciómetro
  myservob.write(potenciasb);
  myservoc.write(potenciasc);
  myservod.write(potenciasd);
}
delay(1);
}
//Contenido de las funciones originales
void moverNangulo(int anguloa, int angulob, int anguloc, int angulod){
  myservoa.write(anguloa);
  myservob.write(angulob);
  myservoc.write(anguloc);
  myservod.write(angulod);
}

void numerosPot(){
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
}

void escribePosicion(){
  Serial.println(next);
  Serial.println(current);
}
