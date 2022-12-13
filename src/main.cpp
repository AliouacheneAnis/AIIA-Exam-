#include <Arduino.h>
#include<WIFIConnector_MKR1010.h>
#include<MQTTConnector.h>
#include <Adafruit_NeoPixel.h>

#define PIN_LED 4     // Control signal, connect to DI of the LED
#define NUM_LED 1     // Number of LEDs in a strip

int val1, val2,val3; 
const int PIN1 = 1, PIN2 = 2, PIN3 = 3; 

// FGonction pour la LED RGB 
void colorWipe(uint32_t c, uint16_t wait); 

// Declaration d'objet 
Adafruit_NeoPixel RGB_Strip = Adafruit_NeoPixel(NUM_LED, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  
  wifiConnect();
  MQTTConnect(); 
  Serial.begin(9600); 
  pinMode(PIN1, INPUT);
  pinMode(PIN2, INPUT);
  pinMode(PIN3, INPUT);
  
  // Start RGB 
  RGB_Strip.begin();
  RGB_Strip.show();
  RGB_Strip.setBrightness(128);    // Set brightness, 0-255 (darkest - brightest)
}

void loop() {
  // put your main code here, to run repeatedly:
    
  // mqtt loop 
  ClientMQTT.loop();
  RGB_Strip.setBrightness(intensite);
  val1 = digitalRead(PIN1);
  val2 = digitalRead(PIN2);
  val3 = digitalRead(PIN3);
  Serial.print(val1); 
  Serial.print(val2); 
  Serial.print(val3); 
  Serial.println(""); 

  Serial.println(DataRecu);

  appendPayload("Bouton1", val1); 
  appendPayload("Bouton2", val2); 
  appendPayload("Bouton3", val3); 
  sendPayload();
  delay(1000);
  colorWipe(RGB_Strip.Color(Rouge, Green, Blue), 1000);  // Red 

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint16_t wait) {
  for (uint16_t i = 0; i < RGB_Strip.numPixels(); i++) {
    RGB_Strip.setPixelColor(i, c);
    RGB_Strip.show();
    delay(wait);
  }
}