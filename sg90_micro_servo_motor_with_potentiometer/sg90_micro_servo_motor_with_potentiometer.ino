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
