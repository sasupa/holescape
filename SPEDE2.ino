int startBtn = 2;
int buttonPins[] = {3, 4, 5, 6, 7, 8, 9, 10}; // Array of button pin numbers
int ledPins[] = {11, 12, 13, A0, A1, A2, A3, A4}; // Array of LED pin numbers
int startBtn_state;

int gameState = 0;
int score = 0;
bool scoreCounted;
bool gameWon = false;
int mole = -1;
 
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    pinMode(startBtn, INPUT_PULLUP);
    pinMode(buttonPins[i], INPUT_PULLUP); // Set button pins as INPUT_PULLUP
    pinMode(ledPins[i], OUTPUT); // Set LED pins as OUTPUT
    pinMode(A5, OUTPUT);
  }
  startBtn_state = 1;
  digitalWrite(A5, LOW);
}
 
void pause() {
  unsigned long current;
  unsigned long end;
  
  delay(500);
  mole = -1;
  for (int i = 0; i < 8; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  
  int pause = random(100,1000);
  current = millis();
  end = millis() + pause;
  while  (millis() < end) { 
    if (ledPins[0] == HIGH || ledPins[1] == HIGH || ledPins[2] == HIGH || ledPins[3] == HIGH || ledPins[4] == HIGH || ledPins[5] == HIGH || ledPins[6] == HIGH || ledPins[7] == HIGH) { 
       delay(300);
    }
  }
}
 
// Randomly decide which LED to turn on
void displayMole() {
  mole = random(1, 9);
  if (mole==1) {
    scoreCounted = false;
    digitalWrite(ledPins[0], HIGH);
  } else if (mole==2) {
    scoreCounted = false;
    digitalWrite(ledPins[1], HIGH);
  } else if (mole==3) {
    scoreCounted = false;
    digitalWrite(ledPins[2], HIGH); 
  } else if (mole==4) {
    scoreCounted = false;
    digitalWrite(ledPins[3], HIGH); 
  } else if (mole==5) {
    scoreCounted = false;
    digitalWrite(ledPins[4], HIGH); 
  } else if (mole==6) {
    scoreCounted = false;
    digitalWrite(ledPins[5], HIGH); 
  } else if (mole==7) {
    scoreCounted = false;
    digitalWrite(ledPins[6], HIGH); 
  } else if (mole==8) {
    scoreCounted = false;
    digitalWrite(ledPins[7], HIGH); 
  }
}
 
// If the user presses a button corresponding to the right LED (Whack a mole) > 1 score earned

void whackMole() {
  unsigned long current;
  unsigned long end;
  current = millis();
  end = millis() + 750;
  while  (millis() < end && gameWon==false) {
    
      int btn1_state = digitalRead(buttonPins[0]);
      if (btn1_state == 0) { // check if the 1=red is pressed
        if (mole==1 && scoreCounted==false) {
        score++;
        Serial.println(score);
        scoreCounted=true;
        delay(10);
      } 
      } 
    
    int btn2_state = digitalRead(buttonPins[1]);
      if (btn2_state == 0) { // check if the 1=red is pressed
      if (mole==2 && scoreCounted==false) {
        score++;
        Serial.println(score);
        scoreCounted=true;
        delay(10);
      } 
    }
    
    int btn3_state = digitalRead(buttonPins[2]);
      if (btn3_state == 0) { // check if the 1=red is pressed
      if (mole==3 && scoreCounted==false) {
        score++;
        Serial.println(score);
        scoreCounted=true;
        delay(10);
      } 
    }
    
    int btn4_state = digitalRead(buttonPins[3]);
      if (btn4_state == 0) { // check if the 1=red is pressed
      if (mole==4 && scoreCounted==false) {
        score++;
        Serial.println(score);
        scoreCounted=true;
        delay(10);
      } 
    }
    
    int btn5_state = digitalRead(buttonPins[4]);
      if (btn5_state == 0) { // check if the 1=red is pressed
      if (mole==5 && scoreCounted==false) {
        score++;
        Serial.println(score);
        scoreCounted=true;
        delay(10);
      } 
    }
    
    int btn6_state = digitalRead(buttonPins[5]);
      if (btn6_state == 0) { // check if the 1=red is pressed
      if (mole==6 && scoreCounted==false) {
        score++;
        Serial.println(score);
        scoreCounted=true;
        delay(10);
      } 
    }
    
    int btn7_state = digitalRead(buttonPins[6]);
      if (btn7_state == 0) { // check if the 1=red is pressed
      if (mole==7 && scoreCounted==false) {
        score++;
        Serial.println(score);
        scoreCounted=true;
        delay(10);
      } 
    }
    
    int btn8_state = digitalRead(buttonPins[7]);
      if (btn8_state == 0) { // check if the 1=red is pressed
      if (mole==8 && scoreCounted==false) {
        score++;
        Serial.println(score);
        scoreCounted=true;
        delay(10);
      } 
    }

  }  
}
 
void loop() {
  if (score >= 10 && !gameWon) {
    gameWon = true;
    gameState = 0;
    for (int x = 0; x < 5; x++) {
      for (int i = 0; i < 8; i++) {
        digitalWrite(ledPins[i], HIGH);
      };
      delay(200);
      for (int i = 0; i < 8; i++) {
        digitalWrite(ledPins[i], LOW);
      };
      delay(200);
    }
    digitalWrite(A5, HIGH);
    Serial.println("Let the games end!");
  }

  if (gameState == 0) {
    startBtn_state = digitalRead(startBtn);
    if (startBtn_state == 0) {
      digitalWrite(A5, LOW);
      Serial.println("Let the games begin!");
      gameState = 1;
    }  
  }
  
  if (gameState == 1) {
    pause();
    displayMole();
    whackMole();
  }
}
