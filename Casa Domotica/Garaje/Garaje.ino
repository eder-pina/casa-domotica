#include<Servo.h>
Servo myServo;
int TRIG = 8; //PIN TRIG DEL SENSOR DE DISTANCIA
int ECO = 9;  //PIN ECHO DEL SENSOR DE DISTANCIA
int tiempo;   // TIEMPO DE REACCION DEL SENSOR DE DISTANCIA
int distancia; // DISTANCIA DE LECTURA

void setup() {
  pinMode(2, OUTPUT); //PIN DE LED ROJO GARAJE
  pinMode(3,OUTPUT);  // PIN DE LED VERDE DE GARAJE
  pinMode(TRIG,OUTPUT);
  pinMode(ECO,INPUT);
  myServo.attach(5);  // PIN SERVOMOTOR GARAJE
  onOffLeds();
  Serial.begin(9600);
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
}

void leerdistancia(){   //FUNCION PARA LEER DISTANCIA DEL AUTO
  digitalWrite(TRIG,HIGH);
  delay(10000);
  digitalWrite(TRIG,LOW);
  tiempo = pulseIn(ECO,HIGH);
  distancia = tiempo / 58.2;
}

void onOffLeds(){   //FUNCION PARA ENCENDER Y APAGAR LEDS DEL GARAJ||E
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
  int angulo=180;
  do{
    angulo=angulo-1;
    myServo.write(angulo);
    delay(50);
  }while(angulo>0);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
}