#include <PID_v1.h>

// Definir los pines de entrada y salida del motor
int pinEntrada = 3; // Entrada del sensor encoder
int pinIN1 = 7; // Pin de control de dirección del motor
int pinIN2 = 8; // Pin de control de dirección del motor

// Definir las constantes del controlador PID
double Kp = 1.0;
double Ki = 0.5;
double Kd = 0.1;

// Crear el objeto PID
PID myPID(&sensorValue, &outputValue, &setPoint, Kp, Ki, Kd, DIRECT);

// Definir la variable para almacenar la lectura del sensor
double sensorValue = 0;

// Definir la variable para almacenar el valor de salida del controlador
double outputValue = 0;

// Definir la variable para almacenar el valor de consigna del controlador
double setPoint = 50;

// Definir el tiempo de muestreo
unsigned long tiempoAnterior = 0;
unsigned long tiempoActual = 0;
double tiempoMuestreo = 0.001; // en segundos

void setup() {
  // Inicializar el puerto serie
  Serial.begin(9600);

  // Configurar los pines de entrada y salida
  pinMode(pinEntrada, INPUT);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);

  // Inicializar el objeto PID
  myPID.SetMode(AUTOMATIC);
}

void loop() {
  // Obtener la lectura del sensor
  sensorValue = pulseIn(pinEntrada, HIGH);

  // Obtener el tiempo actual
  tiempoActual = millis();

  // Calcular el tiempo transcurrido desde la última iteración
  double tiempoTranscurrido = (double)(tiempoActual - tiempoAnterior) / 1000.0;

  // Verificar si ha pasado el tiempo de muestreo
  if (tiempoTranscurrido >= tiempoMuestreo) {
    // Actualizar el tiempo anterior
    tiempoAnterior = tiempoActual;

    // Calcular el valor de salida del controlador
    myPID.Compute();

    // Ajustar el valor de la salida en los pines de control del motor
    if (outputValue > 0) {
      digitalWrite(pinIN1, HIGH);
      digitalWrite(pinIN2, LOW);
    } else {
      digitalWrite(pinIN1, LOW);
      digitalWrite(pinIN2, HIGH);
    }

    // Imprimir los valores para depuración
    Serial.print(sensorValue);
    Serial.print("\t");
    Serial.print(outputValue);
    Serial.print("\t");
    Serial.println(setPoint);
  }
}
