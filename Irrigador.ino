
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

bool leituraSensor;
bool leituraAnterior;

int tempo = 1000;

void setup() {
  // ativador lc
  lcd.begin (16,2);
  
  //Sensor
  pinMode(8, INPUT);

  //Atuador
  pinMode(12, OUTPUT);
  
  //LEDs
  pinMode(5, OUTPUT);  //vermelho
  pinMode(6, OUTPUT);  //amarelo
  pinMode(7, OUTPUT);  //verde
}

void loop() {

  leituraSensor = digitalRead(8);
  

  if (leituraSensor == HIGH) {
     //No estado seco
     digitalWrite(5, HIGH);  //vermelho
     digitalWrite(7, LOW);   //verde
  
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("A terra esta:");
  lcd.setCursor(0,1);
  lcd.print("Seco!!!");
  delay(tempo);
  
  
  
  } else {
     //No estado úmido
     digitalWrite(5, LOW);   //vermelho
     digitalWrite(7, HIGH);  //verde
  
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("A terra esta:");
  lcd.setCursor(0,1);
  lcd.print("Umida!!!");
  delay(tempo);
 
  }



  //Ao entrar no estado seco  
  if (leituraSensor && !leituraAnterior) {
     delay(5000);
     digitalWrite(5, LOW);   //vermelho
     digitalWrite(6, HIGH);  //amarelo
         lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Irrigacao status:");
  lcd.setCursor(0,1);
  lcd.print("Ativada!!!");
  delay(tempo);

     while (digitalRead(8)) {
        digitalWrite(12, HIGH);   //rele / válvula / solenoide / bomba
        delay(500);
        digitalWrite(12, LOW);   //rele / válvula / solenoide / bomba

        delay(10000);          
     }
     digitalWrite(6, LOW);  //amarelo
   
  
  }
  
  leituraAnterior = leituraSensor;
}
