/*
Fading an LED between a min max value
Version 3

  by Ben Kazemi - ben.kazemi@gmail.com
  22/09/2015
*/
                    
int led = 3; // change this to where you've connected your LED
int brightness = 0; // analogue read will slice the source voltage into 255 discrete values
                     // so you can actually source 0V to V_source to your component, this means we can fade our LED
boolean isIncreasing = true; // this will tell the code whether to fade in or out the LED, and is initialised to
                   // true since we declared brightness to 0 (during initialisation)
void setup() {
  pinMode(led, OUTPUT);  
}

void loop() {
  analogWrite(led, brightness); // write a value between 0 and 255 to the led pin 
  /*
    this function utilises a technique called Pulse width modulation. you pick a really high frequency and change the 
    length of time the square wave is high. that sets a ratio of how long the pulse is high to how long it's low. 
    this can be interpreted as a percentage, or a number between 0 and 255 for an 8 bit register (which is what we're using here)
    
    Critical: this only works on pins 3, 5, 6, 9, 10, and 11 - check the documentation when in doubt (or need to know about functions)
  */
  
  if (isIncreasing)
    brightness++; // 1 line in the if body so we don't need curly braces 
  else 
    brightness--; // this is the same as brightness = brightness - 1; 
    
    // can change the value to increment to have faster or slower fading. Experiment! 
    // another factor of fade speed is the delay several lines down
    
   
  if (brightness == 0) {        // if we've reached a minimum value then started fading in
    isIncreasing = true ;
  } else if (brightness == 255) {  // if we've reached a max value then we want to fade out
    isIncreasing = false;         
  }
  
  delay(10); // wait a short while 
}
