/*
having two LEDs that pulsate in sequence using PWM (to fade them and not just have binary on off choices);
  button to turn them on or off 
  serial d/l characters define light or dark room settings
  serial z/x define faster/slower pulsate speeds
  buzzer or third led to signify a max speed

Version 6

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
int topSpeedLED = A5; 
boolean isIncreasing[] = {true, false};
unsigned int brightness[] = {0, 255};  
int buttonPin = 14;    // the number of the pushbutton pin
int fadeInterval = 3;
boolean toggle = true; 
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned int minBrightness = 0;
unsigned int maxBrightness = 255;
long delayTime = 5; 
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  Serial.begin(9600);  
  
  pinMode(topSpeedLED, OUTPUT);
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
    /*
      there are much more efficient ways of doing this! experiment.. try to eliminate the need for an array
      and instead, set brightness of of trailing LEDs dependent on 1 brightness setting
    */
    for (int i = 0; i < maxLEDs; i++) { 
      analogWrite(led[i], brightness[i]); 
     
      if (isIncreasing[i]) {
        if (brightness[i] + fadeInterval >= maxBrightness)
          brightness[i] = maxBrightness;
        else
          brightness[i] = brightness[i] + fadeInterval;  
      }
      else { 
        if (brightness[i] - fadeInterval <= minBrightness)
          brightness[i] = minBrightness;
        else
          brightness[i] = brightness[i] - fadeInterval; 
      }
        
      if (brightness[i] == minBrightness)      
        isIncreasing[i] = true ;
      else if (brightness[i] == maxBrightness)   
        isIncreasing[i] = false;         
    }
    delay(delayTime); 
    
  } else {
    for (int i = 0; i< maxLEDs; i++) {
      digitalWrite(led[i], LOW);     
    } 
    isIncreasing[0] = true;
    isIncreasing[1] = false;
    brightness[0] = minBrightness; 
    brightness[1] = maxBrightness;   
  }
}
//######################### serial event ####################################################
void serialEvent() {
  while (Serial.available()) { 
    char inChar = (char)Serial.read(); 
    Serial.print("I received: ");
    Serial.print(inChar);
    switch (inChar) {
      case 'z': if (delayTime - fadeInterval > 1) {
        /*
            see what happens if you set delayTime as an unsigned long instead of a long
            (hint: check the serial monitor). Why is this ? 
        */
                  delayTime = delayTime - fadeInterval;
                }
                else {
                  delayTime = 1;
                  digitalWrite(topSpeedLED, HIGH);
                }
                Serial.print(", delay time is: ");  
                Serial.print(delayTime);  
                break;
      case 'x': if (delayTime + fadeInterval <= 200) {
                  delayTime = delayTime + fadeInterval;
                  digitalWrite(topSpeedLED, LOW);
                }
                Serial.print(", delay time is: ");
                Serial.print(delayTime);  
                break;  
      case 'd': maxBrightness = 100; // Dark mode - make everything a bit darker
                minBrightness = 0;
                isIncreasing[0] = true;
                isIncreasing[1] = false;
                brightness[0] = minBrightness; 
                brightness[1] = maxBrightness;   
                fadeInterval = 2;
                Serial.print(", Dark room mode set");  
                break;  
      case 'l': minBrightness = 5;
                maxBrightness = 255; // Light mode - make everything a bit lighter
                isIncreasing[0] = true;
                isIncreasing[1] = false;
                brightness[0] = minBrightness; 
                brightness[1] = maxBrightness;  
                fadeInterval = 3;  
                Serial.print(", Light room mode set");   
                break;  
 
    }
    for (int i = 0; i< maxLEDs; i++) {
      if (i != selectedLED)
        digitalWrite(led[i], LOW);     
    }     
    Serial.println();
  }
}
