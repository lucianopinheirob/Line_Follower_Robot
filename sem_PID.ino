#define receptorEsquerda A2   //Pino de entrada do sensor
#define receptorCentro A0   //Pino de entrada do sensor
#define receptorDireita  A4   //Pino de entrada do sensor
#define dir1motorDireita 8    //Pino direcional do motor
#define dir2motorDireita 10   //Pino direcional do motor
#define dir1motorEsquerda 6   //Pino direcional do motor
#define dir2motorEsquerda 7   //Pino direcional do motor
#define motorDireita 9    //Pino velocidade do motor
#define motorEsquerda 5   //Pino velocidade do motor


void setup() {
  analogReference(INTERNAL);  //Como a variação de tensão é de cerca de 1,8V, considereamos uma faixa de valores de 0 a 1,1V suficiente para nosso projeto
  pinMode(receptorEsquerda, INPUT);   //Definição dos pinos de entrada e saida
  pinMode(receptorDireita, INPUT);
  pinMode(receptorCentro, INPUT);
  pinMode(dir1motorDireita, OUTPUT);    //dir1motorDireita = 1, dir2motorDireita = 0, dir1motorEsquerda = 1, dir2motorEsquerda = 0 ==> carro vai para tras
  pinMode(dir2motorDireita, OUTPUT);    //dir1motorDireita = 0, dir2motorDireita = 1, dir1motorEsquerda = 0, dir2motorEsquerda = 1 ==> carro vai para frente
  pinMode(dir1motorEsquerda, OUTPUT);
  pinMode(dir2motorEsquerda, OUTPUT);
  pinMode(motorDireita, OUTPUT);
  pinMode(motorEsquerda, OUTPUT);

  digitalWrite(dir1motorDireita, LOW);  //Definição da direção do carro
  digitalWrite(dir2motorDireita, HIGH);
  digitalWrite(dir1motorEsquerda, LOW);
  digitalWrite(dir2motorEsquerda, HIGH);
}

void loop() {   //Arvore de decisões, se o sensor indica que o carro está para a esquerda ou direita da linha, a velocidade dos motores é alterada para corrigir a posição
  if(analogRead(receptorEsquerda) < 400){
    analogWrite(motorEsquerda, 100);
    analogWrite(motorDireita, 245);
  }
    else if(analogRead(receptorDireita) < 400){
      analogWrite(motorEsquerda, 245);
      analogWrite(motorDireita, 100);
    }
      else if(analogRead(receptorDireita) < 400 && analogRead(receptorEsquerda) < 400){
        analogWrite(motorDireita, 0);
        analogWrite(motorEsquerda, 0);
      }
      else{
        analogWrite(motorDireita, 130);
        analogWrite(motorEsquerda, 130);
      }
}
