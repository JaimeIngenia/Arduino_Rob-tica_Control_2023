int pinA = 3;
volatile int contador = 0;


void setup() {
  pinMode(pinA,INPUT_PULLUP);
  Serial.begin(115200);
  attachInterrupt(1,interrupcion, RISING);  // Flancos de subida

}

void loop() {
  Serial.print("pulsos: ");
  Serial.println(contador);

}

void interrupcion(){
  contador++;
  }
