#include "Calculator.h"

#include <math.h>
#include <UTFT.h> 

Calculator::Calculator(UTFT myGLCD)
{
  this->myGLCD = myGLCD;
  this->inputKeystroke = KEY_CLEAR;	
  this->inputType = C_CLEAR;
  this->calculatorState = CALC_CLEAR;
  for (int i=0;i<=9;i++)
  {
    this->value[i]=0;
    this->digits[i] = 0;
  }
  this->operandno = 0;
  this->outputRow = 2;
  this->theOperator = KEY_PLUS;
}
unsigned long Calculator::retrieveOperand()
{
  return this->value[this->operandno];
}
int Calculator::getDigits()
{
  return this->digits[this->operandno];
}
void Calculator::putKeystroke(int intKeystroke)
{
  // Save the Keystroke
  this->inputKeystroke = intKeystroke;



  // What kind of key was pressed?
  if (intKeystroke >= KEY_ZERO && intKeystroke <= KEY_NINE)
  {
      int digits;
      unsigned long value1;
      value1 = this->value[this->operandno];
      value1 *= 10;
      value1 += intKeystroke;
      digits = this->digits[this->operandno];
      digits += 1;
      this->digits[this->operandno] = digits;
      this->value[this->operandno] = value1;
      this->inputType = C_NUMBER;
  }
  else if (intKeystroke == KEY_PLUS || intKeystroke == KEY_MINUS || intKeystroke == KEY_DIVIDE || intKeystroke == KEY_MULTIPLY)
  {
    this->operandno++;
    this->outputRow += 1;
    this->theOperator = intKeystroke;
    this->inputType = C_OPERATOR;
  }
  else if (intKeystroke == KEY_PLUSMINUS || intKeystroke == KEY_SQUAREROOT)
  {
    this->inputType = C_UNARY;
  }
  else if (intKeystroke == KEY_DECIMALPOINT)
  {
    this->inputType = C_DECIMALPOINT;
  }
  else if (intKeystroke == KEY_EQUAL)
  {
    int operandno;
    operandno = this->operandno;
    operandno++;
    this->outputRow += 1;
    unsigned long oneback = this->value[operandno - 1];
    unsigned long twoback = this->value[operandno - 2];
    unsigned long result;
    int theOperator;
    theOperator = this->theOperator;
    if (theOperator == KEY_PLUS)
    {
      result = twoback + oneback;
    }
    else if (theOperator == KEY_MINUS)
    {
      result = twoback - oneback;
    }
    else if (theOperator == KEY_MULTIPLY)
    {
      result = twoback * oneback;
    }
    else if (theOperator == KEY_DIVIDE)
    {
      result = twoback / oneback;
    }
    this->value[operandno] = result;
    this->digits[operandno] = 1 + int(log10(result));
    this->operandno = operandno;
    this->outputRow += 1;
    this->inputType = C_EQUAL;
  }
  else if (intKeystroke == KEY_CLEAR)
  {
    for (int i = 0; i<=9; i++)
    {
       this->value[i] = 0;
       this->digits[i] = 0;
    }
    this->operandno = 0;
    this->outputRow = 2;
    this->inputType = C_CLEAR;
  }
  else
  {
    // toggle led
  }
  // Determine the current system state
  if (this->calculatorState == CALC_CLEAR)
  {
    if (this->inputType == C_NUMBER)
    {
      this->calculatorState = CALC_INTEGER;
    }
    else
    {
      this->calculatorState = CALC_CLEAR;
    }
  }
  else if (this->calculatorState == CALC_INTEGER)
  {
    if (this->inputType == C_NUMBER)
    {
      this->calculatorState = CALC_INTEGER;
    }
    else if (this->inputType == C_DECIMALPOINT)
    {
      this->calculatorState = CALC_DECIMAL;
    }
    else if (this->inputType == C_OPERATOR)
    {
      this->calculatorState == CALC_SECOND;  // Ready for entry of second operand.
    }

    else if (this->inputType == C_EQUAL)
    {
      this->calculatorState = C_EQUAL;
    }
    else
    {
      this->calculatorState = CALC_CLEAR;
    }
  }
  else if (this->calculatorState = CALC_DECIMAL)
  {
    if (this->inputType == C_NUMBER)
    {
      this->calculatorState = CALC_DECIMAL;
    }
    else if (this->inputType == C_DECIMALPOINT)
    {
      this->calculatorState = CALC_DECIMAL;  // It remains CALC DECIMAL
    }
    else if (this->inputType == C_DECIMALPOINT)
    {
      this->calculatorState = CALC_DECIMAL;
    }
    else if (this-inputType == C_OPERATOR)
    {
      this->calculatorState = CALC_SECOND;
//      this->operandNo += 1;
    }
    else if (this->inputType == C_EQUAL)
    {
      this->calculatorState = C_EQUAL;
    }
    else
    {
      this->calculatorState = CALC_CLEAR;
    }
  }
  else if (this->calculatorState == CALC_SECOND)
  {
    if (this->inputType == C_NUMBER)
    {
      this->calculatorState = CALC_INTEGER;
    }
    else
    {
      this->calculatorState = CALC_CLEAR;
    }
  }
  else if (this->calculatorState == CALC_EQUAL)
  {
     this->calculatorState = CALC_CLEAR; 
  }
  else
  {
     this->calculatorState = CALC_CLEAR;
  }    
}
int Calculator::getCalculatorState()
{
  return this->calculatorState;
}
int Calculator::getInputType()
{
  return this->inputType;
}
void Calculator::setInputType(int theType)
{
  this->inputType = theType;
}
int Calculator::getKeystroke()
{
  return this->inputKeystroke;
}
void Calculator::clearCalculator()
{
  this->operand1 = 0;
  this->place = 1;
  this->inputKeystroke = 0;
  this->operandno = 0;
  for (int i=0;i<=9;i++)
  {
    this->digits[i] = 0;
    this->value[i] = 0;
  }
  this->operandno = 0;
  this->outputRow = 2;
}
int Calculator::getOperandNo()
{
  return this->operandno;
}
void Calculator::displayOperand(int operandno,int row, int col,UTFT *lcd)
{
        char zeroPlace;
        char onesPlace;
        char twosPlace;
        char currentPlace;
        int theDigitValue;
        unsigned long tens;
        int xpos = col;
        int ypos = row;
        unsigned long operand;
        int digits;
        uint16_t theChar[16];


        operand = this->value[operandno];
          
        digits = this->digits[operandno];
        
        while (digits > 0)
        {
          theDigitValue = operand - int(operand / 10) * 10;
          
          currentPlace = '0' + theDigitValue;
          this->getLargeChar(currentPlace,theChar);
          myGLCD.printLarge(theChar,ypos*20,xpos * 20,0);
          xpos -= 1;

          operand = int(operand / 10);
          digits -= 1;
        }

}
void Calculator::getLargeChar(char currentKey,uint16_t theChar)
{
    uint16_t *ptr;
    int b;

    if (currentKey == 'Q')
    {
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = *(squareroot+k);    
      }
    }
    else if (currentKey == 'S')
    {
      b = 0;
    
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = pgm_read_word(largeFont + (b*0x10)+k);    
      }      
    }
    else if (currentKey == 'P')
    {
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = *(plusminus+k);    
      }
    }
    else if (currentKey == 'C' || currentKey == '=' || currentKey == '.')
    {
      b = currentKey - 0x20 - 2;
    
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = pgm_read_word(largeFont + (b*0x10)+k);    
      }      
    }
    else
    {
      b = currentKey - 0x20;
    
      ptr = theChar;
      for (int k=0;k<16;k++)
      {
        *ptr++ = pgm_read_word(largeFont + (b*0x10)+k);    
      }
    }
}
int Calculator::getOutputRow()
{
      return this->outputRow;
}
void Calculator::setOutputRow(int row)
{
      this->outputRow = row;
}
