/*

Code for KY-008 Laser and Laser Detector
by eLab Peers (C) 2014.

Visit us at:
http://www.elabpeers.com

All rights reserved.

Wiring:
1.  VCC to 5V on Arduino board
2.  GND to GND on Arduino board
3.  S on KY-008 Laser to Pin 6 on Arduino board
4.  OUT on Laser Dector to Pin 7 on Arduino board

*/

/****

KC: This is code from the KY-008 Laser and Laser Detector website: 
https://www.elabpeers.com/ky-008-laser-x-laser-detector.html

The following .c code will work and explains some of the rationale of the code in loop
//  int main(){
//  int count = 0;
//  int avg = 0;
//  while(1){
//    int ph;
//    cin >> ph;
//    count ++;
//    avg = (avg*(count-1) + ph)/count;
//    cout << endl<< avg << endl;
//  }
//}

It basically updates the average based off of new information. When the arm first
powers on, it'll be pretty slow

****/

int Laser = 6;
int Detector = 7;


long long count = 0;
long avg = 0;

unsigned long val_counts [2] = {0,0}; //used to get the ratio of 0s to 1s

int avg_sample_size = 5; //maybe make this larger?
unsigned long previous_values [avg_sample_size]; 
int index = 0;

int prev_sig = 0;



void setup()
{ 
  
  Serial.begin (9600);
  pinMode(Laser, OUTPUT);
  pinMode(Detector, INPUT);
}

void loop()
{
  int i = 0;
  unsigned long ratio = 0;
  digitalWrite(Laser, HIGH);
  boolean val = digitalRead(Detector);

 
  if (val) {
      //laser was not detected
      val_counts[1]++;
      Serial.print(val);
  }
  else {
      //laser was detected
      val_counts[0]++;
      Serial.print(val);
  }

  
  if (val != prev_sig && !val){
      //need to account for the case where
      //the laser is detected for more than one loop
      //but maintains a 359 : 1 non-detect : detect ratio
      //since there are 360 degrees in a circle
      //see line 108 ("ratio = val_counts[1]/val_counts[0];")
      
      
      int i = 0;
      avg = 0;
      
      previous_values[index] = val_counts[1]/val_counts[0];
      index = (index + 1) % 5;
      
      for (; i < 5 ; i++){
        avg += val;
      }
      
      avg /= 5;
  }
  prev_sig = val;
  //ratio = val_counts[1]/val_counts[0];
  
// Serial.print(ratio+ " \n");
// KC: There are some display issues. My guess is that there's some sort of overflow issue.


  
}  
