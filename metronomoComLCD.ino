#include <LiquidCrystal.h>

int buzzer = 13, led1 = 12, led2 = 11, led3 = 10, led4 = 9, pot = A0, contraste = A1, tempo, intervalo, counter = 0, vibra = 6000, brilho = A5;

LiquidCrystal lcd(7,6,5,4,3,2);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  // put your setup code here, to run once:
  analogWrite(contraste, 75);
  analogWrite(brilho, 200);
  pinMode(buzzer, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(pot, INPUT); 
}

void loop() {
  tempo = map(analogRead(pot), 0, 1023, 59, 200);
  
  if (tempo > 59) {   
    intervalo = 60000/tempo;
    Serial.print(tempo);
    Serial.print("   ");
    lcd.setCursor(3, 0);
    lcd.print("Estado: ON");
    lcd.setCursor(4, 2);
    lcd.print("BPM: ");
    lcd.setCursor(9, 2);
    lcd.print(tempo);
    delay(80);
    metronomo();
    lcd.clear();
  } 
  
  else {  //se não estiver pressionado
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Estado: OFF");
    lcd.setCursor(4, 2);
    lcd.print("BPM: ");
    lcd.setCursor(9, 2);
    lcd.print(60);
    Serial.println(tempo);

    delay(80);
  }
}

void metronomo() {
  counter += 1; // Counter tells controller which LED is supposed to flash.
    switch(counter) {
      case 1:
        digitalWrite(led1,HIGH);
        tone(buzzer, vibra, 200);
        Serial.println("1");
        delay(intervalo); // LEDs need to await the interval in order to flash at the right tempo. 
        digitalWrite(led1,LOW);
        break;
      case 2:
        digitalWrite(led2,HIGH);
        tone(buzzer, vibra, 200);
        Serial.println("2");
        delay(intervalo);
        digitalWrite(led2,LOW);
        break;
      case 3:
        digitalWrite(led3,HIGH);
        tone(buzzer, vibra, 200);
        Serial.println("3");
        delay(intervalo);
        digitalWrite(led3,LOW);
        break;
      case 4:
        digitalWrite(led4,HIGH);
        tone(buzzer, 5990, 200);
        Serial.println("4");
        delay(intervalo);
        digitalWrite(led4,LOW);
        counter = 0; // After the 4th/last count the counter restarts.
        break;
    }
}