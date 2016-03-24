/*
 Line Follower Nanobot
 Revised for Nanobot by Onur Oktar
 16.03.2016
 */


#include <QTRSensors.h>

#define Kp 0 // experiment to determine this, start by something small that just makes your bot follow the line at a slow speed
#define Kd 0 // experiment to determine this, slowly increase the speeds and adjust this value. ( Note: Kp < Kd) 
#define rightMaxSpeed 200 // max speed of the robot
#define leftMaxSpeed 200 // max speed of the robot
#define rightBaseSpeed 150 // this is the speed at which the motors should spin when the robot is perfectly on the line
#define leftBaseSpeed 150  // this is the speed at which the motors should spin when the robot is perfectly on the line
#define NUM_SENSORS  3     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 us for sensor outputs to go low
#define EMITTER_PIN 7
#define NUM_SAMPLES_PER_SENSOR  4
int directionF = 2;
int directionB = 8;
int pwmL = 5;
int pwmR = 6;

QTRSensorsAnalog qtra((unsigned char[]) {
  1, 2, 3
} , NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN); // sensor connected through analog pins A0 - A5 i.e. digital pins 14-19

unsigned int sensorValues[NUM_SENSORS];


int r = 0;
int l = 0;
int c = 0;


void setup()
{
  pinMode(directionF, OUTPUT);
  pinMode(directionB, OUTPUT);
  pinMode(pwmL, OUTPUT);
  pinMode(pwmR, OUTPUT);

  int i;
  for (int i = 0; i < 400; i++) // calibrate for sometime by sliding the sensors across the line, or you may use auto-calibration instead

    /* comment this part out for automatic calibration
    if ( i  < 25 || i >= 75 ) // turn to the left and right to expose the sensors to the brightest and darkest readings that may be encountered
       turn_right();
     else
       turn_left(); */
    qtra.calibrate();
  delay(20);

  delay(2000); // wait for 2s to position the bot before entering the main loop

  /* comment out for serial printing

  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  */
}



void loop()
{


  DECISION();
  MOVEMENT();




}




void backward() {
  digitalWrite(directionF, LOW);
  digitalWrite(directionB, HIGH);
  analogWrite(pwmL, 100);
  analogWrite(pwmR, 100);

}


void slowbackward() {
  digitalWrite(directionF, LOW);
  digitalWrite(directionB, HIGH);
  analogWrite(pwmL, 80);
  analogWrite(pwmR, 80);


}


void left() {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, 0);
  analogWrite(pwmR, 150);


  //  qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
  unsigned int position = qtra.readLine(sensorValues);






}


void slowleft() {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, 0);
  analogWrite(pwmR, 100);


}


void right() {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, 150);
  analogWrite(pwmR, 0);


  //  qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
  unsigned int position = qtra.readLine(sensorValues);


}


void slowright() {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, 100);
  analogWrite(pwmR, 0);
}


void forward() {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, 150);
  analogWrite(pwmR, 150);
  //  qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
  unsigned int position = qtra.readLine(sensorValues);


}


void pivotleft() {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, 150);
  analogWrite(pwmR, 50);
}


void pivotright() {
  digitalWrite(directionF, LOW);
  digitalWrite(directionB, HIGH);
  analogWrite(pwmL, 150);
  analogWrite(pwmR, 50);


}


void slowforward() {
  digitalWrite(directionF, HIGH);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, 100);
  analogWrite(pwmR, 100);
}




void stop() {
  digitalWrite(directionF, LOW);
  digitalWrite(directionB, LOW);
  analogWrite(pwmL, 0);
  analogWrite(pwmR, 0);
}



void DECISION()
{
  // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
  // To get raw sensor values, call:
  //  qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
  unsigned int position = qtra.readLine(sensorValues);


  if (position > 1030) {

    r = 1;
    l = 0;
    c = 0;


  }

  if (position < 970) {

    l = 1;
    r = 0;
    c = 0;


  }


  if (position >= 970 && position <= 1030) {


    c = 1;
    r = 0;
    l = 0;

  }


}


void MOVEMENT() {
  if (l == 0 && c == 0 && r == 1) {

    left();
  }
  if (l == 1 && c == 0 && r == 0) {

    right();
  }
  if (l == 0 && c == 1 && r == 0) {

    forward();
  }

}



