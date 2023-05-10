int IN1 = 8;
int IN2 = 7;
int PWM_salida = 10;
int pinA = 3;

float  rpm; //Variable de proceso coentiene la salida de PWM
volatile long contadorEncoder = 0;
volatile long contadorSincronoTimmerOne = 0;

unsigned long time_start;

// Variables del control PDI
double Kp = 5.2192;
double Kd = 235.188;
double Ki = 0.028955;

double dt = 0.01;
double error = 0;
double last_error = 0;
double integral_error = 0;
double derivative_error = 0;
double setpoint = 0;
double output = 0;

// Variables del encoder
volatile int encoder_pos = 0;
int encoder_last_pos = 0;
int encoder_delta = 0;

// Función de interrupción del encoder
void encoder_ISR()
{
  encoder_pos += (digitalRead(pinA) == HIGH) ? 1 : -1;
}

void setup() 
{
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

void loop()
{
    setpoint = 19.41; // Cambiar el setpoint según sea necesario
    control();
}

ISR(TIMER1_COMPA_vect){    //Interrupción por igualdad de compación
  
  contadorSincronoTimmerOne++;
  TCCR1B = TCCR1B & B11111000 | B00000011;    // set timer 1 divisor to    64 for PWM frequency of   490.20 Hz (The DEFAULT)
  encoder_pos += (digitalRead(pinA) == HIGH) ? 1 : -1;
//    if (contadorSincronoTimmerOne == 1000) 
//   {
//
//     while(1) { };
//   
//     Serial.print("QUIETO PARAR ADQUISICIÓN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
//   } 
//else{////////////////////////////////////////////////////////////////////////////////////////////////////
//Serial.println(rpm);////////////////////////////////////////////////////////////////////////////////////////////////////
  contadorEncoder = 0; 
//}////////////////////////////////////////////////////////////////////////////////////////////////////
  TCNT1 = 0;      //Reestablecer el valor del temporizador porque si no contará hasta su valor máximo  
  
}

void interrupcion(){
  contadorEncoder++;
  }
  
void control()
{
  error = setpoint - encoder_pos;
  integral_error += error * dt;
  derivative_error = (error - last_error) / dt;
  output = Kp * error + Ki * integral_error + Kd * derivative_error;
  last_error = error;
  
  if (output < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(PWM_salida, -output);
  } else {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWM_salida, output);
  }
  Serial.println(PWM_salida);
}
  
