#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
String inData;

void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Ready to receive");
    Serial.print("Ready to Receive");
    
}

void loop() {


    while (Serial.available() > 0) {
        char recieved = Serial.read();
        inData += recieved;

        if(recieved == '^') {
          inData.remove(inData.length() - 1, 1);
            lcd.setCursor(0,0);
            lcd.print("RAM:" + inData + char(223));
            Serial.print("Sent ram values");
            inData = "";

            if(inData == "DIS") {   
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Disconnected!");
              Serial.print("Disconnected");
            }
        }
        
        if (recieved == '*') {
            inData.remove(inData.length() - 1, 1);
            lcd.setCursor(9,0);
            lcd.print("HDD: " + inData + char(223));
            inData = ""; 
            
            if(inData == "DIS") {   
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Disconnected!");
            }
        } 
        
        if (recieved == '#') {
            inData.remove(inData.length() - 1, 1);
            lcd.setCursor(0,1);
            lcd.print("CPU: " + inData + char(223));
            inData = "";
            
        }
    }
}
