const int LEDPins[5] {2, 3, 4, 5, 6};
int currentLEDIndex {0};
const int winningLEDIndex {2};
const int ButtonPin {8};
int prevButtonState {LOW};
int ledOnDuration {300};
long timeLEDLastMoved = {0};

void setup()
{
  for (int i = 0; i < 5; i++)
  {
    pinMode(LEDPins[i], OUTPUT);
  }
  pinMode(ButtonPin, INPUT);
  
  Serial.begin(9600);
  newGame();
}

void loop() {
  
  if(millis() - timeLEDLastMoved >= ledOnDuration)
  {
    timeLEDLastMoved = millis();
    currentLEDIndex++;
    currentLEDIndex = currentLEDIndex % 6;
    turnOnLEDAtIndex(currentLEDIndex);
  }
  
  if(digitalRead(ButtonPin) == HIGH && prevButtonState == LOW)
  {
    if(currentLEDIndex == winningLEDIndex)
    {
      digitalWrite(winningLEDIndex, LOW);
      delay(50);
      digitalWrite(winningLEDIndex, HIGH);

      ledOnDuration *= 0.9;
      
      Serial.print("Score: ");
      Serial.println(ledOnDuration);
      
    }
    else //Game over
    {
      Serial.println("GAME OVER");
      Serial.print("Final Score ");
      Serial.println(ledOnDuration);
      
      //Blink the Led that the player stopped on.
      for (int x = 0; x <= 10; x++)
      {
        if(digitalRead(currentLEDIndex + 1) == LOW)
        {
          digitalWrite(currentLEDIndex + 1, HIGH);
        }
        else
        {
          digitalWrite(currentLEDIndex + 1, LOW);
        }
        delay(200);
      }
      newGame();
    }
  }
  prevButtonState = digitalRead(ButtonPin);
} // End of our Main Loop //

void turnOnLEDAtIndex(int currentLEDIndex)
{
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(LEDPins[i], LOW);
  }
  digitalWrite(currentLEDIndex + 1, HIGH);
}

void newGame()
{
  currentLEDIndex = 0;
  ledOnDuration = 1000;
  Serial.println("New Game: Score 1000");
}
