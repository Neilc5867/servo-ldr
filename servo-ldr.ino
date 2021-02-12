#include <Servo.h>

Servo myServo;
int eastPos=0;
int noonPos=255;
int westPos=1023;
int currPos=0;

int eastPin=A0;
int eastVal=0;
bool eastSun=false;

int westPin=A1;
int westVal=0;
bool westSun=false;

int ledPin=8;//'Safety' led


// consider tolerances for a sensor being 'activated'

void setup() {
  // put your setup code here, to run once:
  // no need to map the servo, can just do min-max.
  myServo.attach(9);  
  // signal pins for LDR's - east/west.
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  initServo();
  //init here - move the servo through entire range
  
  
}//end setup


void loop() {
  // put your main code here, to run repeatedly:
  int timeOfDay=eastPos;
  
  eastVal = analogRead(eastPin);
  Serial.print("East LDR: ");
  Serial.print(eastVal);
  //if logic for east.
  if(eastVal >= 150){
    eastSun=true;
  }//end if
  else{
    eastSun=false;
  }//end else
  //end if logic for east
  Serial.print("   ");
  Serial.println(eastSun);

  westVal = analogRead(westPin);
  Serial.print("West LDR: ");
  Serial.print(westVal);
  //if logic for west.
  if(westVal >=150){
    westSun=true;
  }//end if logic for west.
  else{
    westSun=false;
  }
  Serial.print("   ");
  Serial.println(westSun);

  //Do servo adjustments here
  timeOfDay = whatTime(eastVal, westVal);
  servoPos(timeOfDay);
  
  
  //delay so readings don't swamp the board & console
  delay(1000);
  Serial.println();

}//end loop

void initServo(){
  //message
  Serial.println("Initialising the servo & led...");
  //blink the led 
    digitalWrite(8, HIGH);
    delay(100);
    digitalWrite(8,LOW);

    delay(500);
    //move servo through all degrees
  int servoDeg;
  for(servoDeg=0; servoDeg>=180;servoDeg++){
    servoPos(servoDeg);
  }//end for
    delay(500);
  Serial.println("Done.");
  delay(5000);
  
}//end initServo

int whatTime(bool east, bool west){
  //just give back the above ints for ToD
  int currTime=eastPos;
  if(!eastSun && !westSun){
    //no east/west sun = night
    currTime=eastPos;
    myServo.read();
  }
  else if (eastSun && !westSun){
    //east sun, morning
    currTime=eastPos;
  }
  else if (eastSun && westSun){
    //both, noon
    currTime=noonPos;
  }
  else if(!eastSun && westSun){
    //west sun, afternoon
    currTime=westPos;
  }
  else{
    currTime=eastPos;
  }

  return currTime;
  //TODO

}//end whatTime

void servoPos(int pos){
  //light the LED while it's in motion
  
  //move the servo based on the time.
  digitalWrite(8, HIGH);
  myServo.write(pos);
  digitalWrite(8, LOW);
}//end servoPos

void faceEast(){
  //move servo fully on/off for a signal on East LDR
  //0
  
}//end faceEast

void noon(){
  //both LDR's doing stuff - it must be noon
  //512
}//end noon

void faceWest(){
  //move servo fully on/off for a signal on West LDR
  //1024
}//end faceWest

void night(){
  //servo goes back to east ready for morning sun 
  
}//end night
