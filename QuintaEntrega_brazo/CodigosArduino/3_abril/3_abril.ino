// Definir constantes PID
const float kp = 5.2192;
const float ki = 0.028955;
const float kd = 235.188;

// Definir variables PID
float error, last_error, integral, derivative, pid_value;
float setpoint = 0;  // Valor de consigna deseado
float actual_value = 0;  // Valor medido actual

void setup() {
  // Inicializar las variables PID
  error = 0;
  last_error = 0;
  integral = 0;
  derivative = 0;
  pid_value = 0;
  
  // Inicializar los pines de entrada/salida
  pinMode(3, INPUT); // encoder
  pinMode(9, OUTPUT);
  
  // Configurar la comunicación serie
  Serial.begin(9600);
}

void loop() {
  // Leer el valor actual del sensor
  actual_value = analogRead(A0);
  
  // Calcular el error
  error = setpoint - actual_value;
  
  // Calcular la parte proporcional
  float p = kp * error;
  
  // Calcular la parte integral
  integral += ki * error;
  
  // Limitar la parte integral
  if (integral > 255) integral = 255;
  if (integral < -255) integral = -255;
  
  // Calcular la parte derivativa
  derivative = kd * (error - last_error);
  last_error = error;
  
  // Calcular el valor PID
  pid_value = p + integral + derivative;
  
  // Limitar el valor PID
  if (pid_value > 255) pid_value = 255;
  if (pid_value < 0) pid_value = 0;
  
  // Mostrar los valores PID en el monitor serie
  Serial.print("P: ");
  Serial.print(p);
  Serial.print(" I: ");
  Serial.print(integral);
  Serial.print(" D: ");
  Serial.print(derivative);
  Serial.print(" PID: ");
  Serial.println(pid_value);
  
  // Escribir el valor PID en el pin PWM
  analogWrite(9, pid_value);
  
  // Esperar un tiempo antes de volver a iterar
  delay(10);
}
