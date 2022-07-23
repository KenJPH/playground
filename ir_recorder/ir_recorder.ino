#include "ir_recorder.h"

int currentIn;
bool lastIn; // false: ON, true: OFF
unsigned long currentTime;
unsigned long lastTime;

int recordIndex;
record records[record_size];

void setup() {
  Serial.begin(9600);
  pinMode(inPin, INPUT);
  digitalWrite(inPin, HIGH);
}

void loop() {
  currentIn = (PINB & inPinMask) == inPinMask;
  currentTime = micros();

  if (currentIn != lastIn) {
    insertRecord();

    lastIn = currentIn;
    lastTime = currentTime;
  }

  if (recordIndex == record_size) {
    printRecords();
  }
}

void insertRecord() {
  record r;
  r.in = lastIn;
  r.duration = currentTime - lastTime;
  records[recordIndex++] = r;
}

void printRecords() {
  for (int i = 0; i < record_size; i++) {
    Serial.print(records[i].in);
    Serial.print(",");
    Serial.println(records[i].duration);
  }

  recordIndex = 0;
}
