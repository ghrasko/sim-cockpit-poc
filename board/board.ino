#define BAUDRATE 57600
#define DELAY 100
#define AVIONICSPIN 2
#define APHDGPIN 3
#define LEDPIN 13

bool AvionicsIsOn; 
bool AppHdgIsOn;

// put your setup code here, to run once:
void setup() {
  Serial.begin( BAUDRATE );                 // Initialize serial (USB) communication
  pinMode(AVIONICSPIN, INPUT);                      // Define pin as input for the radio toggle switch
  digitalWrite(AVIONICSPIN, HIGH);                  // Enable pull-up resistor on pin
  pinMode(APHDGPIN, INPUT);                      // Define pin as input for the APP HDG button
  digitalWrite(APHDGPIN, HIGH);                  // Enable pull-up resistor on pin
  pinMode(LEDPIN, OUTPUT);                  // Pin connected to the on-board LED

  AvionicsIsOn = (digitalRead(AVIONICSPIN) == LOW);   // Get initial state. ON is 0V due to pull-up configuration
  Serial.println( AvionicsIsOn ? "AVIONICS-ON" : "AVIONICS-OFF");
  AppHdgIsOn = (digitalRead(APHDGPIN) == LOW);   // Get initial state. ON is 0V due to pull-up configuration
  Serial.println( AppHdgIsOn ? "APPHDG-ON" : "APPHDG-OFF");
}

// put your main code here, to run repeatedly:
void loop() {
  bool tempStat;
  
  tempStat = (digitalRead(AVIONICSPIN) == LOW);   // Get current state
  if( tempStat != AvionicsIsOn )                 // Switch state has changed
  {
    AvionicsIsOn = tempStat;
    Serial.println( AvionicsIsOn ? "AVIONICS-ON" : "AVIONICS-OFF");     // Sending the state via USB (COM)
  }

  tempStat = (digitalRead(APHDGPIN) == LOW);   // Get current state
  if( tempStat != AppHdgIsOn )                 // Switch state has changed
  {
    AppHdgIsOn = tempStat;
    Serial.println( AppHdgIsOn ? "APPHDG-ON" : "APPHDG-OFF");     // Sending the state via USB (COM)
  }

  if(Serial.available() > 0)
  {
    int dataIn = Serial.read();
    digitalWrite(LEDPIN, AvionicsIsOn && char(dataIn) == '1'  ? HIGH : LOW);
    //Serial.print( "ARDUINO ACK: " ); Serial.println( dataIn );
  }
  
  delay( DELAY );
}
