
int pinoMotor = 3; //pino 3 ~PWM para controlar velocidade do motor
int valorPWM = 0; 
void setup(){
    pinMode(pinoMotor, OUTPUT); 
}
 
void loop(){
    valorPWM = 255;
    analogWrite(pinoMotor, valorPWM);
}
