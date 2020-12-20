#define BAUDRATE 9600
#define DELAY 100
#define PIN 2
#define LEDPIN 13

bool SwitchIsOn;

// put your setup code here, to run once:
void setup() {
  Serial.begin( BAUDRATE );                 // Initialize serial (USB) communication
  pinMode(PIN, INPUT);                      // Define pin as input for the toggle switch
  digitalWrite(PIN, HIGH);                  // Enable pull-up resistor on pin
  pinMode(LEDPIN, OUTPUT);                  // Pin connected to the on-board LED

  SwitchIsOn = (digitalRead(PIN) == LOW);   // Get initial state. ON is 0V due to pull-up configuration
  Serial.println( SwitchIsOn ? "1" : "0");
}

// put your main code here, to run repeatedly:
void loop() {
  bool ActSwitchIsOn = (digitalRead(PIN) == LOW);   // Get current state
  if( ActSwitchIsOn != SwitchIsOn )                 // Switch state has changed
  {
    SwitchIsOn = ActSwitchIsOn;
    Serial.println( SwitchIsOn ? "ON" : "OFF");     // Sending the state via USB (COM)
    digitalWrite(LEDPIN, SwitchIsOn ? HIGH : LOW);  // Display status on the on-board LED
  }
  delay( DELAY );
}
