/*********************************************************************
Class for Monochrome OLEDs based on SSD1306 drivers

Ported to wpilib I2C from the Adafruit SSD1306 Library by Cole Brinsfield

Adafruit library written by Limor Fried/Ladyada for Adafruit Industries.
*********************************************************************/

#include <stdlib.h>

#include "Adafruit_GFX.h"
#include "GreyOLED.h"

// the memory buffer for the LCD

static uint8_t buffer[SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0,
    0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xF8, 0xE0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80,
    0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0xFF,
    0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
    0x80, 0x80, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0x80, 0x80, 0x00, 0x80, 0x80,
    0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x80, 0x00, 0x00, 0x8C, 0x8E, 0x84, 0x00, 0x00, 0x80, 0xF8,
    0xF8, 0xF8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
    0xF0, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0xE0, 0xFC, 0xFE,
    0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE,
    0xFF, 0xC7, 0x01, 0x01, 0x01, 0x01, 0x83, 0xFF, 0xFF, 0x00, 0x00, 0x7C,
    0xFE, 0xC7, 0x01, 0x01, 0x01, 0x01, 0x83, 0xFF, 0xFF, 0xFF, 0x00, 0x38,
    0xFE, 0xC7, 0x83, 0x01, 0x01, 0x01, 0x83, 0xC7, 0xFF, 0xFF, 0x00, 0x00,
    0x01, 0xFF, 0xFF, 0x01, 0x01, 0x00, 0xFF, 0xFF, 0x07, 0x01, 0x01, 0x01,
    0x00, 0x00, 0x7F, 0xFF, 0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x7F, 0x00,
    0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x0F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xE7, 0xC7, 0xC7, 0x8F, 0x8F, 0x9F, 0xBF, 0xFF, 0xFF, 0xC3, 0xC0, 0xF0,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
    0xFC, 0xF8, 0xF8, 0xF0, 0xF0, 0xE0, 0xC0, 0x00, 0x01, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03,
    0x03, 0x03, 0x01, 0x01, 0x03, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03,
    0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,
    0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x01, 0x03, 0x01,
    0x00, 0x00, 0x00, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
    0xC0, 0xE0, 0xF0, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x1F, 0x0F,
    0x87, 0xC7, 0xF7, 0xFF, 0xFF, 0x1F, 0x1F, 0x3D, 0xFC, 0xF8, 0xF8, 0xF8,
    0xF8, 0x7C, 0x7D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F,
    0x3F, 0x0F, 0x07, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x1F, 0x7F,
    0xFF, 0xFF, 0xF8, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF8, 0xE0,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFE, 0xFE, 0x00, 0x00, 0x00, 0xFC, 0xFE, 0xFC, 0x0C, 0x06, 0x06, 0x0E,
    0xFC, 0xF8, 0x00, 0x00, 0xF0, 0xF8, 0x1C, 0x0E, 0x06, 0x06, 0x06, 0x0C,
    0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFC,
    0xFE, 0xFC, 0x00, 0x18, 0x3C, 0x7E, 0x66, 0xE6, 0xCE, 0x84, 0x00, 0x00,
    0x06, 0xFF, 0xFF, 0x06, 0x06, 0xFC, 0xFE, 0xFC, 0x0C, 0x06, 0x06, 0x06,
    0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0xC0, 0xF8, 0xFC, 0x4E, 0x46, 0x46,
    0x46, 0x4E, 0x7C, 0x78, 0x40, 0x18, 0x3C, 0x76, 0xE6, 0xCE, 0xCC, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x1F,
    0x1F, 0x3F, 0x3F, 0x3F, 0x3F, 0x1F, 0x0F, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00,
    0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00,
    0x03, 0x07, 0x0E, 0x0C, 0x18, 0x18, 0x0C, 0x06, 0x0F, 0x0F, 0x0F, 0x00,
    0x00, 0x01, 0x0F, 0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07, 0x01, 0x00, 0x04,
    0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00,
    0x00, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F,
    0x00, 0x00, 0x00, 0x07, 0x07, 0x0C, 0x0C, 0x18, 0x1C, 0x0C, 0x06, 0x06,
    0x00, 0x04, 0x0E, 0x0C, 0x18, 0x0C, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00};

#define ssd1306_swap(a, b) \
    {                      \
        int16_t t = a;     \
        a = b;             \
        b = t;             \
    }

// the most basic function, set a single pixel
void GreyOLED::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if ((x < 0) || (x >= width()) || (y < 0) || (y >= height()))
        return;

    // check rotation, move pixel around if necessary
    switch (getRotation()) {
        case 1:
            ssd1306_swap(x, y);
            x = WIDTH - x - 1;
            break;
        case 2:
            x = WIDTH - x - 1;
            y = HEIGHT - y - 1;
            break;
        case 3:
            ssd1306_swap(x, y);
            y = HEIGHT - y - 1;
            break;
    }

    // x is which column
    switch (color) {
        case WHITE:
            buffer[x + (y / 8) * SSD1306_LCDWIDTH] |= (1 << (y & 7));
            break;
        case BLACK:
            buffer[x + (y / 8) * SSD1306_LCDWIDTH] &= ~(1 << (y & 7));
            break;
        case INVERSE:
            buffer[x + (y / 8) * SSD1306_LCDWIDTH] ^= (1 << (y & 7));
            break;
    }
}

// initializer for I2C - we only indicate the reset pin!
GreyOLED::GreyOLED(int8_t reset)
        : Adafruit_GFX(SSD1306_LCDWIDTH, SSD1306_LCDHEIGHT) {
    sclk = dc = cs = sid = -1;
    rst = new DigitalOutput(reset);
}

void GreyOLED::begin(uint8_t vccstate, uint8_t i2caddr, bool reset) {
    _vccstate = vccstate;
    _i2caddr = i2caddr;
    i2c = frc::I2C(PORT, _i2caddr);

    if ((reset) && (rst >= 0)) {
        // Setup reset pin direction (used by both SPI and I2C)
        rst.Set(true);
        // VDD (3.3V) goes high at start, lets just chill for a ms
        delay(1);
        // bring reset low
        rst.Set(false);
        // wait 10ms
        delay(10);
        // bring out of reset
        rst.Set(true);
        // turn on VCC (9V?)
    }

    // Init sequence
    ssd1306_command(SSD1306_DISPLAYOFF);          // 0xAE
    ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);  // 0xD5
    ssd1306_command(0x80);                        // the suggested ratio 0x80

    ssd1306_command(SSD1306_SETMULTIPLEX);  // 0xA8
    ssd1306_commandigitalWrite(rst, HIGH);
    d(SSD1306_LCDHEIGHT - 1);

    ssd1306_command(SSD1306_SETDISPLAYOFFSET);    // 0xD3
    ssd1306_command(0x0);                         // no offset
    ssd1306_command(SSD1306_SETSTARTLINE | 0x0);  // line #0
    ssd1306_command(SSD1306_CHARGEPUMP);          // 0x8D
    if (vccstate == SSD1306_EXTERNALVCC) {
        ssd1306_command(0x10);
    }
    else {
        ssd1306_command(0x14);
    }
    ssd1306_command(SSD1306_MEMORYMODE);  // 0x20
    ssd1306_command(0x00);                // 0x0 act like ks0108
    ssd1306_command(SSD1306_SEGREMAP | 0x1);
    ssd1306_command(SSD1306_COMSCANDEC);
    ssd1306_command(SSD1306_SETCOMPINS);  // 0xDA
    ssd1306_command(0x12);
    ssd1306_command(SSD1306_SETCONTRAST);  // 0x81
    if (vccstate == SSD1306_EXTERNALVCC) {
        ssd1306_command(0x9F);
    }
    else {
        ssd1306_command(0xCF);
    }
    ssd1306_command(SSD1306_SETPRECHARGE);  // 0xd9
    if (vccstate == SSD1306_EXTERNALVCC) {
        ssd1306_command(0x22);
    }
    else {
        ssd1306_command(0xF1);
    }
    ssd1306_command(SSD1306_SETVCOMDETECT);  // 0xDB
    ssd1306_command(0x40);
    ssd1306_command(SSD1306_DISPLAYALLON_RESUME);  // 0xA4
    ssd1306_command(SSD1306_NORMALDISPLAY);        // 0xA6

    ssd1306_command(SSD1306_DEACTIVATE_SCROLL);

    ssd1306_command(SSD1306_DISPLAYON);  //--turn on oled panel
}

void GreyOLED::invertDisplay(uint8_t i) {
    if (i) {
        ssd1306_command(SSD1306_INVERTDISPLAY);
    }
    else {
        ssd1306_command(SSD1306_NORMALDISPLAY);
    }
}

void GreyOLED::ssd1306_command(uint8_t c) {
    // I2C
    uint8_t control = 0x00;  // Co = 0, D/C = 0
    i2c->WriteBulk({control, c}, sizeof(control) + sizeof(c));
}

// startscrollright
// Activate a right handed scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F)
void GreyOLED::startscrollright(uint8_t start, uint8_t stop) {
    ssd1306_command(SSD1306_RIGHT_HORIZONTAL_SCROLL);
    ssd1306_command(0X00);
    ssd1306_command(start);
    ssd1306_command(0X00);
    ssd1306_command(stop);
    ssd1306_command(0X00);
    ssd1306_command(0XFF);
    ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

// startscrollleft
// Activate a right handed scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F)
void GreyOLED::startscrollleft(uint8_t start, uint8_t stop) {
    ssd1306_command(SSD1306_LEFT_HORIZONTAL_SCROLL);
    ssd1306_command(0X00);
    ssd1306_command(start);
    ssd1306_command(0X00);
    ssd1306_command(stop);
    ssd1306_command(0X00);
    ssd1306_command(0XFF);
    ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

// startscrolldiagright
// Activate a diagonal scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F)
void GreyOLED::startscrolldiagright(uint8_t start, uint8_t stop) {
    ssd1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
    ssd1306_command(0X00);
    ssd1306_command(SSD1306_LCDHEIGHT);
    ssd1306_command(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);
    ssd1306_command(0X00);
    ssd1306_command(start);
    ssd1306_command(0X00);
    ssd1306_command(stop);
    ssd1306_command(0X01);
    ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

// startscrolldiagleft
// Activate a diagonal scroll for rows start through stop
// Hint, the display is 16 rows tall. To scroll the whole display, run:
// display.scrollright(0x00, 0x0F)
void GreyOLED::startscrolldiagleft(uint8_t start, uint8_t stop) {
    ssd1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);
    ssd1306_command(0X00);
    ssd1306_command(SSD1306_LCDHEIGHT);
    ssd1306_command(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
    ssd1306_command(0X00);
    ssd1306_command(start);
    ssd1306_command(0X00);
    ssd1306_command(stop);
    ssd1306_command(0X01);
    ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

void GreyOLED::stopscroll(void) {
    ssd1306_command(SSD1306_DEACTIVATE_SCROLL);
}

// Dim the display
// dim = true: display is dimmed
// dim = false: display is normal
void GreyOLED::dim(boolean dim) {
    uint8_t contrast;

    if (dim) {
        contrast = 0;  // Dimmed display
    }
    else {
        if (_vccstate == SSD1306_EXTERNALVCC) {
            contrast = 0x9F;
        }
        else {
            contrast = 0xCF;
        }
    }
    // the range of contrast to too small to be really useful
    // it is useful to dim the display
    ssd1306_command(SSD1306_SETCONTRAST);
    ssd1306_command(contrast);
}

void GreyOLED::display(void) {
    ssd1306_command(SSD1306_COLUMNADDR);
    ssd1306_command(0);                     // Column start address (0 = reset)
    ssd1306_command(SSD1306_LCDWIDTH - 1);  // Column end address (127 = reset)

    ssd1306_command(SSD1306_PAGEADDR);
    ssd1306_command(0);  // Page start address (0 = reset)
#if SSD1306_LCDHEIGHT == 64
    ssd1306_command(7);  // Page end address
#endif
#if SSD1306_LCDHEIGHT == 32
    ssd1306_command(3);  // Page end address
#endif
#if SSD1306_LCDHEIGHT == 16
    ssd1306_command(1);  // Page end address
#endif

    // save I2C bitrate
#ifdef TWBR
    uint8_t twbrbackup = TWBR;
    TWBR = 12;  // upgrade to 400KHz!
#endif

    // Serial.println(TWBR, DEC);
    // Serial.println(TWSR & 0x3, DEC);

    // I2C
    for (uint16_t i = 0; i < (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8); i++) {
        // send a bunch of data in one xmission
        i2c->WriteBulk({0x40}, sizeof(0x40));
        for (uint8_t x = 0; x < 16; x++) {
            i2c->WriteBulk({buffer[i]}, sizeof(buffer[i]));
            i++;
        }
        i--;
    }
#ifdef TWBR
    TWBR = twbrbackup;
#endif
}

// clear everything
void GreyOLED::clearDisplay(void) {
    memset(buffer, 0, (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8));
}

void GreyOLED::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    boolean bSwap = false;
    switch (rotation) {
        case 0:
            // 0 degree rotation, do nothing
            break;
        case 1:
            // 90 degree rotation, swap x & y for rotation, then invert x
            bSwap = true;
            ssd1306_swap(x, y);
            x = WIDTH - x - 1;
            break;
        case 2:
            // 180 degree rotation, invert x and y - then shift y around for
            // height.
            x = WIDTH - x - 1;
            y = HEIGHT - y - 1;
            x -= (w - 1);
            break;
        case 3:
            // 270 degree rotation, swap x & y for rotation, then invert y  and
            // adjust y for w (not to become h)
            bSwap = true;
            ssd1306_swap(x, y);
            y = HEIGHT - y - 1;
            y -= (w - 1);
            break;
    }

    if (bSwap) {
        drawFastVLineInternal(x, y, w, color);
    }
    else {
        drawFastHLineInternal(x, y, w, color);
    }
}

void GreyOLED::drawFastHLineInternal(int16_t x, int16_t y, int16_t w,
                                     uint16_t color) {
    // Do bounds/limit checks
    if (y < 0 || y >= HEIGHT) {
        return;
    }

    // make sure we don't try to draw below 0
    if (x < 0) {
        w += x;
        x = 0;
    }

    // make sure we don't go off the edge of the display
    if ((x + w) > WIDTH) {
        w = (WIDTH - x);
    }

    // if our width is now negative, punt
    if (w <= 0) {
        return;
    }

    // set up the pointer for  movement through the buffer
    register uint8_t *pBuf = buffer;
    // adjust the buffer pointer for the current row
    pBuf += ((y / 8) * SSD1306_LCDWIDTH);
    // and offset x columns in
    pBuf += x;

    register uint8_t mask = 1 << (y & 7);

    switch (color) {
        case WHITE:
            while (w--) {
                *pBuf++ |= mask;
            };
            break;
        case BLACK:
            mask = ~mask;
            while (w--) {
                *pBuf++ &= mask;
            };
            break;
        case INVERSE:
            while (w--) {
                *pBuf++ ^= mask;
            };
            break;
    }
}

void GreyOLED::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    bool bSwap = false;
    switch (rotation) {
        case 0:
            break;
        case 1:
            // 90 degree rotation, swap x & y for rotation, then invert x and
            // adjust x for h (now to become w)
            bSwap = true;
            ssd1306_swap(x, y);
            x = WIDTH - x - 1;
            x -= (h - 1);
            break;
        case 2:
            // 180 degree rotation, invert x and y - then shift y around for
            // height.
            x = WIDTH - x - 1;
            y = HEIGHT - y - 1;
            y -= (h - 1);
            break;
        case 3:
            // 270 degree rotation, swap x & y for rotation, then invert y
            bSwap = true;
            ssd1306_swap(x, y);
            y = HEIGHT - y - 1;
            break;
    }

    if (bSwap) {
        drawFastHLineInternal(x, y, h, color);
    }
    else {
        drawFastVLineInternal(x, y, h, color);
    }
}

void GreyOLED::drawFastVLineInternal(int16_t x, int16_t __y, int16_t __h,
                                     uint16_t color) {
    // do nothing if we're off the left or right side of the screen
    if (x < 0 || x >= WIDTH) {
        return;
    }

    // make sure we don't try to draw below 0
    if (__y < 0) {
        // __y is negative, this will subtract enough from __h to account for
        // __y being 0
        __h += __y;
        __y = 0;
    }

    // make sure we don't go past the height of the display
    if ((__y + __h) > HEIGHT) {
        __h = (HEIGHT - __y);
    }

    // if our height is now negative, punt
    if (__h <= 0) {
        return;
    }

    // this display doesn't need ints for coordinates, use local byte registers
    // for faster juggling
    register uint8_t y = __y;
    register uint8_t h = __h;

    // set up the pointer for fast movement through the buffer
    register uint8_t *pBuf = buffer;
    // adjust the buffer pointer for the current row
    pBuf += ((y / 8) * SSD1306_LCDWIDTH);
    // and offset x columns in
    pBuf += x;

    // do the first partial byte, if necessary - this requires some masking
    register uint8_t mod = (y & 7);
    if (mod) {
        // mask off the high n bits we want to set
        mod = 8 - mod;

        // note - lookup table results in a nearly 10% performance improvement
        // in fill* functions register uint8_t mask = ~(0xFF >> (mod));
        static uint8_t premask[8] = {0x00, 0x80, 0xC0, 0xE0,
                                     0xF0, 0xF8, 0xFC, 0xFE};
        register uint8_t mask = premask[mod];

        // adjust the mask if we're not going to reach the end of this byte
        if (h < mod) {
            mask &= (0XFF >> (mod - h));
        }

        switch (color) {
            case WHITE:
                *pBuf |= mask;
                break;
            case BLACK:
                *pBuf &= ~mask;
                break;
            case INVERSE:
                *pBuf ^= mask;
                break;
        }

        // fast exit if we're done here!
        if (h < mod) {
            return;
        }

        h -= mod;

        pBuf += SSD1306_LCDWIDTH;
    }

    // write solid bytes while we can - effectively doing 8 rows at a time
    if (h >= 8) {
        if (color == INVERSE) {  // separate copy of the code so we don't impact
                                 // performance of the black/white write version
                                 // with an extra comparison per loop
            do {
                *pBuf = ~(*pBuf);

                // adjust the buffer forward 8 rows worth of data
                pBuf += SSD1306_LCDWIDTH;

                // adjust h & y (there's got to be a faster way for me to do
                // this, but this should still help a fair bit for now)
                h -= 8;
            } while (h >= 8);
        }
        else {
            // store a local value to work with
            register uint8_t val = (color == WHITE) ? 255 : 0;

            do {
                // write our value in
                *pBuf = val;

                // adjust the buffer forward 8 rows worth of data
                pBuf += SSD1306_LCDWIDTH;

                // adjust h & y (there's got to be a faster way for me to do
                // this, but this should still help a fair bit for now)
                h -= 8;
            } while (h >= 8);
        }
    }

    // now do the final partial byte, if necessary
    if (h) {
        mod = h & 7;
        // this time we want to mask the low bits of the byte, vs the high bits
        // we did above register uint8_t mask = (1 << mod) - 1; note - lookup
        // table results in a nearly 10% performance improvement in fill*
        // functions
        static uint8_t postmask[8] = {0x00, 0x01, 0x03, 0x07,
                                      0x0F, 0x1F, 0x3F, 0x7F};
        register uint8_t mask = postmask[mod];
        switch (color) {
            case WHITE:
                *pBuf |= mask;
                break;
            case BLACK:
                *pBuf &= ~mask;
                break;
            case INVERSE:
                *pBuf ^= mask;
                break;
        }
    }
}
