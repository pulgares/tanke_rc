#include <EnableInterrupt.h>
#include <Servo.h>
Servo direccion;  // create servo object to control a servo
Servo camara1;
Servo camara2; 

int val;
int cam ;
int cam2 ;
int motorIzqAd = 3;
int motorIzqAt = 5;
int motorDerAd = 6;
int  motorDerAt = 9;
int luces = 14;
int aux1 = 22;
int aux2 = 14;
int aux3 = 15;
const int mitad = 1500;//el valor cuando el mando esta a la mitad
long loop_timer, tiempo_ejecucion;

volatile long contPotenciaInit; // LEER MANDO RC --> POTENCIA
volatile int PulsoPotencia;
void INTpotencia() {
  if (digitalRead(7) == HIGH) contPotenciaInit = micros();
  if (digitalRead(7) == LOW)PulsoPotencia = micros() - contPotenciaInit;
}

volatile long canal13; // LEER MANDO RC --> canal5
volatile int Pulsocanal13;
void INTcanal13() {
  if (digitalRead(13) == HIGH) canal13 = micros();
  if (digitalRead(13) == LOW)Pulsocanal13 = micros() - canal13;
}

volatile long contPitchInit; // LEER MANDO RC --> PITCH
volatile int PulsoPitch;
void INTpitch() {
  if (digitalRead(4) == HIGH) contPitchInit = micros();
  if (digitalRead(4) == LOW) PulsoPitch = micros() - contPitchInit;
}
/*
volatile long contcanal7; // LEER MANDO RC --> canal7
volatile int Pulsocanal7;
void INTcanal7() {
  if (digitalRead(5) == HIGH) contcanal7 = micros();
  if (digitalRead(5) == LOW) Pulsocanal7 = micros() - contcanal7;
}
*/
volatile long contRollInit; // LEER MANDO RC --> ROLL
volatile int PulsoRoll;
void INTroll() {
  if (digitalRead(10) == HIGH) contRollInit = micros();
  if (digitalRead(10) == LOW) PulsoRoll = micros() - contRollInit;
}
/*
volatile long contcanal8; // LEER MANDO RC --> canal8
volatile int Pulsocanal8;
void INTcanal8() {
  if (digitalRead(4) == HIGH) contcanal8 = micros();
  if (digitalRead(4) == LOW) Pulsocanal8 = micros() - contcanal8;
}
*/
volatile long contYawInit; // LEER MANDO RC --> YAW
volatile int PulsoYaw;
void INTyaw() {
  if (digitalRead(2) == HIGH) contYawInit = micros();
  if (digitalRead(2) == LOW) PulsoYaw = micros() - contYawInit;
}
/*
volatile long contcanal2; // LEER MANDO RC --> canal9
volatile int Pulsocanal2;
void INTcanal2() {
  if (digitalRead(2) == HIGH) contcanal2 = micros();
  if (digitalRead(2) == LOW) Pulsocanal2 = micros() - contcanal2;
}
*/
void setup() {
  //direccion.attach(3);
  camara1.attach(11);
  camara2.attach(12);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
 // pinMode(9, INPUT_PULLUP);  
  /*
  //canal7
  enableInterrupt(9, INTcanal7, CHANGE);
  pinMode(4, INPUT_PULLUP);                  // canal8
  enableInterrupt(4, INTcanal8, CHANGE);
  pinMode(12, INPUT_PULLUP);                  // canal9
  enableInterrupt(12, INTcanal9, CHANGE);
   */
  pinMode(13, INPUT_PULLUP);                   // canal13
  enableInterrupt(13, INTcanal13, CHANGE);
  pinMode(2, INPUT_PULLUP);                    // YAW
  enableInterrupt(2, INTyaw, CHANGE);
  pinMode(7, INPUT_PULLUP);                    // POTENCIA
  enableInterrupt(7, INTpotencia, CHANGE);
  pinMode(4, INPUT_PULLUP);                    // PITCH
  enableInterrupt(4, INTpitch, CHANGE);
  pinMode(10, INPUT_PULLUP);                   // ROLL
  enableInterrupt(10, INTroll, CHANGE);

  Serial.begin(115200);
  delay(100);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void delante(){
  digitalWrite(motorIzqAd, HIGH);            //
    digitalWrite(motorIzqAt, LOW);             //adelante
    digitalWrite(motorDerAd, HIGH);            //
    digitalWrite( motorDerAt, LOW);             //
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  void atras(){
    digitalWrite(motorIzqAd, LOW);            //
    digitalWrite(motorIzqAt, HIGH);           //
    digitalWrite(motorDerAd, LOW);            //atras  
    digitalWrite( motorDerAt, HIGH);           //
    }
    void derecha(){
      digitalWrite(motorIzqAd, HIGH);            //
    digitalWrite(motorIzqAt, LOW);            //
    digitalWrite(motorDerAd, LOW);            //derecha  
    digitalWrite( motorDerAt, HIGH);           //
      }
  void izquierda(){
    digitalWrite(motorIzqAd, LOW);            //
    digitalWrite(motorIzqAt, HIGH);           //izquierda
    digitalWrite(motorDerAd, HIGH);           //
    digitalWrite( motorDerAt, LOW);            //
    }
 void parado(){
  digitalWrite(motorIzqAd, LOW);            //
    digitalWrite(motorIzqAt, LOW);             //parado
    digitalWrite(motorDerAd, LOW);            //
    digitalWrite( motorDerAt, LOW);             //
  }
void loop() {
  while (micros() - loop_timer < 10000);

  tiempo_ejecucion = (micros() - loop_timer) / 1000;
  loop_timer = micros();


//                                                  servo camara1
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
cam2=PulsoPitch;                        //
cam2 = map(cam2, 1000, 1990, 0, 190);     //
camara2.write(cam2);                     //

//                                                  servo camara2
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
cam=PulsoRoll;                        //
cam = map(cam, 1000, 1990, 0,190);     //
camara1.write(cam);                     //


//                                              luces
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

if (Pulsocanal13  > 1400) {
                 
    digitalWrite(luces, HIGH);
  } else {                             //luces
    digitalWrite(luces, LOW);
        } 
//////////////////////////////////////////////////////////////////////////////////////////////////
/*
    int PulsoPotencia = map(1400, 1000, 1900, 0, 2);           
 switch (PulsoPotencia) {
    case 0:                                     //  1400
     digitalWrite(motorIzqAd, LOW);             //parado
    digitalWrite(motorIzqAt, LOW);
    digitalWrite(motorDerAd, LOW);              //
    digitalWrite( motorDerAt, LOW);             //
      break;
    case 1:                                     // 1900
      digitalWrite(motorIzqAd, HIGH);           //
    digitalWrite(motorIzqAt, LOW);              //adelante
    digitalWrite(motorDerAd, HIGH);             //
    digitalWrite( motorDerAt, LOW);             //
      break;
    case 2:                                     // 1000
      digitalWrite(motorIzqAd, LOW);            //
    digitalWrite(motorIzqAt, HIGH);             //
    digitalWrite(motorDerAd, LOW);              //atras  
    digitalWrite( motorDerAt, HIGH);            //
      break;
    
  }
  */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                                dos motores tipo tanke

 if (PulsoPotencia >= 1700) {                  //
    delante();
  }                                            
  
  /*
  else {                                    //  
    digitalWrite(motorIzqAd, LOW);             //
    digitalWrite(motorIzqAt, LOW);
    digitalWrite(motorDerAd, LOW);            //
    digitalWrite( motorDerAt, LOW);             //
    }            
          
         */             
if (PulsoPotencia  <= 1400) {
    atras();
  } 
  
  /*
  else {                                                         
    digitalWrite(motorIzqAd, LOW);            //
    digitalWrite(motorIzqAt, LOW);            //
    digitalWrite(motorDerAd, LOW);            //
    digitalWrite( motorDerAt, LOW);            //
    }  
    */
                           
    if (PulsoYaw  >1700) {
    derecha();
  } 
  
  /*
  else {                                                       
    digitalWrite(motorIzqAd, LOW);            //
    digitalWrite(motorIzqAt, LOW);            //
    digitalWrite(motorDerAd, LOW);            //
    digitalWrite( motorDerAt, LOW);            //
    }  
       
     */                     
     if (PulsoYaw  < 1400) {
    izquierda();
  }

/*
else 
  
  {                                                      
    digitalWrite(motorIzqAd, LOW);            //
    digitalWrite(motorIzqAt, LOW);            //
    digitalWrite(motorDerAd, LOW);            //
    digitalWrite( motorDerAt, LOW);            //
    }  
      */  
        /*
      if (PulsoYaw  >1400 && PulsoYaw<1700) {
      
        digitalWrite(motorIzqAd, LOW);            //
    digitalWrite(motorIzqAt, LOW);            //
    digitalWrite(motorDerAd, LOW);            //
    digitalWrite( motorDerAt, LOW);            //
    }   
            
            */ 
            /*   
    if (PulsoPotencia  > 1400 && PulsoPotencia < 1700) 
    { 
    parado();
  }   
              */                    
      }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
/*
  Serial.print(Pulsocanal13);
  Serial.print("\t");
  
  Serial.print(PulsoPotencia);
  Serial.print("\t");

  Serial.print(PulsoPitch);
  Serial.print("\t");
 
  Serial.print(PulsoRoll);
  Serial.print("\t");
  
  Serial.println(PulsoYaw);
  Serial.print("\t");
  */
