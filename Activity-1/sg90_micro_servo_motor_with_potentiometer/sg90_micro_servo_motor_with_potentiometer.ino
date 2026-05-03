int pin_servo = 7;
int pin_potentiometer = A0;
unsigned long period_ref;
unsigned long pwm_period = 20000;
unsigned long on_length = 2400;
unsigned long old_val = on_length;
int threshold = 10;


void setup() {
  // put your setup code here, to run once:
  pinMode(pin_servo, OUTPUT);
  pinMode(pin_potentiometer, INPUT);
  // Serial.begin(9600);
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
      unsigned long val = 1850L * analogRead(pin_potentiometer) / 1023 + 550;
      on_length = val;
      // if (abs(val - old_val) > threshold) {
      //   on_length = val;
      //   old_val = val;
      // }
    }
  }

  else if (time - period_ref > pwm_period) {
    period_ref = micros();
  }
}








// const int servo_pin = 7;
// const int pot_pin = A0;
// unsigned long on_length = 1;
// unsigned long old_val = on_length;
// unsigned long threshold = 5;


// void setup() {
//   pinMode(servo_pin, OUTPUT);
//   pinMode(pot_pin, INPUT);
// }

// void loop() {

//   digitalWrite(servo_pin, HIGH);
//   delay(on_length);
//   digitalWrite(servo_pin, LOW);
//   // unsigned long val = 1900L * analogRead(pot_pin) / 1023 + 500;
//   unsigned long val = 1900L * analogRead(pot_pin) / 1023 + 500;
//   on_length = val / 1000L;
//   // if (abs(val - old_val) > threshold) {
//   //   on_length = val;
//   //   old_val = val;
//   // }
//   delay(20 - on_length);
//   // delay
// }




// // Time in microseconds
// unsigned long pwm_period = 20000;
// unsigned long init_width = 550;
// int status = 1;
// unsigned long init_time;

// int pwm_pin = 7;

// void setup() {
//   // put your setup code here, to run once:
//   pinMode(pwm_pin, OUTPUT);
//   init_time = micros();
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   unsigned long curr_time = micros();

//   if (curr_time - init_time < pwm_period) {
//     if (curr_time - init_time < init_width) {
//       digitalWrite(pwm_pin, 1);
//     }
//     else {
//       digitalWrite(pwm_pin, 0);
//     }
//   }

//   else {
//     init_time = micros();
//   }





  // digitalWrite(pwm_pin, 1);
  // delayMicroseconds(init_width);
  // digitalWrite(pwm_pin, 0);
  // delayMicroseconds(pwm_period - init_width);
  // if (status == 1) {
  //   init_width += 20;
  //   if (init_width > 2400) {
  //     init_width = init_width - 2;
  //     status = - 1;
  //   }
  // }
  // else if (status == - 1) {
  //   init_width -= 20;
  //   if (init_width < 550) {
  //     init_width = init_width + 20;
  //     status = 1;
  //   }
  // }
}
