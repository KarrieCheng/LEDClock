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

int Laser = 6;
int Detector = 7;
long long count = 0;
long avg = 0;
unsigned long val_counts [2] = {0,0};
unsigned long previous_values [5];
int prev_sig = 0;
int val_index = 0;

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





/*
 * 
 * 
 * 
 * 
 * 
 * 
 */


  
  if (val) {
      val_counts[1]++;
  }
  else {
      val_counts[0]++;
  }
  if (val != prev_sig && !val){
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
  ratio = val_counts[1]/val_counts[0];
  Serial.print(ratio);

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


  
}  
