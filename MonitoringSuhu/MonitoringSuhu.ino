#include "DHT.h"
#define DHTPIN 9
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
unsigned long mlsOfDHT = 0;
int dhtLogT[20];
int dhtLogH[20];
int dhtLogHI[20];

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
bool displayUpdate = true;

const int button = 2;
bool buttonReady = true;
int page = 1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("DHT22 test!"));
  dht.begin();
  
  pinMode(button, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.display();
  delay(500); // Pause for 2 seconds
}

void loop() {
  if( millis() > mlsOfDHT){
    master_dht();
    displayUpdate = true;
    mlsOfDHT = millis()+3000;
    Serial.println("");
  }
  if(displayUpdate == true){
    master_ssd1306();
  }
  if(buttonReady == true && !digitalRead(button) == true){
    //Serial.println("Button Press");
    tone(8,2500,100);
    page+=1;
    if(page>4){
      page = 1;
    }
    displayUpdate = true;
    buttonReady = false;
  }
  if(buttonReady == false){
    delay(300);
    buttonReady = true;
  }
}
