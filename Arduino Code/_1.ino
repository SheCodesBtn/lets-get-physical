/*
Blinking an LED
Version 2

  by Ben Kazemi - ben.kazemi@gmail.com
  22/09/2015
*/
int led = A0; // change this to where you've connected your LED

void setup() {
  pinMode(led, OUTPUT); // here we tell the uC that this pin
                        // should 'source' current (power things)
                        // and not 'sink' current (like your phone when it's charging)
                        // we always connect a current limiting resistor in serial with the LED 
/*
                        There's this 'law' called Kirchoffs Voltage law which basically states:
                          The circuits entire voltage source must equal the the sum of all the voltage drops 
                          
                          Really this says that all if i have a 5V source, and one LED, then the 5V will go through the LED
                          and blow.
                          With KVL we know we must drop the source voltage to a a level the LED likes,
                            and that's what the resistor does.
                         
                          Maths behind this is simple but left out so we can do more fun stuff, 
                            and also because it's not the goal of this session
                        
                            
*/
}

void loop() {
  digitalWrite(led, HIGH);
  delay(500);             // this is actually very inefficient as the program stalls here for 
                          //the time you specified and cannot do anything else
                          //, lesson 3 shows a much better way to do this
  digitalWrite(led, LOW);
  delay(500);
}

/*
	measure the current and voltate across the LED!
*/
