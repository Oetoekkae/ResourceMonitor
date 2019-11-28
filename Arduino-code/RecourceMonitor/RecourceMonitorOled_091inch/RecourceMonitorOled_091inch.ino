#include <U8g2lib.h>
#include <U8x8lib.h>

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);
String inData;

void setup() {
    Serial.begin(9600);
    u8g2.begin();
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_5x7_tf);  
    u8g2.drawStr(6,30,"READY TO RECEIVE");
    u8g2.sendBuffer();
    
}

void loop() {

    while (Serial.available() > 0)
    {
        char recieved = Serial.read();
        inData += recieved; 
        
        if (recieved == '*')
        {
            inData.remove(inData.length() - 1, 1);
            u8g2.clearBuffer();
            u8g2.setFont(u8g2_font_5x7_tf);  
            u8g2.drawStr(6, 30, "GPU Temp.: ");
            u8g2.drawStr(20, 30, recieved);
            u8g2.drawStr(25, 30, " C ");
            u8g2.sendBuffer();
            inData = ""; 
            
            if(inData == "DIS")
            {   
              u8g2.clearBuffer();
              u8g2.setFont(u8g2_font_5x7_tf);  
              u8g2.drawStr(6, 4, "Disconnected!");
              u8g2.sendBuffer();
            }
        } 
        
        if (recieved == '#')
        {
            u8g2.clearBuffer();
            u8g2.setFont(u8g2_font_5x7_tf);  
            //u8g2.drawStr(6, 20, "GPU Temp.: " + inData + char(223)+"C ");
            u8g2.sendBuffer();
            inData = ""; 
        }
    }
}
