#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo;
SoftwareSerial BTSerial(0, 1); // RX, TX (ajusta los pines según tu conexión)
int ledhab1 = 2;
int ledhab2 = 3;
int ledcom = 5;
int ledbano = 6;
int angulo = 0;
char dato;

void setup() {
  pinMode(ledhab1,OUTPUT);
  pinMode(ledhab2,OUTPUT);
  pinMode(ledcom,OUTPUT);
  pinMode(ledbano,OUTPUT);
  servo.attach(4); // Pin donde conectas la señal del servo
  Serial.begin(9600);
  BTSerial.begin(10000); // Velocidad de comunicación Bluetooth
}

void loop() {
  if (BTSerial.available() > 0) {
    dato = BTSerial.read();
    Serial.println(dato); // Imprime el dato recibido para debug
    char comando = Serial.read();
    
    if (dato == 'a') {
      angulo = 180;
    } else if (dato == 'b') {
      angulo = 0;
    } else if (comando == 'c') {
      digitalWrite(ledhab1, HIGH); // Enciende el LED
    } else if (comando == 'd') {
      digitalWrite(ledhab1, LOW);  // Apaga el LED
    }else if (comando == 'e') {
      digitalWrite(ledhab2, HIGH); // Enciende el LED
    } else if (comando == 'f') {
      digitalWrite(ledhab2, LOW);  // Apaga el LED
    }else if (comando == 'g') {
      digitalWrite(ledcom, HIGH); // Enciende el LED
    } else if (comando == 'h') {
      digitalWrite(ledcom, LOW);  // Apaga el LED
    }if (comando == 'i') {
      digitalWrite(ledbano, HIGH); // Enciende el LED
    } else if (comando == 'j') {
      digitalWrite(ledbano, LOW);  // Apaga el LED
    }
    servo.write(angulo);
    delay(15); // Espera un poco antes de procesar el siguiente dato
  }
}
