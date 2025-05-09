include <Servo.h>          // Incluye la librería Servo

// Pines
const int servo1Pin = 9;
const int servo2Pin = 10;
const int servo3Pin = A0;
const int servo4Pin = A1;

const int btnServo1Inc = 2;
const int btnServo1Dec = 3;
const int btnServo2Inc = 4;
const int btnServo2Dec = 5;

// Variables de estado
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int posServo1 = 90; // Posición inicial (grados)
int posServo2 = 90;


void setup() {
  Serial.begin(9600);

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

  pinMode(btnServo1Inc, INPUT_PULLUP);
  pinMode(btnServo1Dec, INPUT_PULLUP);
  pinMode(btnServo2Inc, INPUT_PULLUP);
  pinMode(btnServo2Dec, INPUT_PULLUP);

 

  // Posición inicial servos
  servo1.write(posServo1);
  servo2.write(posServo2);

  mostrarEstado();

}

void loop() {
  // put your main code here, to run repeatedly:

}