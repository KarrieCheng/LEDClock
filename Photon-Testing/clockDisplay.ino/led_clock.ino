//CSCE 462 Fall 2015 Group Project
//Karrie Cheng, Nicholas Lonsway, Jerego Orlino
// Modified from Spark Interval Timer demo
// This code utilizes the SparkIntervalTimer library to creat timed interrupts to -
// - flash the time on a flying banner.

#include <string.h>
#include "SparkIntervalTimer.h"
 
#define MSRP_HISTORY  10
#define SEG_PER_REV 72

#define COLON  10
#define BLANK 11

unsigned long mspr[MSRP_HISTORY]; //keeps a history of the few milliseconds per rotation
int mspr_index = 0; //
double mspr_average = 1;

unsigned long loop_start = 0;
unsigned long loop_end = 0;
unsigned long watch = 0;

volatile bool interrupt = false;
intPeriod ms_intervals = 5000;

const uint8_t ledPin = 0;		// LED for first Interval Timer
const uint8_t ledPin2 = 1;		// LED for second Interval Timer
const uint8_t ledPin3 = 2;		// LED for third Interval Timer
const uint8_t ledPin4 = 3;
const uint8_t ledPin5 = 4;

IntervalTimer myTimer;		// 3 for the Core
IntervalTimer myTimer2;
IntervalTimer myTimer3;
IntervalTimer myTimer4;
IntervalTimer myTimer5;

void blinkLED(void);
void blinkLED2(void);
void blinkLED3(void);
void blinkLED4(void);
void blinkLED5(void);



/*TIME GLOBAL VARIABLES*/
int hours = 37;
int minutes = 26;
int tzone = -6; //Default to CST

int hour0 = hours / 10;
int hour1 = hours % 10;
int minute0 = minutes / 10;
int minute1 = minutes % 10;

// int digit_map [1080];
int digit_map [480];
const int columns = 3;
const int leds_per_column = 5;


/**** NUMBER SEGMENT ENCODINGS ****/
const int one_bar [5] =           {1,1,1,1,1};
const int one_blank [5] =         {0,0,0,0,0};
const int one_mid [5] =           {0,0,1,0,0};
const int one_top[5] =            {1,0,0,0,0};
const int two_top [5] =           {1,1,1,0,0};
const int two_exclam [5] =        {1,1,1,0,1};
const int two_inv_excl [5] =      {1,0,0,1,1};
const int two_colon [5] =         {0,1,0,1,0}; //colon
const int two_spread [5] =        {1,0,0,0,1};
const int two_bot_spread [5] =    {0,0,0,1,1};
const int two_top_spread [5] =    {1,0,1,0,0};
const int three_spread [5] =      {1,0,1,0,1};
const int three_spread_inv [5] =  {1,0,1,0,1};

/**** NUMBER SEGMENT ENCODINGS ****/
int zero  [15];
int one   [15];
int two   [15];
int three [15];
int four  [15];
int five  [15];
int six   [15];
int seven [15];
int eight [15];
int nine  [15];
int colon  [15];
int blank  [15];

int* led_reps [12] = {zero, one, two, three, four, five, six, seven, eight, nine, colon, blank};

volatile unsigned long blinkCount = 0; // use volatile for shared variables

/**** INITIAL RUNNING FUNCTION****/
void setup(void) {
    
    Particle.function("tzone",changeZone);
    Time.zone(tzone);
    
    int Detector = 7;
    pinMode(Detector, INPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(ledPin4, OUTPUT);
    pinMode(ledPin5, OUTPUT);

    attachInterrupt(Detector, ISR, FALLING);
    myTimer.begin(blinkLED, 1000, uSec);
    myTimer2.begin(blinkLED2, 1000, uSec);
    myTimer3.begin(blinkLED3, 1000, uSec);
    myTimer4.begin(blinkLED4, 1000, uSec);
    myTimer5.begin(blinkLED5, 1000, uSec);

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
    
    update_time();
    
    delay(100);

}

int changeZone(String command){
    tzone = atoi(command);
    return 0;
}


void ISR() {
    interrupt = true;
}

void create_digit_map(){
    int* temp_digit_array;
    
    int row = 0;
    int column_counter = 0;
    int temp_digit_array_index = 0;
    int index = 0;
    
    
    temp_digit_array = led_reps[BLANK];
    for (temp_digit_array_index = 0; temp_digit_array_index < (SEG_PER_REV/8) * leds_per_column; temp_digit_array_index++){
        index = (column_counter*leds_per_column) + temp_digit_array_index;
        digit_map[index] = temp_digit_array[0];
    } 
    column_counter+=(SEG_PER_REV/4);
    
    
    
    temp_digit_array = led_reps[hour0];
    for (temp_digit_array_index = 0; temp_digit_array_index < columns * leds_per_column; temp_digit_array_index++){
        index = (column_counter*leds_per_column) + temp_digit_array_index;
        digit_map[index] = temp_digit_array[(temp_digit_array_index)];
    }
    column_counter+=3;
    
    temp_digit_array = led_reps[BLANK];
    for (temp_digit_array_index = 0; temp_digit_array_index < leds_per_column; temp_digit_array_index++){
      index = (column_counter*leds_per_column) + temp_digit_array_index;
         digit_map[index] = temp_digit_array[(temp_digit_array_index)];
    } 
    column_counter++;
    
    temp_digit_array = led_reps[hour1];
    for (temp_digit_array_index = 0; temp_digit_array_index < columns * leds_per_column; temp_digit_array_index++){
       index = (column_counter*leds_per_column) + temp_digit_array_index;
        digit_map[index] = temp_digit_array[(temp_digit_array_index)];
    }
    column_counter+=3;
    
    temp_digit_array = led_reps[COLON];
    for (temp_digit_array_index = 0; temp_digit_array_index < columns * leds_per_column; temp_digit_array_index++){
       index = (column_counter*leds_per_column) + temp_digit_array_index;
        digit_map[index] = temp_digit_array[(temp_digit_array_index)];
    }
    column_counter+=3;
    
    temp_digit_array = led_reps[minute0];
    for (temp_digit_array_index = 0; temp_digit_array_index < columns * leds_per_column; temp_digit_array_index++){
        index = (column_counter*leds_per_column) + temp_digit_array_index;
        digit_map[index] = temp_digit_array[(temp_digit_array_index)];
    }
    column_counter+=3;
    
    temp_digit_array = led_reps[BLANK];
    for (temp_digit_array_index = 0; temp_digit_array_index < leds_per_column; temp_digit_array_index++){
      index = (column_counter*leds_per_column) + temp_digit_array_index;
         digit_map[index] = temp_digit_array[(temp_digit_array_index)];
    } 
    column_counter++;
    
    temp_digit_array = led_reps[minute1];
    for (temp_digit_array_index = 0; temp_digit_array_index < columns * leds_per_column; temp_digit_array_index++){
       index = (column_counter*leds_per_column) + temp_digit_array_index;
        digit_map[index] = temp_digit_array[(temp_digit_array_index)];
    }
    column_counter+=3;
    
    
    
    
    
    
    temp_digit_array = led_reps[BLANK];
    for (temp_digit_array_index = 0; temp_digit_array_index < (SEG_PER_REV/4) * leds_per_column; temp_digit_array_index++){
        index = (column_counter*leds_per_column) + temp_digit_array_index;
        digit_map[index] = temp_digit_array[0];
    } 
    column_counter+=(SEG_PER_REV/4);

    
    
    
    
    
    
   temp_digit_array = led_reps[hour0];
    for (temp_digit_array_index = 0; temp_digit_array_index < columns * leds_per_column; temp_digit_array_index++){
        index = (column_counter*leds_per_column) + temp_digit_array_index;
        digit_map[index] = temp_digit_array[(temp_digit_array_index)];
    }
    column_counter+=3;
    
    temp_digit_array = led_reps[BLANK];
    for (temp_digit_array_index = 0; temp_digit_array_index < leds_per_column; temp_digit_array_index++){
      index = (column_counter*leds_per_column) + temp_digit_array_index;
         digit_map[index] = temp_digit_array[(temp_digit_array_index)];
    } 
    column_counter++;
    
    temp_digit_array = led_reps[hour1];
    for (temp_digit_array_index = 0; temp_digit_array_index < columns * leds_per_column; temp_digit_array_index++){
       index = (column_counter*leds_per_column) + temp_digit_array_index;
        digit_map[index] = temp_digit_array[(temp_digit_array_index)];
    }
    column_counter+=3;
    
    temp_digit_array = led_reps[COLON];
    for (temp_digit_array_index = 0; temp_digit_array_index < columns * leds_per_column; temp_digit_array_index++){
       index = (column_counter*leds_per_column) + temp_digit_array_index;
        digit_map[index] = temp_digit_array[(temp_digit_array_index)];
    }
    column_counter+=3;
    
    temp_digit_array = led_reps[minute0];
    for (temp_digit_array_index = 0; temp_digit_array_index < columns * leds_per_column; temp_digit_array_index++){
        index = (column_counter*leds_per_column) + temp_digit_array_index;
        digit_map[index] = temp_digit_array[(temp_digit_array_index)];
    }
    column_counter+=3;
    
    temp_digit_array = led_reps[BLANK];
    for (temp_digit_array_index = 0; temp_digit_array_index < leds_per_column; temp_digit_array_index++){
      index = (column_counter*leds_per_column) + temp_digit_array_index;
         digit_map[index] = temp_digit_array[(temp_digit_array_index)];
    } 
    column_counter++;
    
    temp_digit_array = led_reps[minute1];
    for (temp_digit_array_index = 0; temp_digit_array_index < columns * leds_per_column; temp_digit_array_index++){
       index = (column_counter*leds_per_column) + temp_digit_array_index;
        digit_map[index] = temp_digit_array[(temp_digit_array_index)];
    }
    column_counter+=3;
    
    temp_digit_array = led_reps[BLANK];
    for (temp_digit_array_index = 0; temp_digit_array_index < (SEG_PER_REV - column_counter) * leds_per_column;temp_digit_array_index++){
        index = (column_counter*leds_per_column) + temp_digit_array_index;
        digit_map[index] = temp_digit_array[0];
    } 
}



/****LED WRITE FUNCTIONS****/
void blinkLED(void) {
    // digit_map[blinkCount * 5 ] = 1;
    blinkCount = (blinkCount + 1)% SEG_PER_REV;		// increase when LED turns on
    (digit_map[blinkCount * 5 + 4] == 1)? digitalWrite(ledPin, HIGH): digitalWrite(ledPin, LOW);
}
// Callback for Timer 2
void blinkLED2(void) {
    //digit_map[blinkCount * 5 + 1] =1;
    (digit_map[blinkCount * 5 + 3] == 1)? digitalWrite(ledPin2, HIGH): digitalWrite(ledPin2, LOW);
}
// Callback for Timer 3
void blinkLED3(void) {
     (digit_map[blinkCount * 5 + 2] == 1)? digitalWrite(ledPin3, HIGH): digitalWrite(ledPin3, LOW);
}
// Callback for Timer 4
void blinkLED4(void) {
    (digit_map[blinkCount * 5 + 1] == 1)? digitalWrite(ledPin4, HIGH): digitalWrite(ledPin4, LOW);
}
// Callback for Timer 5
void blinkLED5(void) {
    (digit_map[blinkCount * 5 + 0] == 1)? digitalWrite(ledPin5, HIGH): digitalWrite(ledPin5, LOW);
}


/**** RPM FUNCTIONS****/

void update_counters(){
    loop_end = millis();
    mspr[mspr_index] = loop_end - loop_start;
    loop_start = millis();

    mspr_index = (mspr_index + 1) % MSRP_HISTORY;
}


void update_avg(){
    int array_counter = 0;
    unsigned long sum = 0;
    for (array_counter = 0; array_counter < MSRP_HISTORY; array_counter++){
        sum += mspr[array_counter];
    }
    mspr_average = sum/MSRP_HISTORY;
    ms_intervals = (mspr_average/SEG_PER_REV)*1000;
}

void update_time(){
  Time.zone(tzone);
  Particle.syncTime();
  
  hours = Time.hour();
  minutes = Time.minute();
  
  hours = hours % 12;
  if(hours == 0){
      hours = 12;
  }
  
  hour0 = hours / 10;
  hour1 = hours % 10;
  minute0 = minutes / 10;
  minute1 = minutes % 10;
  create_digit_map();
}


/****MAIN FUNCTION****/
void loop(void) {
    
   if (interrupt) {
         

        interrupt = false;
        update_time();
        update_counters();
        update_avg();
        update_time();
        myTimer.resetPeriod_SIT(ms_intervals, uSec);
        myTimer2.resetPeriod_SIT(ms_intervals, uSec);
        myTimer3.resetPeriod_SIT(ms_intervals, uSec);
        myTimer4.resetPeriod_SIT(ms_intervals, uSec);
        myTimer5.resetPeriod_SIT(ms_intervals, uSec);
        
    }
}
