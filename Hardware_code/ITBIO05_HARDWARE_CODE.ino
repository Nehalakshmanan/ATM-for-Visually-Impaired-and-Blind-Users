#include "global.h"
#include "button.h"
#include "servo.h"
#include <avr/wdt.h>
void audio(int data);
DFRobotDFPlayerMini player;

void setup() {
  Serial.begin(9600);
  softwareSerial.begin(9600);
  board1.begin();
  board1.setPWMFreq(60);

  // **Initialize all servos to 0°**
  Serial.println("Initializing servos to 0°...");
  for (int i = 0; i < 16; i++) {
    board1.setPWM(i, 0, angleToPulse(0));
  }
  if (player.begin(softwareSerial)) {
    Serial.println("OK");
  }
  else
  {
    Serial.println("Not-OK");
  }
  lcd.begin(16, 2);
  //  lcd.backlight();
  lcd.print("ATM for");
  lcd.setCursor(0, 1);
  lcd.print("Deaf Dumb Blind");
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);
  pinMode(button5Pin, INPUT_PULLUP);
  pinMode(button6Pin, INPUT_PULLUP);
  pinMode(button7Pin, INPUT_PULLUP);
  pinMode(button8Pin, INPUT_PULLUP);
  pinMode(button9Pin, INPUT_PULLUP);
  pinMode(button10Pin, INPUT_PULLUP);
  pinMode(confirmButtonPin, INPUT_PULLUP);
  wdt_disable();
  delay(200);
  lcd.clear();
}

void loop() {
  buttonRead();
  Serial.println("currentState=" + String(currentState));
  switch (currentState)
  {
    case MAIN_MENU:
      //      lcd.begin(16, 2);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcom to ");
      lcd.setCursor(0, 1);
      lcd.print("XYZ Bank..");
      player.volume(30);
      player.play(11);
      ForAlphbets();
      ReceivedString = "Welcome to XYZ Bank";
      for (int i = 0; i < ReceivedString.length(); i++)
      {
        char currentChar = ReceivedString.charAt(i);
        convertToBraille(currentChar);
      }
      delay(500);
      currentState = FACE_CHECK;
      break;

    case FACE_CHECK:
      lcd.begin(16, 2);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Waiting For Face..");
      player.volume(30);
      player.play(12);
      ForAlphbets();
      ReceivedString = "Waiting For Face";
      for (int i = 0; i < ReceivedString.length(); i++)
      {
        currentChar = ReceivedString.charAt(i);
        convertToBraille(currentChar);
      }
      while (!Serial.available() > 0);
      while (Serial.available() > 0)
      {
        f_data = Serial.read();
        Serial.print(f_data);

        if (pre_data != f_data)
        {
          Serial.println("storing into pre_data");
          pre_data = f_data;

          Serial.println(pre_data);

          switch (pre_data)
          {
            case 'A' :
              //              lcd.begin(16, 2);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("FACE ID:1");
              Serial.println("FACE ID:1");
              delay(500);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("User Name:");
              currentName = names[0];
              Namelength = strlen(currentName);
              lcd.setCursor(0, 1);
              for (int i = 0; i < Namelength; i++)
              {
                lcd.print(currentName[i]);
              }
              player.volume(30);
              player.play(13);
              ForAlphbets();
              for (int i = 0; i < 20; i++)
              {
                currentChar = names[0][i];
                convertToBraille(currentChar);
              }
              delay(500);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Account Number:");
              currentNumber = accountNumbers[0];
              Numberlength = strlen(currentNumber);
              lcd.setCursor(0, 1);
              for (int i = 0; i < Numberlength; i++)
              {
                lcd.print(currentNumber[i]);
              }

              ForNumbers();
              for (int i = 0; i < Numberlength; i++)
              {
                currentChar = accountNumbers[0][i];
                convertToBraille(currentChar);
                IntDigit = currentChar - '0';
                delay(300);
                audio(IntDigit);

              }
              currentCard = 0;
              f_data, pre_data = 'X';
              currentState = ATM_PIN;
              break;
            case 'B' :
              //              lcd.begin(16, 2);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("FACE ID:2");
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("User Name:");
              currentName = names[1];
              Namelength = strlen(currentName);
              lcd.setCursor(0, 1);
              for (int i = 0; i < Namelength; i++)
              {
                lcd.print(currentName[i]);
              }
              player.volume(30);
              player.play(14);
              ForAlphbets();
              for (int i = 0; i < Namelength; i++)
              {
                currentChar = names[1][i];
                convertToBraille(currentChar);
              }
              delay(500);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Account Number:");
              currentNumber = accountNumbers[1];
              Numberlength = strlen(currentNumber);
              lcd.setCursor(0, 1);
              for (int i = 0; i < Numberlength; i++)
              {
                lcd.print(currentNumber[i]);
              }
              ForNumbers();
              for (int i = 0; i < Numberlength; i++)
              {
                currentChar = accountNumbers[1][i];
                convertToBraille(currentChar);
                IntDigit = currentChar - '0';
                delay(300);
                audio(IntDigit);
              }
              currentCard = 1;
              f_data, pre_data = 'X';
              currentState = ATM_PIN;
              break;
          }
        }
      }
      break;
    case ATM_PIN:
      Serial.println("currentCard = " + String(currentCard));
      //      lcd.begin(16, 2);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("1.ENTER ATM PIN");
      player.volume(30);
      player.play(15);

      ForNumbers();
      ReceivedString = "1.";
      for (int i = 0; i < ReceivedString.length(); i++)
      {
        char currentChar = ReceivedString.charAt(i);
        convertToBraille(currentChar);
      }
      ForAlphbets();
      ReceivedString = "ENTER ATM PIN";
      for (int i = 0; i < ReceivedString.length(); i++)
      {
        char currentChar = ReceivedString.charAt(i);
        convertToBraille(currentChar);
      }
      while (Option == 'x') {
        Serial.println("Entered while");
        buttonRead();
        if (!btn1State || !btn2State || !btn3State || !btn4State || !btn5State || !btn6State || !btn7State || !btn8State || !btn9State || !btn10State) {
          Serial.println("all state");
          Option = buttonToNumber(btn1State, btn2State, btn3State, btn4State, btn5State, btn6State, btn7State, btn8State, btn9State, btn10State);
          Serial.println(Option);
          delay(1000);
        }
      }
      if (Option != ' ')
      {
        switch (Option)
        {
          case '1':
            Option = 'x';
            lcd.clear();
            player.volume(30);
            player.play(16);
            currentState = ENTER_ATM_PIN;
            break;
          case '2':
            Option = 'x';
            break;
        }
      }
      break;

    case ENTER_ATM_PIN:
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print("ENTER PIN:");
      if (!btn1State || !btn2State || !btn3State || !btn4State || !btn5State || !btn6State || !btn7State || !btn8State || !btn9State || !btn10State) {
        while (brailleIndex < 4) {
          buttonRead();
          Atm_Pin = buttonToNumber(btn1State, btn2State, btn3State, btn4State, btn5State, btn6State, btn7State, btn8State, btn9State, btn10State);
          if (Atm_Pin != 'x') {
            brailleInput[brailleIndex] = Atm_Pin;
            lcd.setCursor(brailleIndex, 1);
            lcd.print(brailleInput[brailleIndex]);
            brailleIndex++;
            delay(2000);
            convertToBraille(Atm_Pin);
//            IntDigit = Atm_Pin - '0';
//            audio(IntDigit);
            delay(500);
          }
          Atm_Pin = 'x';
        }
      }
      Serial.print("brailleInput=" + String(brailleInput[0]));
      if (brailleInput[0] != '\0') {
        for (int i = 0; i < strlen(brailleInput); i++)
        {
          PresentChar = brailleInput[i];
          //          convertToBraille(PresentChar);
          IntDigit = PresentChar - '0';
          Serial.println("IntDigit=" + String(IntDigit));
          //          audio(IntDigit);
          delay(500);
        }
      }

      if (brailleIndex >= 4)
      {
        brailleInput[4] = '\0';
        int result = strcmp(AtmPin[currentCard], brailleInput);
        Serial.println("result=" + String(result));
        if (result == 0)
        {
          //          lcd.begin(16, 2);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("PASSWROD MATCHED");
          player.volume(30);
          player.play(17);
          delay(1000);
          brailleIndex = 0;
          brailleclear();
          delay(2000);
          currentState = AMOUNT;
          Serial.println("currentState=" + String(currentState));
        }
        else
        {
          //          lcd.begin(16, 2);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("WRONG PASSWORD");
          Serial.println("WRONG");
          delay(500);
          player.volume(30);
          player.play(18);
          brailleIndex = 0;
          delay(500);
          lcd.clear();
          brailleclear();
          currentState = ATM_PIN;
        }
      }
      break;
  }
  switch (currentState)
  {
    case AMOUNT:
      //      lcd.begin(16, 2);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("1.BALANCE");
      lcd.setCursor(9, 0);
      lcd.print("3.EXIT");
      lcd.setCursor(0, 1);
      lcd.print("2.WITHDRAWAL");
      player.volume(30);
      player.play(19);
      AmountServo();
      while (Option == 'x') {
        Serial.println("Entered while");
        buttonRead();
        if (!btn1State || !btn2State || !btn3State || !btn4State || !btn5State || !btn6State || !btn7State || !btn8State || !btn9State || !btn10State) {
          Serial.println("all state");
          Option = buttonToNumber(btn1State, btn2State, btn3State, btn4State, btn5State, btn6State, btn7State, btn8State, btn9State, btn10State);
          if (Option != 'x')
          {
            IntDigit = Option - '0';
            delay(300);
            audio(IntDigit);
            delay(300);
          }
          Serial.println(Option);
          delay(1000);
        }
      }
      delay(1000);
      Serial.println("OPTION:" + String(Option));
      switch (Option)
      {
        case '1':
          Option = 'x';
          lcd.clear();
          currentState = BALANCE_ENQUIRY;
          break;
        case '2':
          Option = 'x';
          lcd.clear();
          currentState = WITH_DRAWAL;
          break;
        case '3':
          Option = 'x';
          lcd.clear();
          currentState = MAIN_MENU;
          break;
      }
      break;

    case BALANCE_ENQUIRY:
      //      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print("Balance: $");
      lcd.setCursor(0, 1);
      lcd.print(accountBalances[currentCard]);
      NumberString = String(accountBalances[currentCard]);
      for (int i = 0; i < NumberString.length(); i++)
      {
        digitChar = NumberString.charAt(i);
        digit = digitChar - '0';
        delay(300);
//        audio(digit);
//        delay(300);
        convertToBraille(digitChar);
      }
      brailleclear();
      delay(500);
      currentState = AMOUNT;
      break;
  }
  switch (currentState)
  {
    case WITH_DRAWAL:
      Serial.println("WITH_DRAWAL");
      //      lcd.begin(16, 2);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ENTER AMOUNT:");
      player.volume(30);
      player.play(20);
      delay(200);
      int withdrawalAmount = 0;
      bool confirmed = false;
      char amountInput[3] = "";
      int digitIndex = 0;
      brailleclear();
      if (!btn1State || !btn2State || !btn3State || !btn4State || !btn5State || !btn6State || !btn7State || !btn8State || !btn9State || !btn10State) {
        while (digitalRead(confirmButtonPin) == HIGH)
        {
          buttonRead();
          char Amount = buttonToNumber(btn1State, btn2State, btn3State, btn4State, btn5State, btn6State, btn7State, btn8State, btn9State, btn10State);
          if (Amount != 'x') {
            brailleInput[brailleIndex] = Amount;
            lcd.setCursor(brailleIndex, 1);
            lcd.print(brailleInput[brailleIndex]);
            brailleIndex++;
            delay(500);
            IntDigit = Amount - '0';
            delay(300);
            audio(IntDigit);
            delay(300);
            convertToBraille(Amount);
          }
          Amount = 'x';
        }
      }
      for (int i = 0; i < strlen(brailleInput) - 2; i++)
      {
        PresentChar = brailleInput[i];
        lastbraile[index++] = brailleInput[i];
        Serial.println("PresentChar" + String(PresentChar));
        IntDigit = PresentChar - '0';
        delay(100);
        audio(IntDigit);
        delay(300);
        convertToBraille(PresentChar);
      }
      Serial.println("confirmState value:" + String(confirmState));
      if (!confirmState) {
        confirmed = true;
        lcd.clear();
        delay(20);
      }
      if (confirmed) {
        Serial.println("confirmState");
        withdrawalAmount = atoi(lastbraile);
        Serial.println("withdrawalAmount" + String(withdrawalAmount));
        newBalance = accountBalances[currentCard] - withdrawalAmount;
        accountBalances[currentCard] = newBalance;
        NumberString = String(accountBalances[currentCard]);
        brailleclear();
        Serial.println("NewBalance = " + String(newBalance));
        lcd.begin(16, 2);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("BALANCE:");
        lcd.setCursor(0, 1);
        lcd.print(String(newBalance));
        for (int i = 0; i < NumberString.length(); i++)
        {
          digitChar = NumberString.charAt(i);
          digit = digitChar - '0';
//          delay(100);
//          audio(digit);
          delay(300);
          convertToBraille(digitChar);
        }
        delay(1000);
        player.volume(30);
        player.play(21);
        delay(6000);
        lcd.clear();
        brailleclear();
        player.volume(30);
        player.play(22);
        delay(2000);
        wdt_enable(WDTO_1S);
        confirmed = false;
        flag = true;
        return;
      }
      if (brailleIndex == 4)
      {
        lcd.clear();
        brailleIndex = 0;
      }
      if (flag == true)
      {
        brailleclear();
        currentState = MAIN_MENU;
      }
      break;
      brailleclear();
  }
  delay(300);
}



void AmountServo()
{
  ForNumbers();
  ReceivedString = "1.";
  for (int i = 0; i < ReceivedString.length(); i++)
  {
    char currentChar = ReceivedString.charAt(i);
    convertToBraille(currentChar);
  }
  ForAlphbets();
  ReceivedString = "BALANCE";
  for (int i = 0; i < ReceivedString.length(); i++)
  {
    char currentChar = ReceivedString.charAt(i);
    convertToBraille(currentChar);
  }


  ForNumbers();
  ReceivedString = "2.";
  for (int i = 0; i < ReceivedString.length(); i++)
  {
    char currentChar = ReceivedString.charAt(i);
    convertToBraille(currentChar);
  }
  ForAlphbets();
  ReceivedString = "WITHDRAWAL";
  for (int i = 0; i < ReceivedString.length(); i++)
  {
    char currentChar = ReceivedString.charAt(i);
    convertToBraille(currentChar);
  }
}

void buttonRead()
{
  btn1State = digitalRead(button1Pin);
  Serial.println("btn1State" + String(btn1State));
  btn2State = digitalRead(button2Pin);
  Serial.println("btn2State" + String(btn2State));
  btn3State = digitalRead(button3Pin);
  Serial.println("btn3State" + String(btn3State));
  btn4State = digitalRead(button4Pin);
  Serial.println("btn4State" + String(btn4State));
  btn5State = digitalRead(button5Pin);
  Serial.println("btn5State" + String(btn5State));
  btn6State = digitalRead(button6Pin);
  Serial.println("btn6State" + String(btn6State));
  btn7State = digitalRead(button7Pin);
  Serial.println("btn7State" + String(btn7State));
  btn8State = digitalRead(button8Pin);
  Serial.println("btn8State" + String(btn8State));
  btn9State = digitalRead(button9Pin);
  Serial.println("btn9State" + String(btn9State));
  btn10State = digitalRead(button10Pin);
  Serial.println("btn10State" + String(btn10State));
  confirmState = digitalRead(confirmButtonPin);
  Serial.println("confirmState" + String(confirmState));
}
void brailleclear()
{
  for (int i = 0; i < strlen(brailleInput); i++)
  {
    brailleInput[i] = '\0';
  }
}

void audio(int data)
{
  switch (data)
  {
    case 0:
      player.volume(30);
      player.play(1);
      delay(250);
      break;

    case 1:
      player.volume(30);
      player.play(2);
      delay(250);
      break;

    case 2:
      player.volume(30);
      player.play(3);
      delay(250);
      break;

    case 3:
      player.volume(30);
      player.play(4);
      delay(250);
      break;

    case 4:
      player.volume(30);
      player.play(5);
      delay(250);
      break;

    case 5:
      player.volume(30);
      player.play(6);
      delay(250);
      break;

    case 6:
      player.volume(30);
      player.play(7);
      delay(250);
      break;

    case 7:
      player.volume(30);
      player.play(8);
      delay(250);
      break;

    case 8:
      player.volume(30);
      player.play(9);
      delay(250);
      break;
    case 9:
      player.volume(30);
      player.play(10);
      delay(250);
      break;
  }
}
