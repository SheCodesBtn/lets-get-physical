/*
Fading an LED between a min max value with a button to toggle 
Version 4

  by Ben Kazemi - ben.kazemi@gmail.com   
  using debounce code from the debounce example:
   created 21 November 2006
   by David A. Mellis
   modified 30 Aug 2011
   by Limor Fried
   modified 28 Dec 2012
   by Mike Walters
  22/09/2015
  
 Debounce

 Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
 press), the output pin is toggled from LOW to HIGH or HIGH to LOW.  There's
 a minimum delay between toggles to debounce the circuit (i.e. to ignore
 noise).

 The circuit:
 * LED attached from pin 5 to ground
 * pushbutton attached from pin 14 to +5V
 * 10K resistor attached from pin 14 to ground
  
*/
                    
int led = 5; 
int buttonPin = 14;    // the number of the pushbutton pin
int brightness = 0; 
boolean isIncreasing = true;      
boolean toggle = false; 
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(led, OUTPUT);  
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle if the new button state is HIGH
      if (buttonState == HIGH) {
        toggle = !toggle;
      }
    }
  }
  
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
  
  /*
  now we can use the boolean toggle to do what we want 
  */
  if (toggle) { 
    analogWrite(led, brightness); 
   
    if (isIncreasing)
      brightness++;  
    else 
      brightness--; 
      
    if (brightness == 0)        
      isIncreasing = true ;
    else if (brightness == 255)   
      isIncreasing = false;         
    
    
    delay(5); 
  } else { // if we've toggled off then reset brightness and turn led off
    digitalWrite(led, LOW);  //we want to turn the led off before changing brightness otherwise you get funky behaviour
    isIncreasing = true; // leave this out, and see what happens when you turn the led off when it is decreasing in brightness.
    brightness = 0; // what happens when we leave this out? 
  }
}
