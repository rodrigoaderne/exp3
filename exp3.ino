int pinoPotenciometro = A0;
int pinoMotor = 4;
int pinoVelocidade = 3;
 
void setup(){
    pinMode(pinoPotenciometro, INPUT);
    pinMode(pinoMotor, OUTPUT);
    pinMode(pinoVelocidade, OUTPUT);
 
    digitalWrite(pinoMotor, HIGH);
}
 
void loop(){
    float valorPotenciometro = (float)(analogRead(pinoPotenciometro) * 5) / 1024;
    float valorPWM = (valorPotenciometro * 255) / 5;
    analogWrite(pinoVelocidade, valorPWM);
}
