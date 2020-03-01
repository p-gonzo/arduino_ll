# Devetry Lunch and Learn
## Programable Hardware with Arduino

### Our base board configuration:
Please configure your board as follows using eight `jumper cables`:

In the above diagram, we connect the 5V pin on the Arduino to the HIGH rail on our breadboard, and the Ground pin oun our Arduino to the LOW rail.

We also connect our rails together.

![Base Setup](./assets/base.png)

### A simple circuit:
- **Note**:, how there is no software required for this circuit.
0. Ensure that your Arduino is connected to your Laptop with the Blue USB Cable.
1. Plug your `LED` as shown into the breadboard.
  - Take note of which side is the `anode` (long wire) and `cathode` (short wire).  (The side with the `cathode` also has a small divot next to it's extruding wire.)
2. Using a `jumper cable`, plug the `anode` of the LED into the HIGH RAIL
3. Using a 220 Ohm Resistor (`Red Red Brown` or `Red Red Black Black`), connect the `cathode` to the LOW RAIL.

- **NOTE**: Never complete an LED circuit **directly** between `5V` and `GND` without a resistor.  Your LED will blow, and you may burn your finger.

![Base Setup](./assets/base_with_led.png)

### Controlling our LED with Software:
0. Remove the `jumper cable` connecting your LED's `anode` to the HIGH RAIL and connect it to `pin 8` on the Arduino.

![Base Setup](./assets/base_with_led_2.png)

1. Open the Arduino Software
2. To to `tools > port` and ensure the selection contains `Arduino` somewhere
3. Copy/Paste the sketch below into the IDE.

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

4. Click the `upload` button. (Above the sketch tab, rightward facing arrow)

Note how the LED pulses every half second.

### Controlling the LED with a momentary switch (pushbutton):
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