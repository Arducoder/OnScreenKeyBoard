#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

#define TFT_CS        13
#define TFT_RST       15
#define TFT_DC        14
#define TFT_MOSI 11 // Data out
#define TFT_SCLK 10  // Clock out
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
#define ST77XX_PURPLE 694489


int i = 0;
int i2 = 0;
String alphabet[28] = {"a", "b", "c", "e", "d", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "space"};
String letter;
String writtentext;
int cursorpt;
int stepdownpt;
int Btt1 = 2;
int Btt2 = 3;
int Btt3 = 6;
int Btt4 = 7;
void setup() {
  tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
  tft.setTextColor(0xFFFF, 0x0000);
  tft.fillScreen(ST77XX_BLACK);
  pinMode(Btt1, INPUT_PULLUP);
  pinMode(Btt2, INPUT_PULLUP);
  pinMode(Btt3, INPUT_PULLUP);
  pinMode(Btt4, INPUT_PULLUP);
  drawKeyBoard(50);
}

void loop() {
  runKeyBoard(Btt1, Btt2, Btt3, 50);
}
void drawKeyBoard (uint16_t y) {
  i = 0;
  while (i != 16) {
    tft.drawRect(i * 8, y, 8, 10, ST77XX_WHITE);
    tft.setCursor(i * 8 + 1, y + 1);
    tft.print(alphabet[i]);
    i++;
  }
  i2 = 0;
  while (i2 != 11) {

    if (i == 26) {
      tft.drawRect(i2 * 8, y + 10, 32, 10, ST77XX_WHITE);
    } else {
      tft.drawRect(i2 * 8, y + 10, 8, 10, ST77XX_WHITE);
    }
    tft.setCursor(i2 * 8 + 1, y + 11);
    tft.print(alphabet[i]);
    i++;
    i2++;
  }
}
void runKeyBoard (uint16_t btleft, uint16_t btright, uint16_t btenter, uint16_t y) {
  if (digitalRead(btleft) == 0) {
    if (cursorpt != 0) {
      cursorpt --;
        drawKeyBoard(y);
    }
  }
  if (digitalRead(btright) == 0) {
    if (cursorpt != 26) {
      cursorpt ++;
        drawKeyBoard(y);
    }
  }
  if (cursorpt < 16) {
    tft.drawRect(cursorpt * 8, y, 8, 10, ST77XX_RED);
  } else {
    stepdownpt = cursorpt - 16;
    tft.drawRect(stepdownpt * 8, y+10, 8, 10, ST77XX_RED);
  }
  if (digitalRead(btenter)==0){
    if(cursorpt==26){
      letter = " ";
    }else{
    letter = alphabet[cursorpt];
    }
    writtentext += letter;
    tft.setCursor(0,0);
    tft.print(writtentext);
    delay(100);
  }

}
