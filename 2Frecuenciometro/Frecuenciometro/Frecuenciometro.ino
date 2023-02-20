#include <TimerOne.h>

//***************************
// Configuración de pines
//***************************

const int pulsos = 3;

//*****************************
// Definición de variables
//*****************************
volatile int ISRCounter = 0;
int   counter = 0;
int frec = 0;

void setup(void)
   {  
       pinMode(pulsos, INPUT_PULLUP);
       attachInterrupt(digitalPinToInterrupt(pulsos), interruptCount, RISING);
       Timer1.initialize(100000);         // Dispara cada 100 ms
       Timer1.attachInterrupt(ISR_Blink); // Activa la interrupcion y la asocia a ISR_Blink
       Serial.begin(9600);
   }

   void loop()
    {
     frec = counter;  
     Serial.print("Frecuencia   = ");  
     Serial.println(counter);
     delay(300);
    }
//**********************************************
// Función de interrupción Millis cada 100ms
//**********************************************
   void ISR_Blink()
    {   
      counter = ISRCounter*10;  
      ISRCounter=0;
     }

//***********************************************************
// Función de interrupción por cambio en el pin 2
//************************************************************
  void interruptCount()
   {
      counter++;
   }
