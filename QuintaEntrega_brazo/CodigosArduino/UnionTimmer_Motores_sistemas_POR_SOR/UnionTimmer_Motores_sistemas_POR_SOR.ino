int IN1 = 8;
int IN2 = 7;
int PWM_salida = 9;

float  rpm; //Variable de proceso coentiene la salida de PWM
int pinA = 3;
volatile long contadorEncoder = 0;
volatile long contadorSincronoTimmerOne = 0;

unsigned long time_start;

void setup() {
  pinMode( IN1, OUTPUT );
  pinMode( IN2, OUTPUT );
  pinMode(pinA, INPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(pinA), interrupcion,RISING);
  cli();                   //Desabilito las interrupciones
  TCCR1A = 0;              //El registro de control A queda todo en 0
  TCCR1B = 0;              //Limpia registrador
  TCCR1B |= B00000101;   //MODO CTC, prescaler //TCCR1B |= B00000100; //TCCR1B |= ( 1 << cs10 ) | ( 1 << cs12 ); 
  TCNT1   = 0;              //Inicializa el temporizador
  OCR1A  =  15.63;        //Carga el registrador de comparación: [ 16MHz / (Pre-escalador * FrecuenciaInterrupcionDeseada)] - 1   o dividir los pulsos del cristal entre la frecuencia deseada
  TIMSK1 |= ( 1 << OCIE1A); //Habilita interrupción por igualdad de comparacion // TIMSK1 |= B00000010;
  sei(); //Habilito las interrupciones
}

void loop() {

}

ISR(TIMER1_COMPA_vect){    //Interrupción por igualdad de compación
  
  contadorSincronoTimmerOne++;
  //Serial.println(contadorSincronoTimmerOne);
  
    if (contadorSincronoTimmerOne == 1000) 
   {

     while(1) { };
   
     Serial.print("QUIETO PARAR ADQUISICIÓN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
   } 
   else{
    digitalWrite(IN1, LOW);
    digitalWrite(IN1, HIGH);
    rpm = contadorEncoder*1000*(60.0/(27000.0*6));
    Serial.println(rpm);
    contadorEncoder = 0; 
   }
  TCNT1 = 0;      //Reestablecer el valor del temporizador porque si no contará hasta su valor máximo  
  
}

void interrupcion(){
  contadorEncoder++;
  
  }
