# Devetry Lunch and Learn
## Programable Hardware with Arduino

### Our base board configuration:
Please configure your board as follows using eight jumper cables:

![Base Setup](./assets/base.png)

In the above diagram, we connect the 5V pin on the Arduino to the HIGH rail on our breadboard, and the Ground pin oun our Arduino to the LOW rail.

We also connect our rails together.

### A simple circuit:
- Note, how there is no software required for this circuit.

![Base Setup](./assets/base_with_led.png)

- Wire Board
- Wire LED
- Turn on LED
- Rewire board
- Blink on LED with software

```cpp
const int LED_PIN {8};
int LED_STATE {HIGH};

void setup()
{
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{  
  digitalWrite(LED_PIN, LED_STATE);
  delay(500);
  LED_STATE = !LED_STATE;
}
```

- Unplug LED
- Wire Button
- Upload Sketch

```cpp
const int LED_PIN {8};
const int BUTTON_PIN {2};

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{  
  digitalWrite(LED_PIN, digitalRead(BUTTON_PIN));
}
```

- Note funk behavior
- Add pulldown resistor

-On / Off behavior

```cpp
const int LED_PIN {8};
const int BUTTON_PIN {2};

int LED_STATE {LOW};

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
  if (digitalRead(BUTTON_PIN))
    LED_STATE = !LED_STATE;
  digitalWrite(LED_PIN, LED_STATE);
}
```

- Explain switch bouncing

```cpp
const int LED_PIN {8};
const int BUTTON_PIN {2};

int LED_STATE {LOW};

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
  if (digitalRead(BUTTON_PIN))
  {
    delay(40);
    if (digitalRead(BUTTON_PIN))
      LED_STATE = !LED_STATE;
  }
  digitalWrite(LED_PIN, LED_STATE);
}
```

- Try to make our LED blink when button is pressed

Show how will start, but wont turn off:
```cpp
const int LED_PIN {8};
const int BUTTON_PIN {2};

int LED_STATE{LOW};
bool LED_BLINKING {false};

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop()
{
  if (digitalRead(BUTTON_PIN))
  {
    delay(40);
    if (digitalRead(BUTTON_PIN))
      LED_BLINKING = !LED_BLINKING;
  }
  if (LED_BLINKING)
  {
    digitalWrite(LED_PIN, LED_STATE);
    delay(500);
    LED_STATE = !LED_STATE;
  }
}
```

- Discuss problems with delay
- Show how interrupt can help

```cpp
const int LED_PIN {8};
const int BUTTON_PIN {2};

int LED_STATE{LOW};
bool LED_BLINKING {false};

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), readButtonPinWithDebounce, RISING);
}

void readButtonPinWithDebounce()
{
  delay(40);
  if (digitalRead(BUTTON_PIN))
    LED_BLINKING = !LED_BLINKING;
}

void loop()
{
  if (LED_BLINKING)
  {
    digitalWrite(LED_PIN, LED_STATE);
    delay(500);
    LED_STATE = !LED_STATE;
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }
}
```