#include <Servo.h> 
Servo myservo_1; // left/right
//Servo myservo_2; // up/down
//Servo myservo_3; // A/Y
//Servo myservo_4; // B/X
//Servo myservo_5; // SR/WT - TODO!!!
// Default baud speed for communication
#define BAUD 9600
// Led 
#define led 13
// Macro for on/off
#define on (digitalWrite(led, HIGH))
#define off (digitalWrite(led, LOW))

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
#define SRMax 80 // on 3dsXL increase this value to soft reset. On the standard 3ds decrease this value to soft reset.
#define SROff 90 // on 3dsXL decrease this to lift the soft reset rod away from the 3dsXL. On the standard 3ds the servo motor is the opposite orientation therefore increase this to left it away from the 3ds.

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
  pinMode(led, OUTPUT);
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
  String input;
  //If any input is detected in arduino
  if(Serial.available() > 0){
    //read the whole string until '\n' delimiter is read
    input = Serial.readStringUntil('\n');
    //If input == "ON" then turn on the led 
    //and send a reply
    if (input.equals("ON")){
      digitalWrite(led, HIGH);
      Serial.println("Led is on");
    } 
    //If input == "OFF" then turn off the led 
    //and send a reply
    else if (input.equals("OFF")){
      digitalWrite(led, LOW);
      Serial.println("Led is off");
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
        myservo_3.write(buttonOff);
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
        myservo_2.write(upMax);
        delay(prePress);
        myservo_2.write(upMax + backOff);
    }
     
    // Press and release up  
    if (letter == 101) // 'e'
    {
        myservo_2.write(upMax);
        delay(arrowRelease);
        myservo_2.write(buttonOff);
    }
    
    // Press and hold left
    if (letter == 52) // '4'
    {
        myservo_1.write(leftMax);
        delay(prePress);
        myservo_1.write(leftMax + backOff);  
    }
      
    // Press and release left  
    if (letter == 115) // 's'
    {
        myservo_1.write(leftMax);
        delay(arrowRelease);
        myservo_1.write(buttonOff);
    }
     
    // Press and hold down
    if (letter == 50) // '2'
    {
        myservo_2.write(downMax);
        delay(prePress);
        myservo_2.write(downMax - backOff);
    }
      
    // Press and release down  
    if (letter == 100) // 'd'
    {
        myservo_2.write(downMax);
        delay(arrowRelease);
        myservo_2.write(buttonOff);
    }
    
    // Press and hold right
    if (letter == 54)// '6'
    {
       myservo_1.write(rightMax);
       delay(prePress); 
       myservo_1.write(rightMax - backOff); 
    }
      
    // Press and release right  
    if (letter == 102) // 'f'
    {
        myservo_1.write(rightMax);
        delay(arrowRelease);
        myservo_1.write(buttonOff);
    }
  
    // Press Y    
    if (letter == 121) // 'y'
    {
        myservo_3.write(YMax);
        delay(buttonRelease);
        myservo_3.write(buttonOff);     
    }
    
    // Press B
    if (letter == 98) // 'b'
    {
        myservo_4.write(BMax);
        delay(buttonRelease);
        myservo_4.write(buttonOff);   
    }
   
    // Press A   
    if (letter == 97) // 'a'
    {
        myservo_3.write(AMax);
        delay(buttonRelease);
        myservo_3.write(buttonOff);
    }
      
    // Press X
    if (letter == 120) // 'x'
    {
        myservo_4.write(XMax);
        delay(buttonRelease);
        myservo_4.write(buttonOff); 
    }
      
    // Soft Reset
    if (letter == 83) // 'S'
    {
        myservo_5.write(SRMax);
        delay(250);
        myservo_5.write(SROff); 
    }
  
    // Wonder trade
    if (letter == 87) // 'W'
    {
        myservo_5.write(WMax);
        delay(250);
        myservo_5.write(SROff); 
    }
      
    // All buttons un-pressed
    if (letter == 48) // '0'
    {     
        myservo_1.write(buttonOff); 
        myservo_2.write(buttonOff); 
        myservo_3.write(buttonOff);
        myservo_4.write(buttonOff);
        myservo_5.write(buttonOff);
    }
  }
}
