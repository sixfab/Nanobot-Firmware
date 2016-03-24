
/*
 Written by Okan Saraçoğlu
 Revised by Onur Oktar
 16.03.2016
 */

#define echoPin A4 // Echo Pin
#define trigPin A5 // Trigger Pin
#define LEDPin 13 // Onboard LED

int directionF = 2;
int directionB = 8;
int pwmL = 5;
int pwmR = 6;
int velocity = 0;

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(directionF, OUTPUT);
  pinMode(directionB, OUTPUT);
  pinMode(pwmL, OUTPUT);
  pinMode(pwmR, OUTPUT);
}

void loop() {
  /* The following trigPin/echoPin cycle is used to determine the
   distance of the nearest object by bouncing soundwaves off of it. */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration / 58.2;

  CarForward(200);

  if ( distance <= 10 ) {
    /* Send a negative number to computer and Turn LED ON
    to indicate "out of range" */
    CarStopped();
    CarBack(100);
    delay(500);

    CarBackRight(velocity);
    delay(500);

    CarForward(150);

  }



}
void CarForward(int x) {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, x);
  analogWrite(pwmR, x);
}
void CarStopped() {
  digitalWrite(directionF, LOW);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, 0);
  analogWrite(pwmR, 0);

}

void CarBackRight(int x) {
  digitalWrite(directionF, LOW);
  digitalWrite(directionB, HIGH);
  analogWrite(pwmL, x);
  analogWrite(pwmR, x - 50);
  delay(500);

}
void CarBack(int x) {
  digitalWrite(directionF, LOW);
  digitalWrite(directionB, HIGH);
  analogWrite(pwmL, x);
  analogWrite(pwmR, x);
}


