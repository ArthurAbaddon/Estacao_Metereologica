
#include "LiquidCrystal_I2C.h";


 
int     pin       = A0;  // Declara o pino analógico 0 como "pin"
int     Winddir   = 0;   // Declara o valor inicial em 0
float   valor     = 0;   // declara a variável inicial em 0

// --- Constantes ---
const float pi = 3.14159265;     //Número de pi
int period = 5000;               //Tempo de medida(miliseconds)
int delaytime = 2000;            //Invervalo entre as amostras (miliseconds)
int radius = 147;                //Raio do anemometro(mm)

// --- Variáveis Globais ---
unsigned int Sample  = 0;        //Armazena o número de amostras
unsigned int counter = 0;        //Contador para o sensor
unsigned int RPM = 0;            //Rotações por minuto
float speedwind = 0;             //Velocidade do vento (m/s)
float windspeed = 0;             //Velocidade do vento (km/h)
 
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Declara o endereço do Display I2C

void anemometro(); //Função do anemometro do sistema
 
void setup() {
  // Configura o Display I2C de acordo com a biblioteca
  lcd.begin();
  lcd.backlight();
 
  Serial.begin(9600);         // Define o baundrate em 9600
  analogReference(DEFAULT);
  
  pinMode(2, INPUT);        //configura o digital 2 como entrada
  digitalWrite(2, HIGH);    //internall pull-up active

  Serial.begin(9600);       //inicia serial em 9600 baud rate
}
 
void loop() {
  valor = analogRead(pin) * (5.0 / 1023.0); // Calcula a tensão
 
  lcd.clear();
 
  // Apresenta os valores da tensão de saída no Monitor Serial
  Serial.print("Leitura do sensor: ");
  Serial.print(valor);
  Serial.println(" volt");
 
  // Indica a posição norte
  if (valor <= 2.90) {
    Winddir = 0;
    lcd.setCursor(7, 1);
    lcd.print("Norte");
  }
 
 // Indica a posição noroeste
  else if (valor <= 3.05) {
    Winddir = 315;
    lcd.setCursor(7, 1);
    lcd.print("Noroeste");
  }
 
 // Indica a posição oeste
  else if (valor <= 3.25) {
    Winddir = 270;
    lcd.setCursor(7, 1);
    lcd.print("Oeste");
  }
 
 // Indica a posição sudoeste
  else if (valor <= 3.45) {
    Winddir = 225;
    lcd.setCursor(7, 1);
    lcd.print("Sudoeste");
  }
 
 // Indica a posição sul
  else if (valor <= 3.75) {
    Winddir = 180;
    lcd.setCursor(7, 1);
    lcd.print("Sul");
  }
 
 // Indica a posição sudeste
  else if (valor <= 4.00) {
    Winddir = 135;
    lcd.setCursor(7, 1);
    lcd.print("Sudeste");
  }
 
 // Indica a posição leste
  else if (valor <= 4.25) {
    Winddir = 90;
    lcd.setCursor(7, 1);
    lcd.print("Leste");
  }
 
 // Indica a posição nordeste
  else if (valor <= 4.65) {
    Winddir = 45;
    lcd.setCursor(7, 1);
    lcd.print("Nordeste");
  }
 
// Caso nenhum valor seja compatível, imprime FAIL
  else {
    Winddir = 000;
    lcd.setCursor(7, 1);
    lcd.print("FAIL");
  }
 
 // Imprime os valores do Ângulo na linha 1
  lcd.setCursor(0, 0);
  lcd.print("Angulo: ");
  lcd.print(Winddir);
  lcd.print(" Graus");
 
 // Imprime a posição do vento na linha 2
  lcd.setCursor(0, 1);
  lcd.print("Vento: ");
  delay(5000);
}


void anemometro(){
   Sample++;
  Serial.print(Sample);
  Serial.print(": Inicia Leitura...");
  windvelocity();
  Serial.println("   Finalizado.");
  Serial.print("Contador: ");
  Serial.print(counter);
  Serial.print(";  RPM: ");
  RPMcalc();
  Serial.print(RPM);
  Serial.print(";  Vel. Vento: ");

  //*****************************************************************
  //print m/s
  WindSpeed();
  Serial.print(windspeed);
  Serial.print(" [m/s] ");

  //*****************************************************************
  //print km/h
  SpeedWind();
  Serial.print(speedwind);
  Serial.print(" [km/h] ");
  Serial.println();

  delay(delaytime);                        //taxa de atualização
} //end setup


//Função para medir velocidade do vento
void windvelocity() {
  speedwind = 0;
  windspeed = 0;

  counter = 0;
  attachInterrupt(0, addcount, RISING);
  unsigned long millis();
  long startTime = millis();
  while (millis() < startTime + period) {}
}

//Função para calcular o RPM
void RPMcalc() {
  RPM = ((counter) * 60) / (period / 1000); // Calculate revolutions per minute (RPM)
}

//Velocidade do vento em m/s
void WindSpeed() {
  windspeed = ((4 * pi * radius * RPM) / 60) / 1000; //Calcula a velocidade do vento em m/s
} //end WindSpeed

//Velocidade do vento em km/h
void SpeedWind() {
  speedwind = (((4 * pi * radius * RPM) / 60) / 1000) * 3.6; //Calcula velocidade do vento em km/h
} //end SpeedWind

//Incrementa contador
void addcount() {
  counter++;
}
