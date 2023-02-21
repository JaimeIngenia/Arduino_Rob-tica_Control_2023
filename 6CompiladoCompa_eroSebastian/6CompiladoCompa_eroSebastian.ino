volatile unsigned muestraActual = 0;
volatile unsigned muestraAnterior = 0;
volatile unsigned deltaMuestreo = 0;
int k = 10;
int IN1 = 8;
int IN2 = 7;
 

// Variables para almacenar el estado del encoder
volatile int encoderPos = 0;
volatile int lastEncoderPos = 0;





int POT_sp = 1;
float sp;
int PWM_salida = 9; 
float pv;

const int pinA = 3;
volatile int contador = 0;
unsigned long previousMillis = 0;
long interval = 2;


void setup() {
  // Configurar los pines del encoder como entradas y activar las resistencias de pull-up
  pinMode(pinA, INPUT);
  pinMode( PWM_salida, OUTPUT );
  Serial.begin(115200);
  attachInterrupt(1, interrupcion,RISING);
  
  //motores
  pinMode( IN1, OUTPUT );
  pinMode( IN2, OUTPUT );
}

void loop() {
  muestraActual = millis();
  deltaMuestreo = (double) muestraActual - muestraAnterior;
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //analogWrite(PWM_salida,119);

  if( deltaMuestreo >= k){
    
    muestraAnterior = muestraActual;
    pv = 100*contador*(60.0/27000.0); // RPM del eje
    contador = 0;
  }

  sp = analogRead(POT_sp)*(100.0/1023.0);
  analogWrite(PWM_salida, sp*(255.0/100.0));

  Serial.print(" SP: ");
  Serial.print(sp);
  Serial.print(", PV: ");
  Serial.println(pv);
}


void interrupcion(){
  contador++;
  }
