#ifndef BUTTON_H
#define BUTTON_H

#include "global.h"
char buttonToNumber(int btn1, int btn2, int btn3, int btn4, int btn5, int btn6, int btn7, int btn8, int btn9, int btn10) {
  if (!btn1) return '1';
  if (!btn2) return '2';
  if (!btn3) return '3';
  if (!btn4) return '4';
  if (!btn5) return '5';
  if (!btn6) return '6';
  if (!btn7) return '7';
  if (!btn8) return '8';
  if (!btn9) return '9';
  if (!btn10) return '0';
  return 'x';
}

#endif
