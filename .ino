//notas para as musicas
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
// porta do buzzer
#define BUZZER 8
//biblioteca do LCD
#include <LiquidCrystal_I2C.h>
//portao onde o botaõ foi colocado
#define botao_sobe 2
#define botao_desce 4
// velBotao é oque define a velociade que ele pode trocar de faixa
#define velBotao 300
//lcd(numero do lcd, largura, altura)
LiquidCrystal_I2C lcd(0x27,20,4); 

int melody[] = {
  NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5,
  NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_C5,
  NOTE_C6, NOTE_G6, NOTE_E6, NOTE_C6, NOTE_G6, NOTE_E6,
  
  NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_B5,
  NOTE_FS5, NOTE_DS5, NOTE_DS5, NOTE_E5, NOTE_F5,
  NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_B5
};

int durations[] = {
  16, 16, 16, 16,
  32, 16, 8, 16,
  16, 16, 16, 32, 16, 8,
  
  16, 16, 16, 16, 32,
  16, 8, 32, 32, 32,
  32, 32, 32, 32, 32, 16, 8
};

//variaveis globais
int posDinossauro = 3;
int pontuacao;
int velocidade;
int botaoVirtual = HIGH;
int botaoVirtual2 = HIGH;

//função que controla a musica
void musica() {
  int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    int duration = 1000 / durations[note];
    tone(BUZZER, melody[note], duration);


    int pauseBetweenNotes = duration * 2.00;
    delay(pauseBetweenNotes);
    
    noTone(BUZZER);
  }

}

// tela inicial do jogo
void telaInicial() {
  lcd.clear();
  lcd.setCursor(5, 1);
  lcd.print("Dino game");
  lcd.setCursor(3, 2);
  lcd.print("PRESS TO START");
  while (digitalRead(botao_sobe) == HIGH and digitalRead(botao_desce) == HIGH) {
  }
  
  lcd.clear();
  pontuacao = 0;
  randomSeed(analogRead(A0));
  velocidade = 100;
  musica();
  loop();  
}

// faz a animação de batida e mostra uma tela com a pontuação
void bateu() {    
    lcd.setCursor(2, posDinossauro);
    lcd.print("X");
    delay(1000);
    lcd.clear();
    lcd.setCursor(5, 1);
    lcd.print("Dino game");
    lcd.setCursor(9, 2);
    lcd.print(pontuacao);
  
  	while(digitalRead(botao_sobe) == HIGH and digitalRead(botao_desce) == HIGH) {    
    }
  
  	telaInicial();
}


//inicia as portas do arduino
void setup() {  
  Serial.begin(9600);
  pinMode(botao_sobe, INPUT_PULLUP);
  pinMode(botao_desce, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  telaInicial();
}


//faz todo o codigo do jogo desde posição do dino a obstaculo
void loop() {
  
  //gera o obstaculo
  int posObstaculo = 20;
  int posAltObstaculo = random(0, 4); 
  int posAltObstaculo2 = random(0,4);
  int posAltObstaculo3 = random(0,4);

  int posicaoAnterior = posDinossauro;

  //while que deixa todo codigo "assincrono"
  while(posObstaculo >= -1) {

    //desenha o obstaculo
    lcd.setCursor(posObstaculo, posAltObstaculo);
    lcd.print("#");
    lcd.setCursor(posObstaculo, posAltObstaculo2);
    lcd.print("#");
    lcd.setCursor(posObstaculo, posAltObstaculo3);
    lcd.print("#");
    //desenha o dinoussauro
    lcd.setCursor(2, posDinossauro);
    lcd.print("&");
    //mostra a pontuação
    lcd.setCursor(17, 0);
    lcd.print(pontuacao);

    delay(velocidade);

    //apaga os obstaculos
    lcd.setCursor(posObstaculo, posAltObstaculo);
    lcd.print(" ");
    lcd.setCursor(posObstaculo, posAltObstaculo2);
    lcd.print(" ");
    lcd.setCursor(posObstaculo, posAltObstaculo3);
    lcd.print(" ");
 

    posObstaculo--;  
  

   
   //faz a verificação do dino (troca da faixa e apagar a posição)
    if (digitalRead(botao_sobe) == LOW && botaoVirtual == HIGH) {
      if(posDinossauro>0) {
        posDinossauro--;
      }
      
      botaoVirtual = LOW;
    }

    if (digitalRead(botao_desce) == LOW && botaoVirtual2 == HIGH) {
      if(posDinossauro<3) {
        posDinossauro++;
      }
      
      botaoVirtual2 = LOW;
    }
    
    if (digitalRead(botao_sobe) == HIGH && botaoVirtual == LOW) {
      
      botaoVirtual = HIGH;
    }

    if (digitalRead(botao_desce) == HIGH && botaoVirtual2 == LOW) {
      
      botaoVirtual2 = HIGH;
    }

    if (posicaoAnterior != posDinossauro) {
      lcd.setCursor(2, posicaoAnterior);
      lcd.print(" ");
      posicaoAnterior = posDinossauro;
    }
    
    
    //funcao que verifica se bateu
    if(posObstaculo == 2 && posAltObstaculo == posDinossauro or posObstaculo == 2 && posAltObstaculo2 == posDinossauro or posObstaculo == 2 && posAltObstaculo3 == posDinossauro) {
      bateu();      
    }
    

  }
  
  pontuacao++;
  if(velocidade>15) {
    velocidade -= 1;
  }
}
