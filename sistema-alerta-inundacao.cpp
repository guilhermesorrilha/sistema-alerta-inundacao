#include <LiquidCrystal_I2C.h> // Biblioteca para usar o display LCD via interface I2C

// Define os pinos usados pelo sensor ultrassônico
#define trig 13 // Pino de disparo do sensor ultrassônico
#define echo 12 // Pino de recepção do sensor ultrassônico
#define led 10 // Pino do LED de aviso

// Inicializa o display LCD com o endereço I2C 0x27 e dimensões 20 colunas por 4 linhas
LiquidCrystal_I2C lcd(0x27, 20, 4);

float dist = 0; // Variável que armazenará a distância medida

void setup() {
  // Configura os pinos
  pinMode(trig, OUTPUT); // Define o pino trig como saída
  pinMode(echo, INPUT); // Define o pino echo como entrada
  pinMode(led, OUTPUT); // Define o pino do LED como saída

  // Inicializa o LCD
  lcd.init(); // Inicializa o LCD
  lcd.backlight(); // Liga a luz de fundo do LCD
  lcd.begin(20, 4); // Define as dimensões do display 
}

void loop() {
  // Envia um pulso de 10 microssegundos no pino trig para ativar a medição
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Mede o tempo de retorno do sinal e calcula a distância
  dist = pulseIn(echo, HIGH); // Mede o tempo (em microssegundos) do eco
  dist = dist / 58; // Converte o tempo em centímetros (fórmula aproximada)

  // Verifica se a distância é menor ou igual a 350 cm
  if(dist <= 350) {
    // Mostra alerta no LCD
    lcd.setCursor(7, 1); // Define a posição do cursor (coluna 7, linha 1)
    lcd.print("AVISO:");
    lcd.setCursor(1, 2); // Define a posição do cursor (coluna 1, linha 2)
    lcd.print("RISCO DE INUNDACAO");

    // Liga o LED de aviso
    digitalWrite(led, HIGH);
  } else {
    // Se não houver risco, limpa o LCD e desliga o LED
    lcd.clear();
    digitalWrite(led, LOW);
  }
}

