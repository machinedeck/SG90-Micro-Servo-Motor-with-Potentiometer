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
