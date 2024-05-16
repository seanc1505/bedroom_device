#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

// U8G2 Constructor for SPI mode
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 52, /* data=*/ 51, /* cs=*/ 53, /* reset=*/ 49);

void setup() {
  u8g2.begin();
}

void loop() {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 24, "Hello World!");
  } while (u8g2.nextPage());
  delay(1000);
}
