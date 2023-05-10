int IN1 = 8;
int IN2 = 7;
int PWM_salida = 10;

void setup() {
  pinMode( IN1, OUTPUT );
  pinMode( IN2, OUTPUT );
  pinMode( PWM_salida, OUTPUT );
  

}

void loop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(PWM_salida, 180);
  
}
