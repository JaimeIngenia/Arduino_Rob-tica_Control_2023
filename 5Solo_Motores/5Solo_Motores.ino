int IN1 = 8;
int IN2 = 7;
int PWM_salida = 9;

void setup() {
  pinMode( IN1, OUTPUT );
  pinMode( IN2, OUTPUT );
  //pinMode(PWM_salida, OUTPUT);

}

void loop() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN1, LOW);
  //analogWrite(PWM_salida,219);
  

}
