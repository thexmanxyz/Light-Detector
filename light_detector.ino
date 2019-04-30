/* Constants */

const unsigned short PIN_BLUE_LED = 2;            // pin number of the blue LED - night (digital)
const unsigned short PIN_GREEN_LED = 3;           // pin number of the green LED - twilight (digital)
const unsigned short PIN_RED_LED = 4;             // pin number of the red LED - day (digital)
const unsigned short PIN_BTN = 8;                 // pin number of the pushbutton (digital)
const unsigned short PIN_BTN_PRESS_LED =  13;     // pin number of the button indicator LED (digital)

const unsigned short PIN_PHOTO_RESISTOR = A0;     // pin number of the photoresistor (analog)

const unsigned short AMBIENCE_THRESHOLD1 = 15;    // ambience threshold (1)
const unsigned short AMBIENCE_THRESHOLD2 = 30;    // ambience threshold (2)
const unsigned short DEBOUNCE_DELAY = 50;         // the debounce delay to prevent output flickering

/* Variables */

bool btnState = false;                // the current pushbutton state (debounced)
bool btnLastState = false;            // the last iteration pushbutton state (debounced)
bool btnLastRead = false;             // the last iteration pushbutton read state (raw)

unsigned long lastTransmissionTime = 0;  // the last transmission time
unsigned long lastDebounceTime = 0;      // the last button toggle time

String ambience = "";                    // the ambience transmission string

void setup() {
  
  // begin serial transmission
  Serial.begin(9600);
  
  // initialize the LED pins as output
  pinMode(PIN_BTN_PRESS_LED, OUTPUT);
  pinMode(PIN_BLUE_LED, OUTPUT);
  pinMode(PIN_GREEN_LED, OUTPUT);
  pinMode(PIN_RED_LED, OUTPUT);
  
  // initialize the pushbutton pin as input
  pinMode(PIN_BTN, INPUT);
}

void loop() {

  // read the value of the photoresistor (analog)
  unsigned int photoResistorValue = analogRead(PIN_PHOTO_RESISTOR);
  
  // read the state of the button (digital)
  bool btnRead = digitalRead(PIN_BTN);

  // check to see if you the button just got pressed
  // or if the button state changed due to noise
  if (btnRead != btnLastRead) {
    
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  // whatever the button value is at, it's been there for longer than the debounce delay
  // e.g. the input went from LOW to HIGH and we've waited long enough (ignore noise)
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {

    // if the button state has changed
    if (btnRead != btnState) {

      //change current (real) button state 
      btnState = btnRead;
 
      // set the button pressed indicator light in dependence of the button state
      // if the button is pressed, light the indicator otherwise not
      digitalWrite(PIN_BTN_PRESS_LED, btnState);
    }
  }

  // if button was pressed but is not hold over multiple iterations or
  // got already pressed and the interval since the last press >= 5000ms 
  if((!btnLastState && btnState) || (lastTransmissionTime > 0 && millis() - lastTransmissionTime >= 5000)){

    // print ambience string and photo resistor value to serial
    Serial.print("Send Data: ");          // send data (1)
    Serial.print(ambience);               // send data (2)
    Serial.print(" (");                   // send data (3)
    Serial.print(photoResistorValue);     // send data (4)
    Serial.println(")");                  // send data (5)

    // reset last transmission time
    lastTransmissionTime = millis();
  }

  // ambience threshold1 not met
  if(photoResistorValue <= AMBIENCE_THRESHOLD1){
    digitalWrite(PIN_BLUE_LED, HIGH);
    digitalWrite(PIN_GREEN_LED, LOW);
    digitalWrite(PIN_RED_LED, LOW);
    ambience = "Night";

  // ambience threshold1 met, but ambience threshold2 not met
  }else if(photoResistorValue > AMBIENCE_THRESHOLD1 && photoResistorValue <= AMBIENCE_THRESHOLD2){
    digitalWrite(PIN_GREEN_LED, HIGH);
    digitalWrite(PIN_BLUE_LED, LOW);
    digitalWrite(PIN_RED_LED, LOW);
    ambience = "Twilight";

  // both tresholds met (only checked for greater one)
  }else if(photoResistorValue > AMBIENCE_THRESHOLD2){
    digitalWrite(PIN_RED_LED, HIGH);
    digitalWrite(PIN_BLUE_LED, LOW);
    digitalWrite(PIN_GREEN_LED, LOW);
    ambience = "Day";
  }
 
  // store the button state value from the last iteration  (debounced value)
  btnLastState = btnState; 

  // store the button read value from the last iteration (raw read value)
  btnLastRead = btnRead;
}
