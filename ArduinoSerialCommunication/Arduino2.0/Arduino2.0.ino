#include <Servo.h> 
Servo myservo_1; // left/right
//Servo myservo_2; // up/down
//Servo myservo_3; // A/Y
//Servo myservo_4; // B/X
//Servo myservo_5; // SR/WT - TODO!!!
// Default baud speed for communication
#define BAUD 9600

// Set positions for left and right buttons
#define leftMax 80
#define rightMax 100
// Set positions for up and down buttons
#define upMax 80
#define downMax 100
// Set positions for A and Y buttons
#define YMax 80
#define AMax 100
// Set positions for B and X buttons
#define BMax 80
#define XMax 100
// Position for all button
#define buttonOff 90
// Set positions for Soft Reset
#define SRMax 80 // On 3dsXL increase this value to soft reset.
                 // On the standard 3ds decrease this value to soft reset.
#define SROff 90 // On 3dsXL decrease this to lift the soft reset rod away
                 // from the 3dsXL. On the standard 3ds the servo motor is
                 // the opposite orientation therefore increase this to left it away from the 3ds.
#define backOff 5
#define arrowRelease 100
#define buttonRelease 120

#define prePress 200
#define lightCutoff 150
// Pin assignment for LDR
#define LDR 0
int v1 = 0;
char b1;
char char_out;

void setup(){
  Serial.begin(BAUD);
  myservo_1.attach(7);
//  myservo_2.attach(8);
//  myservo_3.attach(3);
//  myservo_4.attach(2);
//  myservo_5.attach(6);
//  pinMode(LDR, INPUT);

  myservo_1.write(buttonOff); 
//  myservo_2.write(buttonOff); 
//  myservo_3.write(buttonOff);
//  myservo_4.write(buttonOff);
//  myservo_5.write(buttonOff);
}

/* Legend: 
 *  - Line Feed - 10 - All buttons un-pressed
 *  - B - 66  -  Take LDR reading send L/H info
 *  - C - 67  - Take LDR reading and send first byte
 *  - 8 - 56  - Press and hold up  
 *  - e - 101 - Press and release up
 *  - 4 - 52  - Press and hold left
 *  - s - 115 - Press and release left 
 *  - 2 - 50  - Press and hold down
 *  - d - 100 - Press and release down  
 *  - 6 - 54  - Press and hold right
 *  - f - 102 - Press and release right  
 *  - y - 121 - Press Y  
 *  - b - 98  - Press B
 *  - a - 97  - Press A
 *  - x - 120 - Press X
 *  - S - 83  - Soft Reset
 *  - W - 87  - Wonder trade
 *  - 0 - 48  - All buttons un-pressed
*/

void loop(){
  int input;
  //If any input is detected in arduino
  if(Serial.available() > 0){
    //read 
    input = Serial.read();
    //If input == "4" then press and hold left
    if (input.equals("4"))
    {
      myservo_1.write(leftMax);
       delay(prePress);
       myservo_1.write(leftMax + backOff);  
    } 
    //If input == "0" then unpress
    else if (input.equals("0")){
      myservo_1.write(buttonOff); 
    }
  }
}


void serialEvent()
{
 if (Serial.available() > 0)
 {   
   int letter = Serial.read();
   // Serial.print(letter);

   // All buttons un-pressed
   if(letter != 10)
   {
       myservo_1.write(buttonOff); 
       myservo_2.write(buttonOff); 
       myservo_3.write(buttonOff);;
       myservo_4.write(buttonOff);
       myservo_5.write(buttonOff);
   }
   
   //delay(20);
   
   // Take LDR reading send L/H info
   if (letter == 66) // 'B'
   {
       v1 = analogRead(LDR);        
       if(v1 < lightCutoff)
       {
           char_out = 76; // 'L'
           Serial.print(char_out);  
       }
       else
       {
           char_out = 72; // 'H'
           Serial.print(char_out);
       }
   }
   
   // Take LDR reading and send first byte
   if (letter == 67) // 'C'
   {    
       v1 = analogRead(LDR); 
       delay(10); 
       b1 = (v1/4);
       Serial.print(b1);
   }
     
   // Press and hold up  
   if (letter == 56) // '8'
   {      
       holdArrow_up();
   }
    
   // Press and release up  
   if (letter == 101) // 'e'
   {
       pressArrow_up();
   }
   
   // Press and hold left
   if (letter == 52) // '4'
   {
       holdArrow_left();  
   }
     
   // Press and release left  
   if (letter == 115) // 's'
   {
       pressArrow_left();
   }
    
   // Press and hold down
   if (letter == 50) // '2'
   {
       holdArrow_down();
   }
     
   // Press and release down  
   if (letter == 100) // 'd'
   {
       pressArrow_down();
   }
   
   // Press and hold right
   if (letter == 54)// '6'
   {
      holdArrow_right(); 
   }
     
   // Press and release right  
   if (letter == 102) // 'f'
   {
       pressArrow_right();
   }
 
   // Press Y    
   if (letter == 121) // 'y'
   {
       pressBtn_Y();     
   }
   
   // Press B
   if (letter == 98) // 'b'
   {
       pressBtn_B(); 
   }
  
   // Press A   
   if (letter == 97) // 'a'
   {
       pressBtn_A();
   }
     
   // Press X
   if (letter == 120) // 'x'
   {
       pressBtn_X(); 
   }
     
   // Soft Reset
   if (letter == 83) // 'S'
   {
       softReset();
   }
 
   // Wonder trade
   if (letter == 87) // 'W'
   {
       wonderTrade();
   }
     
   // All buttons un-pressed
   if (letter == 48) // '0'
   {     
       unPressAllButtons();
   }
 }
}


void unPressAllButtons()
{
  myservo_1.write(buttonOff); 
  myservo_2.write(buttonOff); 
  myservo_3.write(buttonOff);
  myservo_4.write(buttonOff);
  myservo_5.write(buttonOff);
}

void wonderTrade()
{
  myservo_5.write(WMax);
  delay(250);
  myservo_5.write(SROff); 
}

void softReset()
{
  myservo_5.write(SRMax);
  delay(250);
  myservo_5.write(SROff); 
}

void pressBtn_X()
{
  myservo_4.write(XMax);
  delay(buttonRelease);
  myservo_4.write(buttonOff); 
}

void pressBtn_A()
{
  myservo_3.write(AMax);
  delay(buttonRelease);
  myservo_3.write(buttonOff);
}

void pressBtn_B()
{
  myservo_4.write(BMax);
  delay(buttonRelease);
  myservo_4.write(buttonOff);  
}

void pressBtn_Y()
{
  myservo_3.write(YMax);
  delay(buttonRelease);
  myservo_3.write(buttonOff);
}

void pressArrow_right()
{
  myservo_1.write(rightMax);
  delay(arrowRelease);
  myservo_1.write(buttonOff);
}

void holdArrow_right()
{
  myservo_1.write(rightMax);
  delay(prePress); 
  myservo_1.write(rightMax - backOff); 
}

void pressArrow_down()
{
  myservo_2.write(downMax);
  delay(arrowRelease);
  myservo_2.write(buttonOff);
}

void holdArrow_down()
{
  myservo_2.write(downMax);
  delay(prePress);
  myservo_2.write(downMax - backOff);
}

void pressArrow_left()
{
  myservo_1.write(leftMax);
  delay(arrowRelease);
  myservo_1.write(buttonOff);
}

void holdArrow_left()
{
  myservo_1.write(leftMax);
  delay(prePress);
  myservo_1.write(leftMax + backOff); 
}

void pressArrow_up()
{
    myservo_2.write(upMax);
    delay(arrowRelease);
    myservo_2.write(buttonOff);
}

void holdArrow_up()
{
  myservo_2.write(upMax);
  delay(prePress);
  myservo_2.write(upMax + backOff);
}

void takeReadingAndSendFirstByte_LDR()
{
  v1 = analogRead(LDR); 
  delay(10); 
  b1 = (v1 / 4);
  Serial.print(b1);
}