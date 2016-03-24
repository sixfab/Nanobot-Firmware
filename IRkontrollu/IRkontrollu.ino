/*
 IR Remote Code
 Written by Okan Saraçoğlu
 Revised by Onur Oktar
 16.03.2016
 */

#include <IRremote.h>
int next = 16720605; // İleri
int prev = 16712445; // Geri
int volM = 16769055; // Sol
int volP = 16754775; // Sağ
int play = 16761405; // Dur
int three = 16743045; // İleri sağa
int nine = 16732845; // Geri sağa
int one = 16724175; // İleri sol
int seven = 16728765; // Geri sol
int equ = 16748655; // Dur
int chM = 16753245; // Kırmızı LED
int chP = 16769565; // Mavi LED
int ch = 16736925; // Buzzer

int RECV_PIN = 4;
int directionF = 2;
int directionB = 8;
int pwmL = 5;
int pwmR = 6;

int velocity = 225;


IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);

  irrecv.enableIRIn(); // Start the receiver

  pinMode(3, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(13, OUTPUT);


  pinMode(directionF, OUTPUT);
  pinMode(directionB, OUTPUT);
  pinMode(pwmL, OUTPUT);
  pinMode(pwmR, OUTPUT);
}

void CarForward(int x) {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, x);
  analogWrite(pwmR, x);
}

void CarBack(int x) {
  digitalWrite(directionF, LOW);
  digitalWrite(directionB, HIGH);
  analogWrite(pwmL, x);
  analogWrite(pwmR, x);
}

void CarLeft() {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, 0);
  analogWrite(pwmR, 200);
}

void CarRight() {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, 200);
  analogWrite(pwmR, 0);
}

void CarStopped() {
  digitalWrite(directionF, LOW);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, 0);
  analogWrite(pwmR, 0);
}

void CarForwardRight(int x) {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, x);
  analogWrite(pwmR, x - 75);
}

void CarForwardLeft(int x) {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, x - 75);
  analogWrite(pwmR, x);
}

void CarBackRight(int x) {
  digitalWrite(directionF, LOW);
  digitalWrite(directionB, HIGH);
  analogWrite(pwmL, x);
  analogWrite(pwmR, x - 75);
}

void CarBackLeft(int x) {
  digitalWrite(directionF, LOW);
  digitalWrite(directionB, HIGH);
  analogWrite(pwmL, x - 75);
  analogWrite(pwmR, x);
}

void CarSetSpeed(int x) {
  analogWrite(pwmL, x);
  analogWrite(pwmR, x);
}


void loop() {
  Serial.println(results.value);
  if (irrecv.decode(&results)) {

    if ((int)results.value == next) {
      CarForward(velocity);
    }

    if ((int)results.value == prev) {
      CarBack(velocity);
    }

    if ((int)results.value == volM) {
      CarLeft();
    }
    if ((int)results.value == volP) {
      CarRight();
    }

    if ((int)results.value == play) {
      CarStopped();
    }

    if ((int)results.value == three) {
      CarForwardRight(velocity);
    }
    if ((int)results.value == nine) {
      CarBackRight(velocity);
    }
    if ((int)results.value == one) {
      CarForwardLeft(velocity);
    }

    if ((int)results.value == seven) {
      CarBackLeft(velocity);
    }

    if ((int)results.value == equ) {
      CarStopped();
    }
    if ((int)results.value == chM) {
      digitalWrite(7, HIGH);
      delay(1000);
      digitalWrite(7, LOW);
      delay(1000);
    }

    if ((int)results.value == chP) {
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
      delay(1000);
    }

    if ((int)results.value == ch) {
      digitalWrite(3, HIGH);
      delay(1000);
      digitalWrite(3, LOW);
      delay(1000);
    }


    irrecv.resume(); // Receive the next value
    digitalWrite(13, LOW);
  }
  delay(100);
}
