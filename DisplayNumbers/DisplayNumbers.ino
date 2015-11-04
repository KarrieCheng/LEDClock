/* Little sample code to turn on the LEDs
   and display the numbers 1-9 and 0
   This code can be improved for sure but
   can be used as a base for later.
   Written on an Arduino Uno
   
   PINS:
   This was written with LEDs in pins 2 through 9
   where 9 is the top pin on the display and 2
   is the bottom pin.
*/

void setup() {                
  // initialize the digital pin as an output.
  pinMode(2, OUTPUT);     
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void turn_on(int leds[], int num_leds){
  for(int i=0; i<num_leds; ++i){
    digitalWrite(leds[i],HIGH);
  }
}

void turn_off(int leds[], int num_leds){
  for(int i=0; i<num_leds; ++i){
    digitalWrite(leds[i], LOW);
  }
}

void end_num(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  delay(1000);
}

void draw_one() {
  /*   *
       *
       *
       *
       *
       *
       *
       *
  */
  delay(600);
  
  int right_on[] = {9,8,7,6,5,4,3,2};
  turn_on(right_on,8);
  delay(300);
  
  end_num();
  }

void draw_two() { 
  /* ***
       *
       *
     ***
     *
     *
     *
     ***
  */

  int left_on[] = {9,6,5,4,3,2};
  turn_on(left_on,6);
  delay(300);
  
  int left_off[] = {5,4,3};
  turn_off(left_off,3);
  delay(300);

  int right_on[] = {8,7};
  turn_on(right_on, 2);
  delay(300);
  
  end_num();
}

void draw_three(){
  /* ***
       *
       *
     ***
       *
       *
       *
     ***
  */
  
  int left_on[] = {9,6,2};
  turn_on(left_on, 3);
  delay(600); 
  
  int right_on[] = {8,7,5,4,3};
  turn_on(right_on, 5);
  delay(300);
  
  end_num();
}

void draw_four(){
  /* * *
     * *
     * *
     ***
       *
       *
       *
       *
  */
  
  int left_on[] = {9,8,7,6};
  turn_on(left_on,4);
  delay(300);
  
  int left_off[] = {9,8,7};
  turn_off(left_off,3);
  delay(300);
  
  int right_on[] = {9,8,7,5,4,3,2};
  turn_on(right_on, 7);
  delay(300);
  
  end_num();
}

void draw_five(){
  /* ***
     *
     *
     ***
       *
       *
       *
     ***
  */
  
  int left_on[] = {9,8,7,6,2};
  turn_on(left_on, 5);
  delay(300);
  
  int left_off[] = {8,7};
  turn_off(left_off, 2);
  delay(300);
  
  int right_on[] = {5,4,3};
  turn_on(right_on, 3);
  delay(300);
  
  end_num();
}

void draw_six(){
  /* ***
     *
     *
     ***
     * *
     * *
     * *
     ***
  */
  
  int left_on[] = {9,8,7,6,5,4,3,2};
  turn_on(left_on, 8);
  delay(300);
  
  int left_off[] = {8,7,5,4,3};
  turn_off(left_off,5);
  delay(300);
  
  int right_on[] = {5,4,3};
  turn_on(right_on, 3);
  delay(300);
  
  end_num();
}

void draw_seven(){
  /* ***
       *
       *
       *
       *
       *
       *
       *
  */
  
  digitalWrite(9,HIGH);
  delay(600);
  
  int right_on[] = {8,7,6,5,4,3,2};
  turn_on(right_on, 7);
  delay(300);
  
  end_num();
}

void draw_eight(){
  /* ***
     * *
     * *
     ***
     * *
     * *
     * *
     ***
  */
  
  int left_on[] = {9,8,7,6,5,4,3,2};
  turn_on(left_on, 8);
  delay(300);
  
  int left_off[] = {8,7,5,4,3};
  turn_off(left_off, 5);
  delay(300);
  
  turn_on(left_on, 8);
  delay(300);
  
  end_num();
}

void draw_nine(){
  /* ***
     * *
     * *
     ***
       *
       *
       *
       *
  */
  
  int left_on[] = {9,8,7,6};
  turn_on(left_on, 4);
  delay(300);
 
  int left_off[] = {8,7};
  turn_off(left_off, 2);
  delay(300);
 
  int right_on[] = {8,7,5,4,3,2};
  turn_on(right_on, 6);
  delay(300);
  
  end_num();
}

void draw_zero(){
  /* ***
     * *
     * *
     * *
     * *
     * *
     * *
     ***
  */
  
  int left_on[] = {9,8,7,6,5,4,3,2};
  turn_on(left_on, 8);
  delay(300);
  
  int left_off[] = {8,7,6,5,4,3};
  turn_off(left_off, 6);
  delay(300);

  turn_on(left_on, 8);
  delay(300);
  
  end_num();
}

// the loop routine runs over and over again forever:
void loop() {
  draw_one();
  draw_two();
  draw_three();
  draw_four();
  draw_five();
  draw_six();
  draw_seven();
  draw_eight();
  draw_nine();
  draw_zero();
}
