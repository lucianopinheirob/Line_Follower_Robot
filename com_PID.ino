#define receptorEsquerda A2   //Pino de entrada do sensor
#define receptorCentro A0   //Pino de entrada do sensor
#define receptorDireita  A4   //Pino de entrada do sensor
#define dir1motorDireita 8    //Pino direcional do motor
#define dir2motorDireita 10   //Pino direcional do motor
#define dir1motorEsquerda 6   //Pino direcional do motor
#define dir2motorEsquerda 7   //Pino direcional do motor
#define motorDireita 9    //Pino velocidade do motor
#define motorEsquerda 5   //Pino velocidade do motor

volatile float sensorEsquerda, sensorDireita;
volatile float erro;
volatile float velocidadeInicial = 0;

volatile float base = 10;

volatile float P = 0;
volatile float I = 0;
volatile float D = 0;

volatile float previous_erro;

volatile float kp = 0.9;    //Constantes de ganhos determinadas experimentalmente seguindo o passo a passo contido no relatorio
volatile float ki = 0.000001;
volatile float kd = 0.005;

volatile float PID_value = 0;

void setup() {
  analogReference(INTERNAL);    //Como a variação de tensão é de cerca de 1,8V, considereamos uma faixa de valores de 0 a 1,1V suficiente para nosso projeto
  pinMode(receptorEsquerda, INPUT);   //Definição dos pinos de entrada e saida
  pinMode(receptorDireita, INPUT);
  pinMode(receptorCentro, INPUT);
  pinMode(dir1motorDireita, OUTPUT);    //dir1motorDireita = 1, dir2motorDireita = 0, dir1motorEsquerda = 1, dir2motorEsquerda = 0 ==> carro vai para tras
  pinMode(dir2motorDireita, OUTPUT);    //dir1motorDireita = 0, dir2motorDireita = 1, dir1motorEsquerda = 0, dir2motorEsquerda = 1 ==> carro vai para frente
  pinMode(dir1motorEsquerda, OUTPUT);
  pinMode(dir2motorEsquerda, OUTPUT);

  digitalWrite(dir1motorDireita, LOW);    //Definição da direção do carro
  digitalWrite(dir2motorDireita, HIGH);
  digitalWrite(dir1motorEsquerda, LOW);
  digitalWrite(dir2motorEsquerda, HIGH);
}

void loop() {
  read_sensor_values();   //Função que le o valor dos sensores
  calculate_pid();    //Função que calcula o valor de PID
  motor_control();    //Controle da velocidade do motor
}

void read_sensor_values(){
  sensorEsquerda=analogRead(receptorEsquerda);    //Leitura dos sensores
  sensorDireita=analogRead(receptorDireita);
  erro = 0;
  if(sensorEsquerda > 500 && sensorDireita > 450)   //Verificação da diferença da posição atual do carro com a referencia
    erro=0;  
    else if(sensorEsquerda < 200 && sensorDireita > 500)
      erro=10;
      else if(sensorEsquerda >= 200 && sensorEsquerda < 450 && sensorDireita > 500)
        erro=5;
        else if(sensorEsquerda >= 450 && sensorDireita > 500)
          erro=1;
          else if(sensorDireita < 160 && sensorEsquerda > 500)
            erro=(-10);
            else if(sensorDireita >= 160 && sensorDireita < 200 && sensorEsquerda > 500)
              erro=(-5);
              else if(sensorDireita >= 200 && sensorEsquerda > 500)
                erro=(-1);
  
   erro = erro*base; //Aumentamos o valor do erro apenas para se obter maiores valores de PID para a diferença entre as velocidades ser mais significativa
}

void calculate_pid(){
  P = erro;
  I = I + erro;
  D = erro-previous_erro;
  
  PID_value = (kp*P) + (ki*I) + (kd*D);   //Calculo do PID
  
  previous_erro=erro; 
}

void motor_control(){
  float velocidadeMotorEsquerdo = velocidadeInicial - PID_value + 138;    //correção da velocidade dos motores, o motor necessita de um offset para conseguir vencer a incercia, este valor de 138 foi determinado experimentalmente
  float velocidadeMotorDireito = velocidadeInicial + PID_value + 138;
  
  velocidadeMotorEsquerdo = constrain(velocidadeMotorEsquerdo,0,255);   //Limitação do valor da velocidade para um valor entre 0 e 255
  velocidadeMotorDireito = constrain(velocidadeMotorDireito,0,255);
  

 analogWrite(motorEsquerda,velocidadeMotorEsquerdo);   //Seta o motor esquerdo com a nova velocidade
 analogWrite(motorDireita,velocidadeMotorDireito);  //Seta o motor direito com a nova velocidade

}
