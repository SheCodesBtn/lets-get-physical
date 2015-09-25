/*
Blinking an LED
Version 2

  by Ben Kazemi - ben.kazemi@gmail.com
  22/09/2015
*/
int led = A0; // change this to where you've connected your LED
boolean state = false;

void setup() {
  pinMode(led, OUTPUT); 
}

void loop() {
  /*
  we now take a boolean variable and toggle it every half a second so it's less 'hard coded'
  */
  state = !state;
  digitalWrite(led, state);
  delay(500);            
  // but this delay is still really inefficient and it halts 
  // the entire microcontroller clock from doing anything else 

  // so we would want to use a 'timer' which is an indepentent module of the microcontroller
  // which can 'interrupt' whatever the current program is running, take precedence, and run whatever 
  // the timer interrupt is pointing to! 
  // this will be left out though because, while it's simple, it slightly veers off from todays goals 
}
