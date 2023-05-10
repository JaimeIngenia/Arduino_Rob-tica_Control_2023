#include <PIDController.hpp>
//**
int POT_sp = 1;
float sp;  //va a medir el tiempo del potenciometro
int PWM_salida = 9;
float pv; //Variable de proceso coentiene la salida de PWM
int pinA = 3;

float cv;
float cv1;
float error, error1, error2;
double kp = 5.2192;
double ki = 0.028955;
double kd = 235.188;
float Tm = 0.001;
//**
int IN1 = 8;
int IN2 = 7;

float  rpm; //Variable de proceso coentiene la salida de PWM
volatile long contadorEncoder = 0;
volatile long contadorSincronoTimmerOne = 0;

unsigned long time_start;

////   Controlador

//double setPoint = 19.41;
double setPoint =7;
double outputValue = PWM_salida;
const int PIN_INPUT = 3;
const int PIN_OUTPUT = 9;
PID::PIDParameters<double> parameters(kp, ki, kd);
PID::PIDController<double> pidController(parameters);
////
void setup() {
  //
  pidController.Input = analogRead(PIN_INPUT);
  pidController.Setpoint = setPoint;
  pidController.TurnOn();
  //
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
    pidController.Input = analogRead(PIN_INPUT);
    pidController.Update();
    analogWrite(PIN_OUTPUT, pidController.Output);
}

ISR(TIMER1_COMPA_vect){    //Interrupción por igualdad de compación
  
  contadorSincronoTimmerOne++;
  //Serial.println(contadorSincronoTimmerOne);
  
//    if (contadorSincronoTimmerOne == 1000) 
//   {
//
//     while(1) { };
//   
//     Serial.print("QUIETO PARAR ADQUISICIÓN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
//   } 
   //else{////////////////////////////////////////////////////////////////////////////////////////////////////
    digitalWrite(IN1, LOW);
    digitalWrite(IN1, HIGH);
    rpm = contadorEncoder*1000*(60.0/(27000.0*6));   // <<<<<<<<<<<<<<<<<<<<<<< ESTE SERÍA pv
    sp = analogRead(POT_sp)*(380.0/1023.0);
    error = sp - rpm;
    cv = cv1 + (kp + kd /Tm) * error + ( - kp + ki*Tm -2*kd/Tm)*error + (kd/Tm)*error2;
    cv1 = cv ;
    error2 = error1;
    error1 = error;
    if(cv>500.0){
      cv = 500.0;
    }
    if (cv<30.0){
      cv = 30.0;
    }
    analogWrite(PWM_salida,cv*(255.0/500.0));

    Serial.print("SP: ");
    Serial.print(sp);
    Serial.print("RPM: ");
    Serial.print(rpm);
    
    
    //Serial.println(rpm);////////////////////////////////////////////////////////////////////////////////////////////////////
    contadorEncoder = 0; 
   //}////////////////////////////////////////////////////////////////////////////////////////////////////
  TCNT1 = 0;      //Reestablecer el valor del temporizador porque si no contará hasta su valor máximo  
  
}

void interrupcion(){
  contadorEncoder++;
  
  }
