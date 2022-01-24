#include "OLED.h";

// The SSD1331 is connected like this (plus VCC plus GND)
const uint8_t   OLED_pin_scl_sck        = 14;
const uint8_t   OLED_pin_sda_mosi       = 13;
const uint8_t   OLED_pin_cs_ss          = 15;
const uint8_t   OLED_pin_res_rst        = 4;
const uint8_t   OLED_pin_dc_rs          = 16;


// SSD1331 color definitions
const uint16_t  OLED_Color_Black        = 0x0000;
const uint16_t  OLED_Color_Blue         = 0x001F;
const uint16_t  OLED_Color_Red          = 0xF800;
const uint16_t  OLED_Color_Green        = 0x07E0;
const uint16_t  OLED_Color_Cyan         = 0x07FF;
const uint16_t  OLED_Color_Magenta      = 0xF81F;
const uint16_t  OLED_Color_Yellow       = 0xFFE0;
const uint16_t  OLED_Color_White        = 0xFFFF;

// The colors we actually want to use
uint16_t        OLED_Background_Color         = OLED_Color_Black;
uint16_t        OLED_Text_Color    = OLED_Color_Blue;

// declare the display
Adafruit_SSD1331 oled =
    Adafruit_SSD1331(
        OLED_pin_cs_ss,
        OLED_pin_dc_rs,
        OLED_pin_sda_mosi,
        OLED_pin_scl_sck,
        OLED_pin_res_rst
     );

// assume the display is off until configured in setup()
bool            isDisplayVisible        = false;

// declare size of working string buffers. Basic strlen("d hh:mm:ss") = 10
const size_t    MaxString               = 16;


void OLEDsetup() {


    // initialise the SSD1331
    oled.begin();
    oled.setFont();
    oled.fillScreen(OLED_Background_Color);
    oled.setTextColor(OLED_Text_Color);
    oled.setTextSize(2);

    

    // the display is now on
    isDisplayVisible = true;

}

void printStatus(int Status){
   oled.clear();
   oled.setCursor(0,0);
  switch(Status) {
    case 1:
      oled.print("TUMBADO");
      break;
    case 2:
      oled.print("SENTADO");
      break;
    case 3:
      oled.print("DE PIE");
      break;
    case 4:
      oled.print("CORRIENDO");
      break;
    case 5:
      oled.print("ANDANDO");
      break;
    default:
      oled.print("Desconocido");
      break;
  }
}   
