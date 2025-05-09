#include <Servo.h> //Incluir la librería servo

Servo myservoa; //Nombrar variable para el servo
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

void setup() {
  myservoa.attach(3);
  myservob.attach(9);
  myservoc.attach(5); //Configurar la señal que llegará al servomotor desde el pin 5
  myservod.attach(11);
  Serial.begin(9600); //Inicial serialización
}

void loop() {
pota = analogRead(potaPin); //El contador cambiará de acuerdo a la lectura del potenciómetro en el pin A3
potb = analogRead(potbPin);
potc = analogRead(potcPin);
potd = analogRead(potdPin);
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
delay(10); //Retraso de 10 ms
}
