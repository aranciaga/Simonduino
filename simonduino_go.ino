/*
* @Name: Simonduino
* @Author: Rainbow 
* @Description: I love you, Joela <3. This is for your birthday
*/

#include "pitches.h"
#include <Tone.h>
#include "nyan.h"
const int greenLed = 8;
const int yellowLed = 9;
const int redLed = 10;
const int blueLed = 11;

int soundValue = 130;
int temp;
const int greenButton = 4;
const int yellowButton = 5;
const int redButton = 6;
const int blueButton = 7;

int easter_egg = 0;
int chooses[255];
int player_selections;
int game[255] = {rand()%4+1, rand()%4+1, rand()%4+1}; 
const int buzzer = 2;
int number_of_games = 2;

void setup(){
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  
  pinMode(greenButton, INPUT);
  pinMode(yellowButton, INPUT);
  pinMode(redButton, INPUT);
  pinMode(blueButton, INPUT);
  randomSeed(analogRead(0));  
  
  if (digitalRead(redButton) == HIGH && digitalRead(yellowButton) == HIGH){
    easter_egg = 1;
    
  } 
  
}
void greenSound(){
  tone(buzzer, NOTE_D6, soundValue);
}

void yellowSound(){
  tone(buzzer, NOTE_E6, soundValue);
}

void redSound(){
  tone(buzzer, NOTE_G6, soundValue);
}

void blueSound(){
  tone(buzzer, NOTE_F6, soundValue);
}

void loop(){
  while(easter_egg==0){
    player_selections = 0;

    while (game[temp] == 0){
      game[temp] = random(5);
    }

    temp = 0;
  
    for (int i = 0; i < number_of_games; i++){
      switch(game[i]){
        case 1:
          digitalWrite(greenLed, HIGH);
          greenSound();
          delay(500);
          digitalWrite(greenLed, LOW);
          break;
        case 2:
          digitalWrite(yellowLed, HIGH);
          yellowSound();
          delay(500);
          digitalWrite(yellowLed, LOW);
          break;
        case 3:
          digitalWrite(redLed, HIGH);
          redSound();
          delay(500);
          digitalWrite(redLed, LOW);
          break;
        case 4:
          digitalWrite(blueLed, HIGH);
          blueSound();
          delay(500);
          digitalWrite(blueLed, LOW);
          break;
      }
    }
    
    do{
      if (digitalRead(greenButton) == HIGH){
        digitalWrite(greenLed, HIGH);
        greenSound();
        delay(300);
        digitalWrite(greenLed, LOW);
        chooses[player_selections] = 1;
        check_input();
        player_selections+=1;
      }
      
      if (digitalRead(yellowButton) == HIGH){
        digitalWrite(yellowLed, HIGH);
        yellowSound();
        delay(300);
        digitalWrite(yellowLed, LOW);
        chooses[player_selections] = 2;
        check_input();
        player_selections+=1;
      }
      
      if (digitalRead(redButton) == HIGH){
        digitalWrite(redLed, HIGH);
        redSound();
        delay(300);
        digitalWrite(redLed, LOW);
        chooses[player_selections] = 3;
        check_input();
        player_selections+=1;
      }
      
      if (digitalRead(blueButton) == HIGH){
        digitalWrite(blueLed, HIGH);
        blueSound();
        delay(300);
        digitalWrite(blueLed, LOW);
        chooses[player_selections] = 4;
        check_input();
        player_selections+=1;
      }
    } while(player_selections < number_of_games);
   
    delay(2000);
    int next = random(5);
    game[player_selections+1] = next;
    temp = player_selections+1;  
    number_of_games+=1;
  }
  
  nyan();
}

void check_input(){
  if (easter_egg == 1){
    nyan();
  } else if (chooses[player_selections] != game[player_selections]){
    error_sequence();
  }
}
void nyan(){
  for (int thisNote = 0; thisNote < 216; thisNote++) {
    int noteDuration = 1400/melodyNoteDurations[thisNote];
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(redLed, HIGH);
    digitalWrite(blueLed, HIGH);
    tone(buzzer, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzer);
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, LOW);
  }
}

void(* resetFunc) (void) = 0;

void error_sequence(){
  digitalWrite(greenLed, HIGH);
  greenSound();
  delay(50);
  digitalWrite(yellowLed, HIGH);
  yellowSound();
  delay(50);
  digitalWrite(redLed, HIGH);
  redSound();
  delay(50);
  digitalWrite(blueLed, HIGH);
  blueSound();
  delay(50);
  
  delay(500);
  
  digitalWrite(blueLed, LOW);
  blueSound();
  delay(50);
  digitalWrite(redLed, LOW);
  redSound();
  delay(50);
  digitalWrite(yellowLed, LOW);
  yellowSound();
  delay(50);
  digitalWrite(greenLed, LOW);
  greenSound();
  delay(2000);
  
  resetFunc();
}



