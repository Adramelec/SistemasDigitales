#include <Servo.h>
#define Temp_Update 15
#define In_Servo 90
#define Time_In 333.333

Servo Servo_Motor;


int posicion_uno = 100; 
int posicion_dos = 50;
int velocidad = 150;

int izqA = 9;
int izqB = 6;
int derA = 11;
int derB = 10;

int Servo_motor(){
  Servo_Motor.write(60);
  delay(Time_In);
  Servo_Motor.write(140);
  delay(Time_In);
}




void Adelante(){
 digitalWrite(derA,velocidad);
 digitalWrite(derB,0);
 digitalWrite(izqA,0);
 digitalWrite(izqB,velocidad);
}

void Retroceder(){
 digitalWrite(derA,0);
 digitalWrite(derB,velocidad);
 digitalWrite(izqA,velocidad);
 digitalWrite(izqB,0);
 delay(4000);
}

void Frenar(){
 digitalWrite(derA,0);
 digitalWrite(derB,0);
 digitalWrite(izqA,0);
 digitalWrite(izqB,0); 
}

void Izquierda(){
 digitalWrite(derA,velocidad);
 digitalWrite(derB,0);
 digitalWrite(izqA,velocidad);
 digitalWrite(izqB,0);

 delay(500);
}

void Derecha(){
 digitalWrite(derA,0);
 digitalWrite(derB,velocidad);
 digitalWrite(izqA,0);
 digitalWrite(izqB,velocidad);
 
 delay(500); 
}

float Servo_derecha(){
  Servo_Motor.write(170);
  delay(500);
  pinMode(5, OUTPUT);         
  digitalWrite(5, LOW);       
  delayMicroseconds(2);               
  digitalWrite(5, HIGH);      
  delayMicroseconds(10);            
  pinMode(5, INPUT);          
  Servo_Motor.write(In_Servo);
  return microsecondsToCentimeters(pulseIn(4, HIGH));
}

float Servo_izquierda(){
  Servo_Motor.write(100);
  delay(500);
  pinMode(5, OUTPUT);         
  digitalWrite(5, LOW);       
  delayMicroseconds(2);               
  digitalWrite(5, HIGH);      
  delayMicroseconds(10);            
  pinMode(5, INPUT);          
  Servo_Motor.write(In_Servo);
  return microsecondsToCentimeters(pulseIn(4, HIGH));
}

float microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void setup()
{
  /*motor-reductores*/
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  
  Servo_Motor.attach(3);
  Servo_Motor.write(In_Servo);

  delay(Time_In);
  
  Serial.begin(9600);
 
  
  
}

void loop()
{
  
  long duracion;
  float cm, derecha, izquierda;
  int direccion;
  
  
  	pinMode(5, OUTPUT);  
  	digitalWrite(5, LOW);
  	delayMicroseconds(2);
  	digitalWrite(5, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(5, LOW);
  	pinMode(4, INPUT);
  	duracion= pulseIn(4, HIGH);
  
  	cm= microsecondsToCentimeters(duracion);
  
  		if(cm>30){
    		Adelante();
    		Servo_motor();
    
  		} else {
    		Frenar();
    		Servo_Motor.write(In_Servo);
  			delay(Time_In);
    		delay(500);
    		Servo_derecha();
    		derecha = Servo_derecha();
    		delay(10);
    		Servo_izquierda();
    		izquierda = Servo_izquierda();
    		delay(500);
  
    	if (derecha > izquierda)
     	{
       		Derecha();
    	} else if(derecha < izquierda){
       		Izquierda();
    	} else {
      		if (derecha == izquierda && derecha < 30)
        {
           Retroceder();

         }
      	else { 
        	direccion = random (0,10);
        	if (direccion <= 5){
          		Derecha();
        	} else {
          		Izquierda();
        	}
      	}
    	}
  	} 
    
  
}