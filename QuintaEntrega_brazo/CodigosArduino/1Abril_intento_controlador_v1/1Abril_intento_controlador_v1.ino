#include <PIDController.hpp>
//**
int POT_sp = 1;
float sp;  //va a medir el tiempo del potenciometro
int PWM_salida = 9;
float pv; //Variable de proceso coentiene la salida de PWM
int pinA = 3;

float cv;
float cv1;
float error, error1, error2;
double Kp = 5.2192;
double Ki = 0.028955;
double Kd = 235.188;
float Tm = 0.001;
//**
int sensorValue = 3; // Entrada del sensor encoder
int pinIN1 = 7; // Pin de control de dirección del motor
int pinIN2 = 8; // Pin de control de dirección del motor
int PWM_salida = 9;


double setPoint = 19.41;
double Kp = 5.2192;
double Ki = 0.028955;
double Kd = 235.188;


double outputValue = PWM_salida;

const int PIN_INPUT = 3;
const int PIN_OUTPUT = 9;

PID::PIDParameters<double> parameters(Kp, Ki, Kd);
PID::PIDController<double> pidController(parameters);

void setup()
{
  pidController.Input = analogRead(PIN_INPUT);
  pidController.Setpoint = setPoint;

  pidController.TurnOn();
}

void loop()
{
  pidController.Input = analogRead(PIN_INPUT);
  pidController.Update();

  analogWrite(PIN_OUTPUT, pidController.Output);
}
