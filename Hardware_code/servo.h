#ifndef SERVO_H
#define SERVO_H
#include "global.h"

int angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
  Serial.print("Angle: "); Serial.print(ang);
  Serial.print(" pulse: "); Serial.println(pulse);
  return pulse;
}

void convertToBraille(char input) {
  int servosToRun[6] = { -1, -1, -1, -1, -1, -1 }; // Initialize with invalid indices

  switch (input) {
    case 'A':
    case 'a':
    case '1':
      servosToRun[0] = 0;
      break;
    case 'B':
    case 'b':
    case '2':
      servosToRun[0] = 0; servosToRun[1] = 2;
      break;
    case 'C':
    case 'c':
    case '3':
      servosToRun[0] = 0; servosToRun[1] = 1;
      break;
    case 'D':
    case 'd':
    case '4':
      servosToRun[0] = 0; servosToRun[1] = 1; servosToRun[2] = 3;
      break;
    case 'E':
    case 'e':
    case '5':
      servosToRun[0] = 0; servosToRun[1] = 3;
      break;
    case 'F':
    case 'f':
    case '6':
      servosToRun[0] = 0; servosToRun[1] = 1; servosToRun[2] = 2;
      break;
    case 'G':
    case 'g':
    case '7':
      servosToRun[0] = 0; servosToRun[1] = 1; servosToRun[2] = 2; servosToRun[3] = 3;
      break;
    case 'H':
    case 'h':
    case '8':
      servosToRun[0] = 0; servosToRun[1] = 2; servosToRun[2] = 3;
      break;
    case 'I':
    case 'i':
    case '9':
      servosToRun[0] = 1; servosToRun[1] = 2;
      break;
    case 'J':
    case 'j':
    case '0':
      servosToRun[0] = 1; servosToRun[1] = 2; servosToRun[2] = 3;
      break;
    case 'K':
    case 'k':
      servosToRun[0] = 0; servosToRun[1] = 4;
      break;
    case 'L':
    case 'l':
      servosToRun[0] = 0; servosToRun[2] = 2; servosToRun[4] = 4;
      break;
    case 'M':
    case 'm':
      servosToRun[0] = 0; servosToRun[1] = 1; servosToRun[4] = 4;
      break;
    case 'N':
    case 'n':
      servosToRun[0] = 0; servosToRun[1] = 1; servosToRun[3] = 3; servosToRun[4] = 4;
      break;
    case 'O':
    case 'o':
      servosToRun[0] = 0; servosToRun[3] = 3; servosToRun[4] = 4;
      break;
    case 'P':
    case 'p':
      servosToRun[0] = 0; servosToRun[1] = 1; servosToRun[2] = 2; servosToRun[4] = 4;
      break;
    case 'Q':
    case 'q':
      servosToRun[0] = 0; servosToRun[1] = 1; servosToRun[2] = 2; servosToRun[3] = 3; servosToRun[4] = 4;
      break;
    case 'R':
    case 'r':
      servosToRun[0] = 0; servosToRun[2] = 2; servosToRun[3] = 3; servosToRun[4] = 4;
      break;
    case 'S':
    case 's':
      servosToRun[1] = 1; servosToRun[2] = 2; servosToRun[4] = 4;
      break;
    case 'T':
    case 't':
      servosToRun[1] = 1; servosToRun[2] = 2; servosToRun[3] = 3; servosToRun[4] = 4;
      break;
    case 'U':
    case 'u':
      servosToRun[0] = 0; servosToRun[1] = 1; servosToRun[4] = 4; servosToRun[5] = 5;
      break;
    case 'V':
    case 'v':
      servosToRun[0] = 0; servosToRun[4] = 4; servosToRun[5] = 5;
      break;
    case 'W':
    case 'w':
      servosToRun[1] = 1; servosToRun[2] = 2; servosToRun[3] = 3; servosToRun[5] = 5;
      break;
    case 'X':
    case 'x':
      servosToRun[0] = 0; servosToRun[3] = 3; servosToRun[4] = 4; servosToRun[3] = 5;
      break;
    case 'Y':
    case 'y':
      servosToRun[0] = 0; servosToRun[1] = 1; servosToRun[2] = 3; servosToRun[3] = 4; servosToRun[4] = 5;
      break;
    case 'Z':
    case 'z':
      servosToRun[0] = 0; servosToRun[3] = 3; servosToRun[4] = 4; servosToRun[5] = 5;
      break;
    default: return;
  }

  // Move servos from 0° → 90°
  for (int pos = 0; pos <= 90; pos += 10) { // Increase in steps of 5°
    for (int i = 0; i < 6; i++) {
      if (servosToRun[i] != -1) {
        board1.setPWM(servosToRun[i], 0, angleToPulse(pos));
      }
    }
    delay(DELAYTIME);
  }

  delay(1000); // Stay at 90° for 1 sec

  // Move servos from 90° → 0°
  for (int pos = 90; pos >= 0; pos -= 10) { // Decrease in steps of 5°
    for (int i = 0; i < 6; i++) {
      if (servosToRun[i] != -1) {
        board1.setPWM(servosToRun[i], 0, angleToPulse(pos));
      }
    }
    delay(DELAYTIME);
  }
}

void ForNumbers() {
  int servosToRun[6] = { 1, 2, 3, 4, -1, -1 }; // Servos for number prefix (dots 3, 4, 5, 6)

  // Move servos from 0° to 90°
  for (int pos = 0; pos <= 90; pos += 10) {
    for (int i = 0; i < 6; i++) {
      if (servosToRun[i] != -1) {
        board1.setPWM(servosToRun[i], 0, angleToPulse(pos));
      }
    }
    delay(DELAYTIME);
  }

  delay(1000); // Hold at 90° for 1 second

  // Move servos from 90° to 0°
  for (int pos = 90; pos >= 0; pos -= 10) {
    for (int i = 0; i < 6; i++) {
      if (servosToRun[i] != -1) {
        board1.setPWM(servosToRun[i], 0, angleToPulse(pos));
      }
    }
    delay(DELAYTIME);
  }
}


void ForAlphbets() {
  int servosToRun[6] = { 5, -1, -1, -1, -1, -1 }; // Servo for letter prefix (dot 6)

  // Move servo from 0° to 90°
  for (int pos = 0; pos <= 90; pos += 10) {
    for (int i = 0; i < 6; i++) {
      if (servosToRun[i] != -1) {
        board1.setPWM(servosToRun[i], 0, angleToPulse(pos));
      }
    }
    delay(DELAYTIME);
  }

  delay(1000); // Hold at 90° for 1 second

  // Move servo from 90° to 0°
  for (int pos = 90; pos >= 0; pos -= 10) {
    for (int i = 0; i < 6; i++) {
      if (servosToRun[i] != -1) {
        board1.setPWM(servosToRun[i], 0, angleToPulse(pos));
      }
    }
    delay(DELAYTIME);
  }
}


#endif
