/////////////////////////////////////Include libraries/////////////////////////////////////
#include <Servo.h> 
///////////////////////////////////////Define servos///////////////////////////////////////
Servo myservo_1; // left/right
Servo myservo_2; // up/down
Servo myservo_3; // A/Y
Servo myservo_4; // B/X
Servo myservo_5; // SR/WT - TODO
////////////////////////////////////Define comm. params////////////////////////////////////
#define BAUD 9600
//////////////////////////////////Set positions for arrows/////////////////////////////////
#define LEFT_MAX 80
#define RIGHT_MAX 100
#define UP_MAX 80
#define DOWN_MAX 100
#define ARROW_RELEASE 100
#define PRE_PRESS 200
/////////////////////////////////Set positions for buttons/////////////////////////////////
#define Y_MAX 80
#define A_MAX 100
#define B_MAX 80
#define X_MAX 100
#define BUTTON_OFF 90
#define BUTTON_RELEASE 120
#define BACK_OFF 5
///////////////////////Set positions for Soft Reset and Wonder Trade///////////////////////
#define SOFT_RESET_MAX 80  
#define SOFT_RESET_OFF 90   
#define WONDER_TRADE_MAX 100
////////////////////////////////////Set params for LDR/////////////////////////////////////
#define LDR 0 
#define LIGHT_CUT_OFF 150
////////////////////////////////Variables handling LDR info////////////////////////////////
int v1 = 0;
char b1;
char char_out;
//////////////////////////////////////////Setup////////////////////////////////////////////
void setup()
{
  Serial.begin(BAUD);
  myservo_1.attach(7);
  myservo_2.attach(8);
  myservo_3.attach(3);
  myservo_4.attach(2);
  myservo_5.attach(6);
//  pinMode(LDR, INPUT);

  myservo_1.write(BUTTON_OFF); 
  myservo_2.write(BUTTON_OFF); 
  myservo_3.write(BUTTON_OFF);
  myservo_4.write(BUTTON_OFF);
  myservo_5.write(BUTTON_OFF);

//  pinMode(LED_BUILTIN, OUTPUT);
}
/////////////////////////////////////////Legend////////////////////////////////////////////
/*  - Line Feed - 10 - All buttons un-pressed
    - B - 66  -  Take LDR reading send L/H info
    - C - 67  - Take LDR reading and send first byte
    - 8 - 56  - Press and hold up  
    - e - 101 - Press and release up
    - 4 - 52  - Press and hold left
    - s - 115 - Press and release left 
    - 2 - 50  - Press and hold down
    - d - 100 - Press and release down  
    - 6 - 54  - Press and hold right
    - f - 102 - Press and release right  
    - y - 121 - Press Y  
    - b - 98  - Press B
    - a - 97  - Press A
    - x - 120 - Press X
    - S - 83  - Soft Reset
    - W - 87  - Wonder trade
    - 0 - 48  - All buttons un-pressed */
//////////////////////////////////////Infinite Loop////////////////////////////////////////
void loop()
{
     String input;
     if (Serial.available() > 0)
     {   
         input = Serial.readStringUntil('\n');

         if(!input.equals("10"))
             unPressAllButtons();  

          if (input.equals("B")){
            takeReadingAndSendInfo_LDR();
          } else if (input.equals("C")) {
            takeReadingAndSendFirstByte_LDR();
          } else if (input.equals("8")) {
             holdArrow_up();
          } else if (input.equals("e")) {
            pressArrow_up();
          } else if (input.equals("4")) {
            holdArrow_left();
          } else if (input.equals("s")) {
            pressArrow_left();
          } else if (input.equals("2")) {
            holdArrow_down();
          } else if (input.equals("d")) {
            pressArrow_down();
          } else if (input.equals("6")) {
            holdArrow_right();
          } else if (input.equals("f")) {
            pressArrow_right();
          } else if (input.equals("y")) {
            pressBtn_Y();
          } else if (input.equals("b")) {
            pressBtn_B();
          } else if (input.equals("a")) {
            pressBtn_A();
          } else if (input.equals("x")) {
            pressBtn_X();
          } else if (input.equals("S")) {
            softReset();
          } else if (input.equals("W")) {
            wonderTrade();
          } else if (input.equals("0")) {
            unPressAllButtons();
          } 
     }
}
/////////////////////////////////////When sending data/////////////////////////////////////
//void serialEvent()
// {
//     String input;
//     if (Serial.available() > 0)
//     {   
//         input = Serial.readStringUntil('\n');
//
//         if(!input.equals("10"))
//             unPressAllButtons();  
//
//          if (input.equals("B")){
//            takeReadingAndSendInfo_LDR();
//          } else if (input.equals("C")) {
//            takeReadingAndSendFirstByte_LDR();
//          } else if (input.equals("8")) {
//             holdArrow_up();
//          } else if (input.equals("e")) {
//            pressArrow_up();
//          } else if (input.equals("4")) {
//            holdArrow_left();
//          } else if (input.equals("s")) {
//            pressArrow_left();
//          } else if (input.equals("2")) {
//            holdArrow_down();
//          } else if (input.equals("d")) {
//            pressArrow_down();
//          } else if (input.equals("6")) {
//            holdArrow_right();
//          } else if (input.equals("f")) {
//            pressArrow_right();
//          } else if (input.equals("y")) {
//            pressBtn_Y();
//          } else if (input.equals("b")) {
//            pressBtn_B();
//          } else if (input.equals("a")) {
//            pressBtn_A();
//          } else if (input.equals("x")) {
//            pressBtn_X();
//          } else if (input.equals("S")) {
//            softReset();
//          } else if (input.equals("W")) {
//            wonderTrade();
//          } else if (input.equals("0")) {
//            unPressAllButtons();
//          } 
//     }
// }
/////////////////////////////////////Custom Functions//////////////////////////////////////
///////////////////////////////////Un-press all buttons////////////////////////////////////
void unPressAllButtons()
{
  myservo_1.write(BUTTON_OFF); 
  myservo_2.write(BUTTON_OFF); 
  myservo_3.write(BUTTON_OFF);
  myservo_4.write(BUTTON_OFF);
  myservo_5.write(BUTTON_OFF);
}
///////////////////////////////////////Wonder Trade////////////////////////////////////////
void wonderTrade()
{
  myservo_5.write(WONDER_TRADE_MAX);
  delay(250);
  myservo_5.write(SOFT_RESET_OFF); 
}
////////////////////////////////////////Soft Reset/////////////////////////////////////////
void softReset()
{
  myservo_5.write(SOFT_RESET_MAX);
  delay(250);
  myservo_5.write(SOFT_RESET_OFF); 
}
/////////////////////////////////////////Press X///////////////////////////////////////////
void pressBtn_X()
{
  myservo_4.write(X_MAX);
  delay(BUTTON_RELEASE);
  myservo_4.write(BUTTON_OFF); 
}
/////////////////////////////////////////Press A///////////////////////////////////////////
void pressBtn_A()
{
  myservo_3.write(A_MAX);
  delay(BUTTON_RELEASE);
  myservo_3.write(BUTTON_OFF);
}
/////////////////////////////////////////Press B///////////////////////////////////////////
void pressBtn_B()
{
  myservo_4.write(B_MAX);
  delay(BUTTON_RELEASE);
  myservo_4.write(BUTTON_OFF);  
}
/////////////////////////////////////////Press Y///////////////////////////////////////////
void pressBtn_Y()
{
  myservo_3.write(Y_MAX);
  delay(BUTTON_RELEASE);
  myservo_3.write(BUTTON_OFF);
}
///////////////////////////////////////Press Right/////////////////////////////////////////
void pressArrow_right()
{
  myservo_1.write(RIGHT_MAX);
  delay(ARROW_RELEASE);
  myservo_1.write(BUTTON_OFF);
}
////////////////////////////////////////Hold Right/////////////////////////////////////////
void holdArrow_right()
{
  myservo_1.write(RIGHT_MAX);
  delay(PRE_PRESS); 
  myservo_1.write(RIGHT_MAX - BACK_OFF); 
}
////////////////////////////////////////Press Down/////////////////////////////////////////
void pressArrow_down()
{
  myservo_2.write(DOWN_MAX);
  delay(ARROW_RELEASE);
  myservo_2.write(BUTTON_OFF);
}
/////////////////////////////////////////Hold Down/////////////////////////////////////////
void holdArrow_down()
{
  myservo_2.write(DOWN_MAX);
  delay(PRE_PRESS);
  myservo_2.write(DOWN_MAX - BACK_OFF);
}
////////////////////////////////////////Press Left/////////////////////////////////////////
void pressArrow_left()
{
  myservo_1.write(LEFT_MAX);
  delay(ARROW_RELEASE);
  myservo_1.write(BUTTON_OFF);
}
/////////////////////////////////////////Hold Left/////////////////////////////////////////
void holdArrow_left()
{
  myservo_1.write(LEFT_MAX);
  delay(PRE_PRESS);
  myservo_1.write(LEFT_MAX + BACK_OFF); 
}
/////////////////////////////////////////Press Up//////////////////////////////////////////
void pressArrow_up()
{
    myservo_2.write(UP_MAX);
    delay(ARROW_RELEASE);
    myservo_2.write(BUTTON_OFF);
}
//////////////////////////////////////////Hold Up//////////////////////////////////////////
void holdArrow_up()
{
  myservo_2.write(UP_MAX);
  delay(PRE_PRESS);
  myservo_2.write(UP_MAX + BACK_OFF);
}
///////////////////////////Take LDR reading and send first byte////////////////////////////
void takeReadingAndSendFirstByte_LDR()
{
  v1 = analogRead(LDR); 
  delay(10); 
  b1 = (v1 / 4);
  Serial.print(b1);
}
////////////////////////////Take LDR reading and send L/H info/////////////////////////////
void takeReadingAndSendInfo_LDR()
{
  v1 = analogRead(LDR);        
  if (v1 < LIGHT_CUT_OFF) {
      char_out = 76; // 'L'
      Serial.print(char_out);  
  } else {
      char_out = 72; // 'H'
      Serial.print(char_out);
  }
}
///////////////////////////////////////////END/////////////////////////////////////////////
