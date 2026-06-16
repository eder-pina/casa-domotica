#include<Servo.h>
#include <SoftwareSerial.h>
Servo myServo;
SoftwareSerial BTSerial(0, 1); // RX, TX (ajusta los pines según tu conexión)
int TRIG = 8; //PIN TRIG DEL SENSOR DE DISTANCIA
int ECO = 9;  //PIN ECHO DEL SENSOR DE DISTANCIA
int tiempo;   // TIEMPO DE REACCION DEL SENSOR DE DISTANCIA
int distancia; // DISTANCIA DE LECTURA
int angulo = 0; 
char dato;

void setup() {
  pinMode(2, OUTPUT); //PIN DE LED ROJO GARAJE
  pinMode(3,OUTPUT);  // PIN DE LED VERDE DE GARAJE
  pinMode(TRIG,OUTPUT);
  pinMode(ECO,INPUT);
  myServo.attach(5);  // PIN SERVOMOTOR GARAJE
  onOffLeds();
  Serial.begin(9600);
  myServo.attach(4); // Pin donde conectas la señal del servo
  Serial.begin(9600);
  BTSerial.begin(10000); // Velocidad de comunicación Bluetooth
}

void loop() {
  Serial.println(distancia);
  leerdistancia();
  if(distancia<=10){  //DISTANCIA DEL AUTO PARA ABRIR Y CERRAR GARAJE
    onOffLeds();
    abrirPuerta();
    delay(2000);     //TIEMPO DE APERTURA DE GARAJE
    cerrarPuerta();
    delay(2000);    //TIEMPO DE CERRADURA
  }
  
  if (BTSerial.available() > 0) {
    dato = BTSerial.read();
    Serial.println(dato); // Imprime el dato recibido para debug
    
    if (dato == 'a') {
      angulo = 180;
    } else if (dato == 'b') {
      angulo = 0;
    }
    
    myServo.write(angulo);
    delay(15); // Espera un poco antes de procesar el siguiente dato
  }
}

void leerdistancia(){   //FUNCION PARA LEER DISTANCIA DEL AUTO
  digitalWrite(TRIG,HIGH);
  delay(1000);
  digitalWrite(TRIG,LOW);
  tiempo = pulseIn(ECO,HIGH);
  distancia = tiempo / 58.2;
}

void onOffLeds(){   //FUNCION PARA ENCENDER Y APAGAR LEDS DEL GARAJE
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  delay(100);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  delay(100);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  delay(100);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
}

void abrirPuerta(){  //FUNCION PARA ABRIR PUERTA DE GARAJE
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  int angulo=0;
  do{
    angulo=angulo+1;
    myServo.write(angulo);
    delay(50);
  }while(angulo<90);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
}

void cerrarPuerta() {  //FUNCION PARA CERRAR PUERTA DE GARAJE
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  int angulo=90;
  do{
    angulo=angulo-1;
    myServo.write(angulo);
    delay(50);
  }while(angulo>0);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
}
