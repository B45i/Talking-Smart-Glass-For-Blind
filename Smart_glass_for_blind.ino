#include <NewPing.h>

#define MAX_DISTANCE 400

const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;
const int trigPin3 = 6;
const int echoPin3 = 7;

const int motorPinLeft   = A0;
const int motorPinCenter = A1;
const int motorPinRight  = A2;

int minLeftDistance   = 100;
int minCenterDistance = 100;
int minRightDistance  = 100;

NewPing sonarLeft(trigPin1, echoPin1 ,MAX_DISTANCE);
NewPing sonarCenter(trigPin2, echoPin2 ,MAX_DISTANCE);
NewPing sonarRight(trigPin3, echoPin3 ,MAX_DISTANCE);

void sayAlert(int distance) {

}

void setup() {
  Serial.begin(9600); 
}

void loop() {
  delay(29);
  int leftDistance  = sonarLeft.ping_cm();
  int centerDistance  = sonarCenter.ping_cm();
  int rightDistance   = sonarRight.ping_cm();

  // For debugging
  Serial.print("Left: ");
  Serial.print(leftDistance);
  Serial.print(", Center: ");
  Serial.print(centerDistance); 
  Serial.print(", Right: ");
  Serial.println(rightDistance);

  if(leftDistance < minLeftDistance) {
    // Serial.println("Obstacle on left");
    sayAlert(leftDistance);
    analogWrite(motorPinLeft, 512);
  }
  else {
    analogWrite(motorPinLeft, 0);
  }

  if(centerDistance < minCenterDistance) {
    // Serial.println("Obstacle ahed");
    sayAlert(centerDistance);
    analogWrite(motorPinCenter, 512);
  }
  else {
    analogWrite(motorPinCenter, 0);
  }

  if(rightDistance < minRightDistance) {
    // Serial.println("Obstacle on right");
    sayAlert(rightDistance);
    analogWrite(motorPinRight, 512);
  }
  else {
    analogWrite(motorPinRight, 0);
  }

}
