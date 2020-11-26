int izqA = 10; 
int izqB = 11; 
int derA = 5; 
int derB = 6; 



void setup()  { 
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);
 } 
 
void loop()  { 
  int v = 100;
    analogWrite(derB, 0);  // frenar
    analogWrite(izqB, 0); 
    analogWrite(izqA, 0);
    analogWrite(derA, 0);
    delay (2000);
  
    analogWrite(5, 0);  // avanzar
    analogWrite(10, v); 
    analogWrite(11, 0);
    analogWrite(6, v);
    delay (2000);
  
  
    analogWrite(6, 0);  // Reversa 
    analogWrite(11, v); 	
    analogWrite(5, v);
    analogWrite(10, 0);
    delay (2000);     
  
    analogWrite(10, v);  // Derecha 
    analogWrite(5, v);
    analogWrite(11, 0);
    analogWrite(6, 0); 
    delay (2000);
  
    analogWrite(11, v);    // Izquierda 
    analogWrite(10, 0); 
    analogWrite(6, v);
  	analogWrite(5, 0);
    delay (5000);
}