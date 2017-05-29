int pinoMotor = 3;
int valorPWM = 0;
//VARIAVEIS PARA BOTAO

int verm_carro = 8;   //PIN DIGITAL 8
int button = 2; // PIN DIGITAL 2
int IR_COUNT = 0;

void interrupcao(){ 
   IR_COUNT++; //FLAG PARA INICIAR CONTADOR.
   digitalWrite(verm_carro, HIGH);
  } 

void setup(){
  pinMode(verm_carro, OUTPUT);
  
  pinMode(pinoMotor, OUTPUT);
  attachInterrupt(0, interrupcao, RISING); //Configurando a interrupção para botão, borda de descida.
  }

void loop(){
  valorPWM = 100;
  analogWrite(pinoMotor, valorPWM);

  if (IR_COUNT > 3){
     
    }
  }
