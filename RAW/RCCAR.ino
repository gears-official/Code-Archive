#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

SoftwareSerial bluetoothSerial(2, 3); // RX, TX

void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  if (bluetoothSerial.available() > 0) {
    String name = bluetoothSerial.readStringUntil('\n');
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println(name);
    display.display();
  }
}