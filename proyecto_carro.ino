  #include <Servo.h>
#include <stdio.h>
#include <DS1302.h>
#include <DHT.h>

const int rst   = 7;  
const int dat   = 8;  
const int clk = 2;  

DS1302 rtc(rst, dat, clk);

#define Temp_Update 15
#define In_Servo 90
#define Time_In 333.333
#define DHTPIN A0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

Servo Servo_Motor;
Servo Servo_bombeo;

byte serialA;
int estado = 'f'; 
int posicion_uno = 50; 
int posicion_dos = 150;
int velocidad = 150;

int izqA = 9;
int izqB = 6;
int derA = 11;
int derB = 10;

String dias_semana(const Time::Day day) {
  switch (day) {
    case Time::kSunday: return "Domingo";
    case Time::kMonday: return "Lunes";
    case Time::kTuesday: return "Martes";
    case Time::kWednesday: return "Miercoles";
    case Time::kThursday: return "Jueves";
    case Time::kFriday: return "Viernes";
    case Time::kSaturday: return "Sabado";
  }
  return "(error)";
}

void imprimirdatos() {
  Time t = rtc.time();
  float H = dht.readHumidity();
  float C = dht.readTemperature();
  float f = dht.readTemperature(true);
  String Humedad = String(H);
  String Cel = String(C);
  String Fa = String(f);

  int ano = t.yr; 
  int mes = t.mon;
  int dia = t.date;
  int hora = t.hr;
  int minuto = t.min;
  String a = String(ano);
  String m = String(mes);
  String d = String(dia);
  String h = String(hora);
  String M = String(minuto);

  Serial.print(a);
  Serial.print(',');
  Serial.print(m);
  Serial.print(',');
  Serial.print(d);
  Serial.print(',');
  Serial.print(h);
  Serial.print(',');
  Serial.print(M);
  Serial.print(',');
  Serial.print(Humedad);
  Serial.print(',');
  Serial.print(Cel);
  Serial.print(',');
  Serial.print(Fa);
  Serial.print(',');
  
  
}

int Servo_motor(){
  Servo_Motor.write(60);
  delay(Time_In);
  Servo_Motor.write(140);
  delay(Time_In);
}


void Adelante(){


 digitalWrite(derA,0);
 digitalWrite(derB,velocidad);
 digitalWrite(izqA,velocidad);
 digitalWrite(izqB,0);
}

void RetrocederMa(){
 digitalWrite(derA,velocidad);
 digitalWrite(derB,0);
 digitalWrite(izqA,0);
 digitalWrite(izqB,velocidad);
}

void Retroceder(){
 digitalWrite(derA,velocidad);
 digitalWrite(derB,0);
 digitalWrite(izqA,0);
 digitalWrite(izqB,velocidad);
 delay(4000);
 
 if (random(100)>50)
 {
 digitalWrite(derA,velocidad);
 digitalWrite(derB,0);
 digitalWrite(izqA,velocidad);
 digitalWrite(izqB,0);
  delay(3000);
 }
 else
 {
 digitalWrite(derA,0);
 digitalWrite(derB,velocidad);
 digitalWrite(izqA,0);
 digitalWrite(izqB,velocidad);
 delay(3000);
 }
}

void Frenar(){
 digitalWrite(derA,0);
 digitalWrite(derB,0);
 digitalWrite(izqA,0);
 digitalWrite(izqB,0); 
}

void Derecha(){
 digitalWrite(derA,velocidad);
 digitalWrite(derB,0);
 digitalWrite(izqA,velocidad);
 digitalWrite(izqB,0);
}

void Izquierda(){
 digitalWrite(derA,0);
 digitalWrite(derB,velocidad);
 digitalWrite(izqA,0);
 digitalWrite(izqB,velocidad);
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
  Servo_bombeo.attach(A3);
  Servo_bombeo.write(posicion_uno);
  rtc.writeProtect(false);
  rtc.halt(false);

  Time t(2020, 11, 23, 5, 55, 50, Time::kMonday);
  rtc.time(t);
  delay(Time_In);
  Serial.begin(9600);
  dht.begin();

}


void loop()
{

  long duracion;
  float cm, derecha, izquierda;
  int direccion;
 
    if(Serial.available()>0){      
      estado = Serial.read();
    }
    
    if(estado=='a'){          
      Adelante();       
    }

     if(estado=='i'){           
      Izquierda();      
    }

    if(estado=='f'){         
      Frenar(); 
    }

     if(estado=='d'){         
      Derecha();  
    }
    
    if(estado=='r'){          
      RetrocederMa();    
    }

    if(estado=='z'){
      Servo_bombeo.write(posicion_dos);
      delay(1500);
      Servo_bombeo.write(posicion_uno);
      delay(1500);
      imprimirdatos();
    }


    if (estado == 'k'){
  
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
           delay(500); 
    	} else if(derecha < izquierda){
       		Izquierda();
          delay(500);
    	} else {
      		if (derecha == izquierda && derecha < 30)
        {
           Retroceder();

         }
      	else { 
        	direccion = random (0,10);
        	if (direccion <= 5){
          		Derecha();
              delay(500); 
        	} else {
          		Izquierda();
              delay(500);
        	}
      	}
    	}
  	}

    
    }
}
