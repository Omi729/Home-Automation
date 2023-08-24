#include "config.h"
// this should correspond to a pin with PWM capability

// set up the 'analog' feed

AdafruitIO_Feed *led = io.feed("led");

int ledPin = 26;
int pirPin = 14;
int pirValue = 0;


void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'analog' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  led->onMessage(handleMessage);


  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  pinMode(ledPin,OUTPUT);
  pinMode(pirPin,INPUT);
  led->get();
}

void loop() {
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
 
  pirValue = digitalRead(pirPin);   
    if (pirValue == HIGH)   
    {           
        digitalWrite(ledPin, HIGH);
            
        // turn ON LED if the motion is detected    
    }   
    
      
}

void handleMessage(AdafruitIO_Data *data) {
  Serial.print("received <- ");

  if (data->toPinLevel() == HIGH)
  {
    digitalWrite(ledPin,HIGH);
    Serial.println("HIGH");
  }
  else
  {
    digitalWrite(ledPin,LOW);
    Serial.println("LOW");
  }
  
  
}

// this function is called whenever an 'analog' message
// is received from Adafruit IO. it was attached to
// the analog feed in the setup() function above.
