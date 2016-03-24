/*
 Bluetooth Code
 Written by Okan Saraçoğlu
 Revised by Onur Oktar
 16.03.2016
 */



int directionF = 2;
int directionB = 8;
int pwmL = 5;
int pwmR = 6;

char command = 'S';
char prevCommand = 'A';
int velocity = 0;
unsigned long timer0 = 2000;  //Stores the time (in millis since execution started)
unsigned long timer1 = 0;  //Stores the time when the last command was received from the phone



void setup() {

  Serial.begin(9600);

  pinMode(directionF, OUTPUT);
  pinMode(directionB, OUTPUT);
  pinMode(pwmL, OUTPUT);
  pinMode(pwmR, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(13, OUTPUT);

}

void loop() {
  if (Serial.available() > 0) {
    timer1 = millis();
    prevCommand = command;
    command = Serial.read();
    Serial.println(command);

    if (command != prevCommand) {
      //Serial.println(command);
      switch (command) {
        case 'F':
          CarForward(velocity);
          break;
        case 'B':
          CarBack(velocity);
          break;
        case 'L':
          CarLeft();
          break;
        case 'R':
          CarRight();
          break;
        case 'S':
          CarStopped();
          break;
        case 'I':  //FR
          CarForwardRight(velocity);
          break;
        case 'J':  //BR
          CarBackRight(velocity);
          break;
        case 'G':  //FL
          CarForwardLeft(velocity);
          break;
        case 'H':  //BL
          CarBackLeft(velocity);
          break;
        case 'D':  //Everything OFF
          CarStopped();
          break;
        case 'W':  // BLUE LED
          digitalWrite(13, HIGH);
          break;
        case 'w': // BLUE LED
          digitalWrite(13, LOW);
          break;
        case 'U':  // RED LED
          digitalWrite(7, HIGH);
          break;
        case 'u': // RED LED
          digitalWrite(7, LOW);
          break;

        case 'X':  // RED and BLUE LED
          digitalWrite(13, HIGH);
          digitalWrite(7, HIGH);
          break;
        case 'x': // RED and BLUE LED
          digitalWrite(13, LOW);
          digitalWrite(7, LOW);
          delay(1000);
          break;

        case 'V':  //Font ON
          analogWrite(3, 150);
          break;
        case 'v':  //Font OFF
          analogWrite(3, 0);
          break;

        default:

          if (command == 'q') {
            velocity = 255;  //Full velocity
            CarSetSpeed(velocity);
          }
          else {
            //Chars '0' - '9' have an integer equivalence of 48 - 57, accordingly.
            if ((command >= 48) && (command <= 57)) {
              //Subtracting 48 changes the range from 48-57 to 0-9.
              //Multiplying by 25 changes the range from 0-9 to 0-225.
              velocity = (command - 48) * 25;
              CarSetSpeed(velocity);
            }
          }
      }
    }
  }
  else {
    timer0 = millis();  //Get the current time (millis since execution started).
    //Check if it has been 500ms since we received last command.
    if ((timer0 - timer1) > 500) {
      //More tan 500ms have passed since last command received, car is out of range.
      //Therefore stop the car and turn lights off.
      CarStopped();
    }
  }
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
  analogWrite(pwmR, 150);
}

void CarRight() {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, 150);
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
  analogWrite(pwmR, x - 50);
}

void CarForwardLeft(int x) {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, x - 50);
  analogWrite(pwmR, x);
}

void CarBackRight(int x) {
  digitalWrite(directionF, LOW);
  digitalWrite(directionB, HIGH);
  analogWrite(pwmL, x);
  analogWrite(pwmR, x - 50);
}

void CarBackLeft(int x) {
  digitalWrite(directionF, LOW);
  digitalWrite(directionB, HIGH);
  analogWrite(pwmL, x - 50);
  analogWrite(pwmR, x);
}

void CarSetSpeed(int x) {
  analogWrite(pwmL, x);
  analogWrite(pwmR, x);
}











