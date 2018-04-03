#include <Arduino.h>
#include <NewPing.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define MAX_DISTANCE 400

const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;
const int trigPin3 = 6;
const int echoPin3 = 7;


const int motorPinRight  = A0;
const int motorPinCenter = A1;
const int motorPinLeft   = A2;

int minLeftDistance   = 100;
int minCenterDistance = 100;
int minRightDistance  = 100;

static unsigned long timer = millis();

int waitTime = 3500;

NewPing sonarLeft(trigPin1, echoPin1 ,MAX_DISTANCE);
NewPing sonarCenter(trigPin2, echoPin2 ,MAX_DISTANCE);
NewPing sonarRight(trigPin3, echoPin3 ,MAX_DISTANCE);

SoftwareSerial mp3SoftwareSerial(8, 9); // RX, TX
DFRobotDFPlayerMini DFPlayer;

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

void leftAlert(int distance) {
  
  if (millis() - timer > waitTime) {
    timer = millis();
    DFPlayer.playLargeFolder(01, distance+1);
  } 
  if (DFPlayer.available()) {
    printDetail(DFPlayer.readType(), DFPlayer.read()); //Print the detail message from DFPlayer
  }
}

void centerAlert(int distance) {

  if (millis() - timer > waitTime) {
    timer = millis();
    DFPlayer.playLargeFolder(02, distance+1);
  } 
  if (DFPlayer.available()) {
    printDetail(DFPlayer.readType(), DFPlayer.read()); //Print the detail message from DFPlayer
  }
}

void rightAlert(int distance) {
  
  if (millis() - timer > waitTime) {
    timer = millis();
    DFPlayer.playLargeFolder(03, distance+1);
  } 
  if (DFPlayer.available()) {
    printDetail(DFPlayer.readType(), DFPlayer.read()); //Print the detail message from DFPlayer
  }
}

void setupDFPlayer() {

  mp3SoftwareSerial.begin(9600);
  Serial.println();
  Serial.println(F("Blind assistancs smart glass..."));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!DFPlayer.begin(mp3SoftwareSerial)){
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  DFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  DFPlayer.volume(29);  //Set volume value (0~30)
  DFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  DFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
}

void setup() {
  Serial.begin(9600);
  setupDFPlayer();
}

void loop() {
  delay(29);
  int leftDistance  = sonarLeft.ping_cm();
  int centerDistance  = sonarCenter.ping_cm();
  int rightDistance   = sonarRight.ping_cm();

 // For debugging
//   Serial.print("Left: ");
//   Serial.print(leftDistance);
//   Serial.print(", Center: ");
//   Serial.print(centerDistance); 
//   Serial.print(", Right: ");
//   Serial.println(rightDistance);

  if(leftDistance < minLeftDistance && leftDistance > 1) {
    
    Serial.print("Obstacle ");
    Serial.print(leftDistance);
    Serial.println(" CM to the left");

    leftAlert(leftDistance);
    analogWrite(motorPinLeft, 512);
  }
  else {
    analogWrite(motorPinLeft, 0);
  }

  if(centerDistance < minCenterDistance && centerDistance > 1) {

    Serial.print("Obstacle ");
    Serial.print(centerDistance);
    Serial.println(" CM ahed");

    centerAlert(centerDistance);
    analogWrite(motorPinCenter, 512);
  }
  else {
    analogWrite(motorPinCenter, 0);
  }

  if(rightDistance < minRightDistance && rightDistance > 1) {

    Serial.print("Obstacle ");
    Serial.print(rightDistance);
    Serial.println(" CM to the right");

    rightAlert(rightDistance);
    analogWrite(motorPinRight, 512);
  }
  else {
    analogWrite(motorPinRight, 0);
  }

}
