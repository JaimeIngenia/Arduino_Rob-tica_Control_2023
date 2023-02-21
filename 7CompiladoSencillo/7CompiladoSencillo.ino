
int POT_sp = 1;
float sp;  //va a medir el tiempo del potenciometro
int PWM_salida = 9;
float pv; //Variable de proceso coentiene la salida de PWM

int pinB = 2;//////////////////////////////////////////////////
int pinA = 3;
volatile int contadorB = 0;////////////////////////

volatile int contador = 0;
unsigned long previousMillis = 0;
long interval = 10;


void setup() {
  pinMode(pinA, INPUT);
  pinMode(PWM_salida, OUTPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(pinA), interrupcion,RISING);
  attachInterrupt(digitalPinToInterrupt(pinB), interrupcionB,RISING);/////////////////////
  }

void loop() {
    unsigned long currentMillis = millis();
    if ((currentMillis - previousMillis >= interval)){
        previousMillis = currentMillis;
        pv = contador*100*(60.0/27000.0); //RPM en eje de salida
                
        contador = 0;
        contadorB = 0;///////////////////////////
      }
          
     sp = analogRead(POT_sp) * (100.0/1023.0);
     analogWrite(PWM_salida, sp*(255.0/100.0));

     Serial.print(" SP: ");
     Serial.print(sp);
     Serial.print(", Revoluciones: ");
     Serial.println(pv);
  }


void interrupcion(){
  contador++;
  }

void interrupcionB(){
  contadorB++;
  }
