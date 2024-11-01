<<<<<<< Updated upstream
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ D2, /* data=*/ D1, /* reset=*/ U8X8_PIN_NONE);  //NodeOLED用這行，或部份NodeMCU系列的板子也用這行
//U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ D2, /* data=*/ D1, /* reset=*/ U8X8_PIN_NONE);  //ESP8266板子搭配SSD1306用這行
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //Arduino搭配SSD1306(0.96" OLED)用這行
//U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //Arduino搭配SH1106(1.3" OLED)用這行
//U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//Arduino搭配SSD1306(0.91" OLED)用這行

#define imgWidth 128
#define imgHeight 48  //這裡只用到48的高度，因為上方要放文字

static const unsigned char PROGMEM logo_bmp[] =
{ 
0XFF,0XFF,0XFF,0XFF,0XFF,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XFF,0XFF,0XFF,0XFF,0XFF,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XFF,0XFF,0X1F,0XFE,0XFF,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XFF,0XFF,0X1F,0XFC,0XFF,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X7F,0XFF,0X1F,0XFC,0XFF,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X7F,0XF8,0X3F,0XFE,0XFF,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X3F,0XC0,0XBF,0XFF,0XFF,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X27,0X00,0XDF,0XFF,0XFF,0XC1,0X00,0X18,0X00,0X06,0X00,0X1C,0X40,0X00,0X00,0X00,
0X27,0X00,0XD8,0XFF,0XFF,0XC1,0X7E,0X18,0XFC,0XFF,0X03,0X7F,0XC0,0XF0,0XFF,0X3F,
0X33,0X00,0XC0,0XFF,0XFF,0XC1,0XFE,0X7F,0XFE,0XFF,0XC3,0XE3,0XCD,0XF0,0XFF,0X3F,
0X13,0X3E,0X00,0XFF,0XFF,0XC1,0X62,0X3F,0X80,0X1F,0XE0,0X7F,0XCD,0X00,0X30,0X00,
0X13,0X7F,0X00,0XF8,0XFF,0X61,0X67,0X1B,0XC0,0X7F,0X00,0X7F,0XCC,0X00,0X30,0X00,
0X99,0XFF,0X00,0XE0,0XFF,0XE1,0X2F,0X1B,0XF8,0XE6,0X01,0X00,0XCC,0X00,0X30,0X00,
0X89,0XFF,0X00,0X00,0XFF,0X71,0X38,0X1B,0X3E,0X86,0XC7,0XFF,0XCC,0X00,0X30,0X00,
0X89,0XFF,0X00,0X00,0XF8,0X71,0XD8,0X7F,0X26,0X46,0XC4,0XFF,0XCD,0X00,0X30,0X00,
0X87,0XFF,0X00,0X00,0XF8,0X79,0X8C,0X7F,0X30,0X64,0XC0,0XFF,0XCD,0X00,0X30,0X00,
0X07,0X7F,0X80,0X01,0XF8,0X79,0X87,0X18,0XFE,0XF9,0XC7,0XFF,0XCD,0X00,0X30,0X00,
0X07,0X3E,0XC0,0X07,0XFC,0X61,0XC2,0X10,0XFF,0XF9,0XC7,0X80,0XCD,0X00,0X30,0X00,
0X03,0X1C,0XE0,0X07,0XFC,0X61,0XFF,0X3F,0X30,0XE0,0XC0,0XFF,0XCD,0X00,0X30,0X00,
0X0F,0X00,0XE0,0X0F,0XF2,0X61,0XFF,0X3F,0X78,0XF0,0XC0,0XFF,0XCC,0X00,0X30,0X00,
0X7F,0X00,0XE0,0X07,0XF2,0X61,0XE0,0X01,0XFC,0XF9,0XC1,0X00,0XCC,0X00,0X30,0X00,
0XE3,0X03,0XE0,0X07,0XF9,0X61,0XF0,0X03,0XBC,0X79,0X43,0XFE,0XCC,0X00,0X30,0X00,
0X81,0X0F,0XC0,0X03,0XF9,0X61,0XFC,0X0E,0X36,0X6C,0X67,0XFE,0XC1,0X00,0X30,0X00,
0X01,0X7C,0X00,0X80,0XF9,0X61,0XCF,0X3C,0X33,0X66,0X66,0X86,0XC1,0X00,0X30,0X00,
0X03,0XE0,0X01,0X80,0XFC,0X61,0XC7,0X30,0X30,0X60,0X60,0XFE,0XC1,0XF8,0XFF,0X7F,
0X1F,0X80,0X0F,0X80,0X8C,0X61,0XC0,0X00,0X30,0X60,0X60,0XFE,0X7D,0XF8,0XFF,0X7F,
0XFD,0X00,0X7C,0XC0,0X8F,0X61,0XC0,0X00,0X20,0X40,0X00,0X82,0X38,0X00,0X00,0X00,
0XF1,0X03,0XF0,0XC1,0X8F,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X33,0X07,0X80,0XEF,0XCF,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X33,0X38,0X00,0XFC,0X8F,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XB1,0XE3,0X03,0XF0,0X0F,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X71,0X1C,0X1F,0XF0,0X1F,0XC1,0X00,0X00,0X0C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XC1,0X71,0X78,0XF0,0XFF,0X41,0X00,0X00,0X0C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X01,0X8E,0XE3,0XFB,0XCF,0X01,0X00,0X00,0X0C,0X00,0X00,0X00,0X00,0X00,0X0C,0X00,
0X01,0X38,0XE6,0XFF,0X9F,0XC1,0XBE,0XF3,0XCC,0X9C,0X07,0XC7,0XF9,0X0E,0X5E,0X64,
0X81,0XC7,0X31,0XFE,0XE3,0XC1,0X76,0X93,0X6D,0XB6,0X87,0X61,0XBB,0X1B,0XCC,0X66,
0X81,0X3F,0X1F,0XF8,0XC1,0XC1,0X66,0X86,0X3D,0XB2,0X81,0X30,0X9A,0X19,0XCC,0X2E,
0X01,0X7F,0XC8,0X38,0XE2,0XC1,0X66,0XF6,0X3D,0XBF,0XC1,0X30,0X9E,0X19,0XCC,0X2A,
0X01,0X7C,0X00,0X24,0XF6,0XC1,0X66,0X96,0X6D,0X83,0X81,0X30,0X9A,0X19,0X8C,0X3B,
0XC1,0X7C,0X00,0X26,0XFE,0XC1,0X66,0X9E,0X6D,0X86,0XB1,0X61,0X9B,0XD9,0X8C,0X19,
0XC1,0X0E,0X00,0XE2,0XFF,0XC1,0X66,0XF6,0XCD,0X9C,0X31,0XC7,0X99,0XD9,0X98,0X19,
0XE1,0X0F,0X00,0XE3,0XFF,0XC1,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XE1,0X0F,0X00,0XF1,0XFF,0X61,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X81,0X07,0X80,0XFF,0XFF,0X21,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X01,0X06,0XC0,0XFF,0XFF,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X01,0X00,0XC0,0XFF,0XFF,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X01,0X00,0XE6,0XFF,0XFF,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XFF,0XFF,0XFF,0XFF,0XFF,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00, };

void setup(void) {
  u8g2.begin();
  u8g2.enableUTF8Print();  
}

void loop(void) {
  u8g2.setFont(u8g2_font_unifont_t_chinese1); //使用我們做好的字型
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 14);
    u8g2.print(" 操你媽");
    u8g2.setCursor(0, 35);
    u8g2.print(" 起來重睡!");   
    u8g2.setCursor(0, 60);
    u8g2.print(" 時間 00:00");
  } while ( u8g2.nextPage() );
  delay(1000);
}
=======
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ D2, /* data=*/ D1, /* reset=*/ U8X8_PIN_NONE); 
//U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


void setup(void) {
  u8g2.begin();
  u8g2.enableUTF8Print();  //啟用UTF8文字的功能  
}

void loop(void) {
  u8g2.setFont(u8g2_font_unifont_t_chinese1); //使用我們做好的字型
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 14);
    u8g2.print("操你媽");
    u8g2.setCursor(0, 35);
    u8g2.print("起來重睡");   
    u8g2.setCursor(0, 60);
    u8g2.print("時間 00:00");
  } while ( u8g2.nextPage() );
  delay(1000);
}
>>>>>>> Stashed changes
