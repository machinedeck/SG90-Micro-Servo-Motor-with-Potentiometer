# Scanning Functionality of SG90 Micro Servo Motor

## Code Explanation
### Parameter Initialization
First, define the timing parameters. The PWM signal has a cycle period of 20 ms, and the pulse width is determines at which angle the servo motor rotates. SG90's possible rotation angle range is 0&deg;-180&deg;, which corresponds to a pulse width range of approximately 0.5-2.4 ms (check datasheet [here](https://handsontec.com/dataspecs/motor_fan/SG90-Servo.pdf)). However, I observed some jitter at 0.5-ms pulse width, so I increased the lower bound to 0.55 ms.

For the scanning part where the shaft of SG90 rotates in cycles from 0&deg; to 180&deg; then back to 0&deg;, I defined a pulse width increment of 25 &mu;s every 20-s PWM cycle. This implies that the shaft performs a half rotation in 1.48 s. With these characteristics, we define the following:
```c
// Time in microseconds
unsigned long pwm_period = 20000;
unsigned long init_width = 550;
unsigned long inc = 25; // Increment of the pulse width every 20 milliseconds
```
We set the parameter `status` to tell the shaft whether to add or subtract increments, corresponding to movement towards (`status = 1`) or away (`status = - 1`) from the 180&deg;-angle position, respectively. `status = 1` is the default state.
```c
int status = 1;
```
Also define the initial time containers to track PWM period and the time period at which the increment must be implemented:
```c
unsigned long init_time;
unsigned long increment_int_time;
```
&#x26A0;**NOTE:** _I got an error before, and now I think the code can be further simplified. I am not pretty sure if I can change the PWM period length to less or greater than 20 ms (as long as greater than the maximum 2.4 ms pulse width), nor am I sure why SG90 needs a PWM signal to rotate the shaft in a certain direction. But I think at an instant, the shaft can rotate to a particular direction if its pulse width is changed in one cycle. I tried incrementing the pulse width every PWM cycle and it rotated continuously, so I guess the PWM signal is needed to sustain its direction._

_However, I am not sure how long the PWM period or the pulse-width-to-PWM-period ratio is so that when I increment it, it successfully land in its supposed direction._

Lastly, the pin which feeds the PWM signal into the SG90 must be defined:
```c
int pwm_pin = 7;
```

### `void setup()`
```c
void setup() {
  // put your setup code here, to run once:
  pinMode(pwm_pin, OUTPUT);
  init_time = micros();
  increment_init_time = micros();
  init_width = 550;
}
```

### `void loop()`
```c
void loop() {
  // put your main code here, to run repeatedly:

  // Record the current time
  unsigned long curr_time = micros();


  // This is for rotation at a single angle
  // This creates the required 20-ms cycle and the pulse width
  if (curr_time - init_time < pwm_period) {
    if (curr_time - init_time < init_width) {
      digitalWrite(pwm_pin, 1);
    }
    else {
      digitalWrite(pwm_pin, 0);
    }
  }
  // This resets the initial time when the cycle is finished
  else {
    init_time = curr_time;
  }

  // This changes the pulse width every 20 ms by incrementing it
  // This translates to the "scanning" or rotation of the shaft
  if (curr_time - increment_int_time > 20000) {
    increment_int_time = curr_time;
    if (status == 1) {
      init_width += inc;
      if (init_width > 2400) {
        init_width = 2400;
        status = - 1;
      }
    }

    else if (status == - 1){
      init_width -= inc;
      if (init_width < 550) {
        init_width = 550;
        status = 1;
      }
    }
  }
}
```


## Overall Code
```c
// Time in microseconds
unsigned long pwm_period = 20000;
unsigned long init_width = 550;
unsigned long inc = 25; // Increment of the pulse width every 2 seconds
int status = 1;
unsigned long init_time;

int pwm_pin = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(pwm_pin, OUTPUT);
  init_time = micros();
  init_width = 550;
}

void loop() {
  // put your main code here, to run repeatedly:

  // Record the current time
  unsigned long curr_time = micros();


  // This is for rotation at a single angle
  // This creates the required 20-ms cycle and the pulse width
  if (curr_time - init_time < pwm_period) {
    if (curr_time - init_time < init_width) {
      digitalWrite(pwm_pin, 1);
    }
    else {
      digitalWrite(pwm_pin, 0);
    }
  }
  // This resets the initial time when the cycle is finished
  else {
    init_time = micros();
  }

  // This changes the pulse width every 2 s by incrementing it
  // This translates to the "scanning" or rotation of the shaft
  if (curr_time - init_time > 2000000) {
    if (status == 1) {
      init_width += inc;
      if (init_width > 2400) {
        init_width = 2400;
        status = - 1;
      }
    }

    else if (status == - 1){
      init_width -= inc;
      if (init_width < 550) {
        init_width = 550;
        status = 1;
      }
    }
  }
}
```


## Overall Code with Interrupt
```c
// Time in microseconds
unsigned long pwm_period = 20000;
unsigned long init_width = 550;
unsigned long inc = 25; // Increment of the pulse width every 2 seconds
int status = 1;
unsigned long init_time;

int button_pin = 2; // Interrupt pin
int button_stat = 1;

int pwm_pin = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(pwm_pin, OUTPUT);
  init_time = micros();
  init_width = 550;
  // Interrupt
  // Use RISING since I am using pull-up resistor switch type
  attachInterrupt(digitalPinToInterrupt(button_pin), interrupt, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Record the current time
  unsigned long curr_time = micros();


  // This is for rotation at a single angle
  // This creates the required 20-ms cycle and the pulse width
  if (curr_time - init_time < pwm_period) {
    if (curr_time - init_time < init_width) {
      digitalWrite(pwm_pin, 1);
    }
    else {
      digitalWrite(pwm_pin, 0);
    }
  }
  // This resets the initial time when the cycle is finished
  else {
    init_time = micros();
  }

  // Check if button_stat = 1 so that continue scanning
  if (button_stat == 1) {
    // This changes the pulse width every 2 s by incrementing it
    // This translates to the "scanning" or rotation of the shaft
    if (curr_time - init_time > 2000000) {
      if (status == 1) {
        init_width += inc;
        if (init_width > 2400) {
          init_width = 2400;
          status = - 1;
        }
      }

      else if (status == - 1){
        init_width -= inc;
        if (init_width < 550) {
          init_width = 550;
          status = 1;
        }
      }
    }
  }
}

// Interrupt
void interrupt() {
  button_stat = !button_stat;
}
```
