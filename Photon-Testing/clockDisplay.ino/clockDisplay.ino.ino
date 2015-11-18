/* Group Project
Base Code from http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 */

int arduino_offset = 0; //depends on the board we are using ; 2 for the Uno, 0 for the photon
int Detector = 7;

const int columns = 3;
const int leds_per_column = 7;

int segments = 128;
int segment_index = 0;
long counter = 0; //for how many times a loop occurs in a revolution

int hours = 11; 
int minutes = 39;

int hour0 = hours / 10;
int hour1 = hours % 10;
int minute0 = minutes / 10;
int minute1 = minutes % 10;

float ms_per_segment = 0;
//this will matter when the arm is ready.

//Number Segments
const int one_bar [7] =           {1,1,1,1,1,1,1};
const int one_blank [7] =         {0,0,0,0,0,0,0};
const int one_mid [7] =           {0,0,0,1,0,0,0};
const int one_top[7] =            {1,0,0,0,0,0,0};
const int two_top [7] =           {1,1,1,1,0,0,0};
const int two_exclam [7] =        {1,1,1,1,0,0,0};
const int two_inv_excl [7] =      {1,0,0,0,1,1,1};
const int two_colon [7] =         {0,0,1,0,1,0,0}; //colon
const int two_spread [7] =        {1,0,0,0,0,0,0};
const int two_bot_spread [7] =    {0,0,0,0,1,0,0};
const int two_top_spread [7] =    {1,0,0,1,0,0,0};
const int three_spread [7] =      {1,0,0,1,0,0,1};
const int three_spread_inv [7] =  {1,0,0,0,1,0,0};

int zero  [21];
int one   [21];
int two   [21];
int three [21];
int four  [21];
int five  [21];
int six   [21];
int seven [21];
int eight [21];
int nine  [21];

int blank  [21];
int colon  [21];

int* led_reps [10] = {zero, one, two, three, four, five, six, seven, eight, nine};

/**** SETUP ****/

void setup() {
    
  // set the digital pin as output:
  pinMode(0 + arduino_offset, OUTPUT);
  pinMode(1 + arduino_offset, OUTPUT);
  pinMode(2 + arduino_offset, OUTPUT);
  pinMode(3 + arduino_offset, OUTPUT);
  pinMode(4 + arduino_offset, OUTPUT);
  pinMode(5 + arduino_offset, OUTPUT);
  pinMode(6 + arduino_offset, OUTPUT);
  pinMode(Detector, INPUT);

  
  /* BIT MAP ASSIGNMENTS */
  int row_counter = 0;
  for (row_counter = 0; row_counter < leds_per_column; row_counter++)
  {
    zero[row_counter + (0 * leds_per_column)] = one_bar[row_counter];
    zero[row_counter + (1 * leds_per_column)] = two_spread[row_counter];
    zero[row_counter + (2 * leds_per_column)] = one_bar[row_counter];
  }
  for (row_counter = 0; row_counter < leds_per_column; row_counter++){
    one[row_counter + (0 * leds_per_column)] = one_blank[row_counter];
    one[row_counter + (1 * leds_per_column)] = one_bar[row_counter];
    one[row_counter + (2 * leds_per_column)] = one_blank[row_counter];
  }
  for (row_counter = 0; row_counter < leds_per_column; row_counter++){
      two[row_counter + (0 * leds_per_column)] = two_inv_excl[row_counter];
      two[row_counter + (1 * leds_per_column)] = three_spread_inv[row_counter];
      two[row_counter + (2 * leds_per_column)] = two_exclam[row_counter];
  }
  for (row_counter = 0; row_counter < leds_per_column; row_counter++){
      three[row_counter + (0 * leds_per_column)] = three_spread[row_counter];
      three[row_counter + (1 * leds_per_column)] = three_spread[row_counter];
      three[row_counter + (2 * leds_per_column)] = one_bar[row_counter];
  }
  for (row_counter = 0; row_counter < leds_per_column; row_counter++){
      four[row_counter + (0 * leds_per_column)] = two_top[row_counter];
      four[row_counter + (1 * leds_per_column)] = one_mid[row_counter];
      four[row_counter + (2 * leds_per_column)] = one_bar[row_counter];
  }
  for (row_counter = 0; row_counter < leds_per_column; row_counter++){
      five[row_counter + (0 * leds_per_column)] = two_exclam[row_counter];
      five[row_counter + (1 * leds_per_column)] = three_spread_inv[row_counter];
      five[row_counter + (2 * leds_per_column)] = two_inv_excl[row_counter];
  }
  for (row_counter = 0; row_counter < leds_per_column; row_counter++){
      six[row_counter + (0 * leds_per_column)] = one_bar[row_counter];
      six[row_counter + (1 * leds_per_column)] = three_spread_inv[row_counter];
      six[row_counter + (2 * leds_per_column)] = two_inv_excl[row_counter];
  }
  for (row_counter = 0; row_counter < leds_per_column; row_counter++){
      seven[row_counter + (0 * leds_per_column)] = one_top[row_counter];
      seven[row_counter + (1 * leds_per_column)] = one_top[row_counter];
      seven[row_counter + (2 * leds_per_column)] = one_bar[row_counter];
  }
  for (row_counter = 0; row_counter < leds_per_column; row_counter++){
      eight[row_counter + (0 * leds_per_column)] = one_bar[row_counter];
      eight[row_counter + (1 * leds_per_column)] = three_spread[row_counter];
      eight[row_counter + (2 * leds_per_column)] = one_bar[row_counter];
  }
  for (row_counter = 0; row_counter < leds_per_column; row_counter++){
      nine[row_counter + (0 * leds_per_column)] = two_top[row_counter];
      nine[row_counter + (1 * leds_per_column)] = two_top_spread[row_counter];
      nine[row_counter + (2 * leds_per_column)] = one_bar[row_counter];
  }
  for (row_counter = 0; row_counter < leds_per_column; row_counter++){
      blank[row_counter + (0 * leds_per_column)] = one_blank[row_counter];
      blank[row_counter + (1 * leds_per_column)] = one_blank[row_counter];
      blank[row_counter + (2 * leds_per_column)] = one_blank[row_counter];
  }
  for (row_counter = 0; row_counter < leds_per_column; row_counter++){
      colon[row_counter + (0 * leds_per_column)] = one_blank[row_counter];
      colon[row_counter + (1 * leds_per_column)] = two_colon[row_counter];
      colon[row_counter + (2 * leds_per_column)] = one_blank[row_counter];
  }


  
}
void draw_time(int digit, int* array [10], int column){
  int* digit_map;
  digit_map = array[digit];

  int row = 0;
  int index = 0;
  for (row = 0; row < 7; row++)
        {
          index = (column*leds_per_column) + row;
          int pin_index = row + arduino_offset;
          if (digit_map[index] == 1){
            Serial.print("Pin Index \t");
            Serial.print(index);
            Serial.print(digit_map[index]);
            digitalWrite(pin_index, HIGH);
          }
          (digit_map[index] == 1)? digitalWrite(pin_index, HIGH): digitalWrite(pin_index, LOW);
        }
  }


void draw_symbol(int* symbol_location, int column){
  
  int row = 0;
  int index = 0;
  
    for (row = 0; row < 7; row++)
    {
      index = (column*leds_per_column) + row;
      int pin_index = row + arduino_offset;
      (symbol_location[index] == 1)? digitalWrite(pin_index, HIGH): digitalWrite(pin_index, LOW);
    }
  
}


/**** MAIN ****/
void loop()
{ 
  boolean val = digitalRead(Detector);
  if (val) {
    Serial.print(counter);
    counter = 0;
  } //this is for when we decide how fast the clock goes
  
  if (segment_index == 640) //64 was arbitrarily chosen
  {
      ms_per_segment = segments/counter;
      segment_index = 0;  
  }

  switch (segment_index) {
            case 1:  draw_time(hour0, led_reps, 0);
                break;
            case 2:  draw_time(hour0, led_reps, 1);
                break;
            case 3:  draw_time(hour0, led_reps, 2);
                break;
                
            case 4:  draw_time(hour1, led_reps, 0);
                break;
            case 5:  draw_time(hour1, led_reps, 1);
                break;
            case 6:  draw_time(hour1, led_reps, 2);
                break;

            case 7: draw_symbol(colon,0);
                break;
            case 8: draw_symbol(colon,1);
                break;
            case 9: draw_symbol(colon,2);
                break;

            case 10:  draw_time(minute0, led_reps, 0);
                break;
            case 11:  draw_time(minute0, led_reps, 1);
                break;
            case 12:  draw_time(minute0, led_reps, 2);
                break;
            
            case 13:  draw_time(minute1, led_reps, 0);
                break;
            case 14:  draw_time(minute1, led_reps, 1);
                break;
            case 15:  draw_time(minute1, led_reps, 2);
                break;
                
            default: draw_symbol(blank,1);
                break;
        }
  segment_index++;
  counter++;
}

