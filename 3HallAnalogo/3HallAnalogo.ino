int SENSOR;
int contador = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  SENSOR = analogRead(A0);
  if (SENSOR < 350){
      
      contador = contador+1;
      Serial.println(contador);
  }else{
      Serial.println("0");
    }
  delay(500);

}
