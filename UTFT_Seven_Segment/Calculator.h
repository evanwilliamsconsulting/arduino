#include <avr/pgmspace.h>
#include <UTFT.h>

const int KEY_ZERO=0;
const int KEY_ONE=1;
const int KEY_TWO=2;
const int KEY_THREE=3;
const int KEY_FOUR=4;;
const int KEY_FIVE=5;
const int KEY_SIX=6;
const int KEY_SEVEN=7;
const int KEY_EIGHT=8;
const int KEY_NINE=9;
const int KEY_CLEAR=10;
const int KEY_DECIMALPOINT=11;
const int KEY_SPACE=12;
const int KEY_SQUAREROOT=13;
const int KEY_PLUSMINUS=14;
const int KEY_DIVIDE=15;
const int KEY_MULTIPLY=16;
const int KEY_PLUS=17;
const int KEY_MINUS=18;
const int KEY_EQUAL=19;

const char keycodes[] = {'0','1','2','3','4','5','6','7','8','9','C','.','S','Q','P','/','*','+','-','='};


const int C_NUMBER = 0;
const int C_OPERATOR =1;
const int C_UNARY = 2;
const int C_SQUAREROOT = 3;
const int C_DECIMALPOINT = 4;
const int C_EQUAL = 5;
const int C_CLEAR= 6;

const int CALC_CLEAR = 0;
const int CALC_INTEGER = 1;
const int CALC_DECIMAL = 2;
const int CALC_SECOND = 3;
const int CALC_EQUAL = 4;

extern UTFT myGLCD;

class Calculator
{
   private:
    float operand1,operand2,result;
    int inputKeystroke;
    int inputType;
    int calculatorState;
    int digits[9];
    int place;
    unsigned long value[9];
    int operandno;
    int theOperator;
    int outputRow;
   public:
    Calculator();
    int getOutputRow();
    void setOutputRow(int row);
    int getOperandNo();
    void putKeystroke(int intKeystroke);
    float add();
    float subtract();
    float multiply();
    float divide();
    unsigned long retrieveOperand();
    int getDigits();
    void clearCalculator();
    int getCalculatorState();
     int getInputType();
     void setInputType(int theType);
    int getKeystroke();
    void displayOperand(int operandno,int row,int col,UTFT *lcd);
    void getLargeChar(char currentKey,uint16_t theChar);
};
