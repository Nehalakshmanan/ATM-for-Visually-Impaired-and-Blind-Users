#ifndef GLOBAL_H
#define GLOBAL_H
#include <LiquidCrystal.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN  125  // Pulse width for 0°
#define SERVOMAX  625  // Pulse width for 180°
#define DELAYTIME 10   // Delay for smooth movement

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const int numMembers = 2;
char names[numMembers][20] = {"NEHA", "KAVYA"};
char accountNumbers[numMembers][13] = {"123456789012", "234567890123"};
char* AtmPin[numMembers] = {"1212", "2323"};
int accountBalances[numMembers] = {10000, 12000};
int eepromAddress = 0;

enum Account
{
  MAIN_MENU,
  FACE_CHECK,
  ATM_PIN,
  ENTER_ATM_PIN,
  FORGOT_PIN,
  AMOUNT,
  BALANCE_ENQUIRY,
  WITH_DRAWAL
};
Account currentState = MAIN_MENU;

int newBalance = 0;
char f_data, pre_data = 'X';
#define EEPROM_BALANCE_START_ADDR 0

static const uint8_t PIN_MP3_TX = 50; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 51; // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

const int button1Pin = 48;
const int button2Pin = 47;
const int button3Pin = 46;
const int button4Pin = 45;
const int button5Pin = 44;
const int button6Pin = 43;
const int button7Pin = 42;
const int button8Pin = 41;
const int button9Pin = 40;
const int button10Pin = 39;
const int confirmButtonPin = 49;

int pos;
char Send = 'x';

int btn1State;
int btn2State;
int btn3State;
int btn4State;
int btn5State;
int btn6State;
int btn7State;
int btn8State;
int btn9State;
int btn10State;

bool flag, amtflag = false;
int confirmState;
char brailleInput[4];
char lastbraile[3];
int index = 0;
int brailleIndex = 0;
char Option = 'x';
int currentCard = -1;
int originalBalance;
String ReceivedString = "x";
char currentChar = 'x';
char PresentChar = 'x';
int count = 0;
char Atm_Pin = 'x';
int IntDigit;
char digitChar;
int digit;
String NumberString;
bool atmpin = false;
void buttonRead();
void brailleclear();
char* currentNumber;
int Numberlength;
int Namelength;
char* currentName;
#endif
