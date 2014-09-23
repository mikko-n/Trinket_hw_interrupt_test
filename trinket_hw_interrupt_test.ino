/*
 * Test sketch for attaching interrupt to falling edge of digital signal
 * on Adafruit Trinket (ATTiny85)
 */

#define BTNPIN 2 // has to be pin #2 because it's Trinket's INT0 pin
#define LEDPIN 1 // internal led

byte BLINK_COUNT = 3;
byte BLINK_DELAY = 50;
volatile byte buttonPressed = 0;

void setup() {
  pinMode(LEDPIN, OUTPUT);
  pinMode(BTNPIN, INPUT);
  digitalWrite(BTNPIN, HIGH);

  // attach interrupt function to INT0 (=pin #2) 
  // and trigger it when the pin goes from HIGH to LOW
  attachInterrupt(0, BlinkLed, FALLING);
}

/*
 * Main routine.
 * Blinks LEDPIN for BLINK_COUNT times with BLINK_DELAY interval
 * if buttonPressed variable has been set
 */
void loop() {
  if (buttonPressed != 0) {
    for(byte i = 0; i<BLINK_COUNT; i++) {
      digitalWrite(LEDPIN, HIGH);
      delay(BLINK_DELAY);
      digitalWrite(LEDPIN, LOW);
      delay(BLINK_DELAY);      
    }
    buttonPressed = 0;
  }
}

/*
 * Subroutine to run every time pin BTNPIN switches from high to low
 *
 * Notes about Interrupt Service Routines: (from http://arduino.cc/en/Reference/attachInterrupt )
 * - delay() and millis() both rely on interrupts, so they do not work here
 * - delayMicroseconds() does not use interrupts so it would work
 * - to make sure variables used in an ISR are updated correctly, declare them as volatile. 
 */
void BlinkLed() {
  buttonPressed = 1;
}
