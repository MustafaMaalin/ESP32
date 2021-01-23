
// Define pins for ultrasonic and buzzer
int const trigger = 10;
int const echo = 9;
int const buzz = 2;

void setup()
{
  pinMode(trigger, OUTPUT); // trig pin will have pulses output
  pinMode(echo, INPUT); // echo pin should be input to get pulse width
  pinMode(buzz, OUTPUT); // buzz pin is output to control buzzering
}

void loop()
{
  // Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters
  int duration, distance;
  // Output pulse with 1ms width on trigger
  digitalWrite(trigger, HIGH); 
  delay(1);
  digitalWrite(trigger, LOW);
  // Measure the pulse input in echo pin
  duration = pulseIn(echo, HIGH);
  // Distance is half the duration devided by 29.1 (from datasheet)
  distance = (duration/2) / 29.1;
  // if distance less than 0.15 meter and more than 0 (0 or less means over range) 
    if (distance <= 15 && distance >= 0) {
      // Buzz
      digitalWrite(buzz, HIGH);
    } else {
      // Don't buzz
      digitalWrite(buzz, LOW);
    }
    // Waiting 60 ms 
    delay(60);
}
