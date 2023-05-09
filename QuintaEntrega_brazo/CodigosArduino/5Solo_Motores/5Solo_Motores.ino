int IN1 = 8;
int IN2 = 7;
int PWM_salida = 9;

void setup() {
  pinMode( IN1, OUTPUT );
  pinMode( IN2, OUTPUT );
  //pinMode( PWM_salida, OUTPUT );
  

}

void loop() {
  delay(5000);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(5000);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(5000);
  
  //analogWrite(PWM_salida,5);
  

}
