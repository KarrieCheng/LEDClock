/* Group Project
Base Code from http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 */


#define LED_COUNT 8
#define DIGIT_COUNT  10


// constants won't change. Used here to set a pin number :
const int ledPin000 =  13;      // the number of the LED pin
const int ledPin001 =  12;      // the number of the LED pin
const int ledPin010 =  11;      // the number of the LED pin
const int ledPin011 =  10;      // the number of the LED pin
const int ledPin100 =  9;      // the number of the LED pin
const int ledPin101 =  8;      // the number of the LED pin
const int ledPin110 =  7;      // the number of the LED pin
const int ledPin111 =  6;      // the number of the LED pin

// Variables will change :
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 1000;           // interval at which to blink (milliseconds)

int leds [8] = {ledPin000, ledPin000, ledPin000, ledPin000,ledPin000, ledPin000, ledPin000, ledPin000};


int one_bar [8] =           {1,1,1,1,1,1,1,1};
int one_blank [8] =         {0,0,0,0,0,0,0,0};
int one_mid [8] =           {0,0,0,1,0,0,0,0};
int one_top[8] =            {1,0,0,0,0,0,0,0};
int two_top [8] =           {1,1,1,1,0,0,0,0};
int two_bottom [8] =        {0,0,0,0,1,1,1,1};
int two_exclam [8] =        {1,1,1,1,0,0,0,1};
int two_inv_excl [8] =      {1,0,0,0,1,1,1,1};
int two_spread [8] =        {1,0,0,0,0,0,0,1};
int two_bot_spread [8] =    {0,0,0,0,1,0,0,1};
int two_top_spread [8] =    {1,0,0,1,0,0,0,0};
int three_spread [8] =      {1,0,0,1,0,0,0,1};
int three_spread_inv [8] =  {1,0,0,0,1,0,0,1};

int zero[3][8] =  {{*one_bar}, {*one_mid}, {*one_bar}};
//int one[8][3] =   {*one_blank, *one_bar, *one_blank};
//int one [3] =   {one_blank, one_bar, one_blank};
//int two [3] =   {two_inv_excl, three_spread_inv, two_exclam};
//int three [3] = {three_spread, three_spread, one_bar};
//int four [3] =  {two_top, one_mid, one_bar};
//int five [3] =  {two_exclam, three_spread_inv, two_inv_excl};
//int six [3] =   {one_bar, three_spread_inv, two_inv_excl};
//int seven [3] = {one_top, one_top, one_bar};
//int eight [3] = {one_blank, three_spread, one_bar};
//int nine [3] =  {two_top, two_top_spread, one_bar};


void setup() {
  // set the digital pin as output:
  pinMode(ledPin000, OUTPUT);
  pinMode(ledPin001, OUTPUT);
  pinMode(ledPin010, OUTPUT);
  pinMode(ledPin011, OUTPUT);
  
}

void loop()
{
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

//    // if the LED is off turn it on and vice-versa:
//    if (ledState == LOW)
//      ledState = HIGH;
//    else
//      ledState = LOW;
//
//    // set the LED with the ledState of the variable:
//
//    int counter = 0;
//    for (
//      digitalWrite(ledPin000, ledState);
//      digitalWrite(ledPin001, ledState);
//      digitalWrite(ledPin010, ledState);
//      digitalWrite(ledPin011, ledState);


digitalWrite(ledPin000, HIGH);


//  int current_array[8] = {1,1,1,1,1,1,1,1};
//  current_array[8] = *one_blank;
//Figure out how to get 2D array in C

//  
//  int counter = 0;
//  //changes led to current
//  for (;counter < LED_COUNT;counter++){
//    if (current_array[counter])
//      ledState = HIGH;
//    else 
//      ledState = LOW;
//    digitalWrite(leds[counter], ledState);
//    printf("Bulb Stuff: %d", current_array[counter]);
//  }


  }
}

