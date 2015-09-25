/*
Fading an LED selected by serial input between a defined min max value for brightness with a button to toggle on off 

Transmitting characters from terminal:
  b = select blue LEd
  g = select green led
  d = dark mode (darkens brghtnesses)
  l = light mode (you guessed it) 

V6 will have the min max values change dependent on a light sensor! 

Version 5

  by Ben Kazemi - ben.kazemi@gmail.com   
  22/09/2015
*/

int ledselector = 0; 
/*
  0 = first LED (blue)
  1 = second LED (green) 
*/
int led[] = {5, 3}; 
int selectedLED = 0; 
int maxLEDs = 2; 

int buttonPin = 14;    // the number of the pushbutton pin
int brightness = 0; 
boolean isIncreasing = true;      
boolean toggle = false; 
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int minBrightness = 0; 
int maxBrightness = 255;
unsigned long delayTime = 10; 
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  /*
    most asyncronous transmission is done with a 'baud rate' which determines how many bits will be sent
     or received per second. because it's async, both the sender and receiver need to have the same baud rate 
     otherwise they receive the wrong data (sampling at the wrong rate.
     syncronous transmission means the two ends share a common clock so you don't need this since each bit is 
     transmitted per clock pulse, but removing the clock pulse means we can remove a wire from our circuit!
  */
  Serial.begin(9600); // initialize serial so a baud rate of 9600 bps (bits per second) 
  
  
  pinMode(buttonPin, INPUT);
  for (int i = 0; i< maxLEDs; i++) {
    pinMode(led[i], OUTPUT);    
  }
}

void loop() {
  //################### code responsible for debouncing the push button #########################
  int reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        toggle = !toggle;
      }
    }
  }
  
  lastButtonState = reading;
  
  //#########################code we want to play with##########################################
  if (toggle) { 
    analogWrite(led[selectedLED], brightness); 
   
    if (isIncreasing)
      brightness++;  
    else 
      brightness--; 
      
    if (brightness == minBrightness)    // you can see here and 2 lines down we add our own min max values     
      isIncreasing = true ;
    else if (brightness == maxBrightness)   
      isIncreasing = false;         
  /*
    the delay time needs to change depending on the max brightness value IF you want the same length time per fade
  */
    delay(delayTime); 
  } else {
    for (int i = 0; i< maxLEDs; i++) {
      digitalWrite(led[i], LOW);     
    } 
    isIncreasing = true; 
    brightness = 0;  
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) { // see if there's anything in the received serial buffer
    // get the new byte:
    char inChar = (char)Serial.read(); // retrieve the received byte frmo the buffer and wipe it from the buffer
    // echo what the arduino has received! 
    Serial.println(inChar);
    switch (inChar) {
      case 'b': selectedLED = 0; //select Blue LED
                break;
      case 'g': selectedLED = 1; //select Green LED
                break;  
      case 'd': maxBrightness = 100; // Dark mode - make everything a bit darker
                brightness = 0;   
                isIncreasing = true;  
                delayTime = 10; 
                break;  
      case 'l': maxBrightness = 255; // Light mode - make everything a bit lighter
                brightness = 0;   
                isIncreasing = true; 
                delayTime = 5;
                break;  
 
                
    }
    for (int i = 0; i< maxLEDs; i++) {
      if (i != selectedLED)
        digitalWrite(led[i], LOW);     
    }     
  }
}
