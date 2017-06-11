/*PRJETO 3 - CONTROLE DE VELOCIDADE - RODRIGO & GUSTAVO. 
 * Este projeto tem a finalidade de acionar e controlar a velocidade de um motor de 5V. Digita-se a velocidade em RPM desejada no teclado e pela UART0 aplica-se o PWM necessario para esta
 * velocidade. Para o controle da velocidade, um sensor infra-vermelho posicionado nas helices do motor aciona a interrupcao do INT0 para contagem de voltas que eh transformada em RPM pela
 * interrupcao de tempo ISR_timer a cada 0.05s, a cada 1s no terminal serial eh impresso a velocidade atual do motor. Ainda na ISR_timer eh feito a malha de realimentacao de controle da
 * velocidade, que compara a velocidade atual com a desejada e realiza a correcao do PWM aplicado ao motor. Por fim, a qualquer momento pode-se digitar uma nova velocidade desejada.
 */

#include <stdio.h>
#include <TimerOne.h>

//variaveis para controle de velocidade
float erro;
float velocidade_atual = 0;
float velocidade_real = 0;
int velocidade_desejada = 0;
int velocidade_real_PWM = 0;

//variaveis para contagem de RPM
int voltas = 0;
int IR_COUNT = 0;
int COUNT_print = 0;
long valor;

//saida para PWM
int pinoMotor = 3;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//interrupcao periodica de 0.05s para calculo de velocidade e contre de realimentacao
void ISR_timer() {

   
   velocidade_atual = voltas*60/0.05; // com o numero de voltas em 0.05s, tem-se a projecao para 1 minuto - RPM
  //reinicia contadores de voltas
   voltas = 0; 
   IR_COUNT = 0;

   //faz a media das velocidades em 1s e imprime no terminal
   valor = valor + (int)velocidade_atual;
   COUNT_print++;
   if(COUNT_print == 19){
    Serial.print(valor/20, DEC);
    Serial.print("\n");
    valor = 0;
    COUNT_print = 0;
   }

   //malha de realimentacao
   erro =  velocidade_atual - velocidade_desejada; // diferenca entre a velocidade atual do motor com a velocidade setada no termnial
   velocidade_real = velocidade_real - (0.0015*erro); //equacao de realimentacao com ganho alpha = 0.0015
   velocidade_real_PWM = (int)(velocidade_real*0.044); //transforma a velocidade de RPM para PWM - sabe-se do motor que tem velocidade maxima de 5750RPM para 5V(PWM = 255)

   //trava PWM em 0 ou 255 caso calculo passe dos respectivos limites
   if(velocidade_real_PWM > 255) velocidade_real_PWM = 255;
   if(velocidade_real_PWM < 0) velocidade_real_PWM = 0;    
 }

//Interrupcao do INT0 para contagem de voltas, a cada meia volta do motor, uma passagem da helice, aciona-se a interrupcao
void interrupcao(){ 

  IR_COUNT++; //a cada meia volta incrementa o contador 
  delay(5); // delay para deboucing
  
  if(IR_COUNT%2 == 0){ 
    voltas = IR_COUNT/2; //se for par, o numero de voltas eh a qtd de int por 2.
  }
  else
    voltas = (IR_COUNT-1)/2; //impar, subtrai um.
  } 
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup(){
  pinMode(pinoMotor, OUTPUT); //saida para PWM do motor
  
  attachInterrupt(0, interrupcao, RISING); //Configurando a interrupção para IR, borda de subida.
  Serial.begin(9600); //comunicacao serial 
  Timer1.initialize(50000); // Interrupcao a cada 0.05s
  Timer1.attachInterrupt(ISR_timer); // Associa a interrupcao periodica a funcao ISR_timer
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//no Loop principal, realiza-se a leitura da velocidade desejada no terminal e aplica o PWM ao motor.
void loop(){
 char vel;

 //PWM corrigigo eh aplicado ao motor
 analogWrite(pinoMotor, velocidade_real_PWM);
 
 //realiza a leitura da velocidade desejada no terminal setada no teclado
 if(Serial.available() > 0){ 
  velocidade_desejada = Serial.parseInt();
  analogWrite(pinoMotor, (int)(velocidade_desejada*0.044)); //aplica no motor PWM inicial
  Serial.print("START\n");
  vel = Serial.read();   
 }
}
