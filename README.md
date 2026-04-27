Initialize the parameters:
```c
int pin_servo = 7;
int pin_potentiometer = A0;
unsigned long period_ref;
unsigned long pwm_period = 20000;
unsigned long on_length = 2400;
unsigned long old_val = on_length;
int threshold = 5;
```
where
- `pin_servo` : the outpin pin that feeds the PWM signal into the servo motor
- `pin_potentiometer` :  the input pin that reads the voltage drop caused by adjusting the potentiometer
- `pwm_period` : defined period of the PWM

In the setup, assign the pins above as either inputs or output accordingly:
```c
void setup() {
  // put your setup code here, to run once:
  pinMode(pin_servo, OUTPUT);
  pinMode(pin_potentiometer, INPUT);
  Serial.begin(9600);
  period_ref = micros();

}
```
## Inside the loop
Determine the current time
```c
unsigned long time = micros();
```
Then specify what happens inside each period:
```c
if (time - period_ref <= pwm_period) {
  ...
}
```
The angle to which the shaft rotates depends on how long each PWM signal is ON; equivalently, how long `on_length` is in a PWM period. For each period, it can be defined that the PWM signal is initially on within the time duration of `on_length`, and off for the rest of the period:
```c
if (time - period_ref <= on_length) {
    digitalWrite(pin_servo, HIGH);
  }
else {
  digitalWrite(pin_servo, LOW);
  ...
  }
}
```
During the off state, take this time to read the potentiometer:
```c
unsigned long val = 1900L * analogRead(pin_potentiometer) / 1023 + 500;
if (abs(val - old_val) > threshold) {
    on_length = val;
    old_val = val;
}
```

Also add:
```c
else if (time - period_ref > pwm_period) {
  period_ref = micros();
}

```

Overall code:
```c
int pin_servo = 7;
int pin_potentiometer = A0;
unsigned long period_ref;
unsigned long pwm_period = 20000;
unsigned long on_length = 2400;
unsigned long old_val = on_length;
int threshold = 5;


void setup() {
  // put your setup code here, to run once:
  pinMode(pin_servo, OUTPUT);
  pinMode(pin_potentiometer, INPUT);
  Serial.begin(9600);
  period_ref = micros();

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long time = micros();
  // on_length = 1900 * analogRead(pin_potentiometer) / 1023 + 500;
  // Serial.println(String(analogRead(pin_potentiometer)) + ", " + String(on_length));
  
  if (time - period_ref <= pwm_period) {
    if (time - period_ref <= on_length) {
      digitalWrite(pin_servo, HIGH);
    }
    else {
      digitalWrite(pin_servo, LOW);
      unsigned long val = 1900L * analogRead(pin_potentiometer) / 1023 + 500;
      if (abs(val - old_val) > threshold) {
        on_length = val;
        old_val = val;
      }
    }
  }

  else if (time - period_ref > pwm_period) {
    period_ref = micros();
  }
}

```
