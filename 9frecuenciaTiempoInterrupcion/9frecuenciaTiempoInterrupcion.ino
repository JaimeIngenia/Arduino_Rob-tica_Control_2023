
volatile unsigned muestreoActualInterrupcionR = 0;        // variables para definiciòn del tiempo de interrupciòn y calculo de la velocidad motor derecho
volatile unsigned muestreoAnteriorInterrupcionR = 0;
volatile unsigned deltaMuestreoInterrupcionR = 0;

int encoderR = 3;   // pin de conexiòn del encoder derecho

void setup() {
  attachInterrupt(digitalPinToInterrupt(encoderR),REncoder,FALLING);                // linea para añadir una interrupciòn a un PIN
  Serial.begin(9600);                                                               // inicio de la comunicaciòn serial
}

void REncoder() {                                                                                    // funciòn de interrupciòn del enconder llanta derecha
      deltaMuestreoInterrupcionR = muestreoActualInterrupcionR -  muestreoAnteriorInterrupcionR;     // diferencia tiempos de interruciones de ticks del motor     
      muestreoAnteriorInterrupcionR = muestreoActualInterrupcionR;                                   // se actualiza el tiempo de interrupciòn anterior

 } 

void loop() { 
    muestreoActualInterrupcionR = millis();                     // se asigna el tiempo de ejecuciòn a el muestreo actual
    Serial.println(deltaMuestreoInterrupcionR);                 // se muestra el tiempo entre TIC y TIC
}
