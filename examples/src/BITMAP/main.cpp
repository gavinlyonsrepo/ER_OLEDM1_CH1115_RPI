
// Example file name : main.cpp
// Description:
// Test file for ER_OLEDM1_CH1115 library, showing how to display bitmaps.
// URL: https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115_RPI
// *****************************

#include <bcm2835.h>
#include "ER_OLEDM1_CH1115.h"
#include <time.h>
#include <stdio.h>

#define OLEDcontrast 0x80 //Constrast 00 to FF , 0x80 is default. 
#define myOLEDwidth  128
#define myOLEDheight 64

// GPIO 
#define RES 25 // GPIO pin number pick any you want
#define DC 24 // GPIO pin number pick any you want 

ERMCH1115 myOLED(myOLEDwidth ,myOLEDheight, RES, DC); // instantiate an object 

// =============== Function prototype ================
void setup(void);
void myLoop(void);
void Test1(void);
void Test2(void);
void Test3(void);
void Test4(void);
void EndTest(void);

// ======================= Main ===================
int main(int argc, char **argv) 
{
	if(!bcm2835_init())
	{
		return -1;
	}

	setup();
	myLoop();
	EndTest();
	return 0;
}

// ' 128x64px "g lyons" + shapes , 
// SW used to make https://javl.github.io/image2cpp/ vertical addressing
uint8_t  fullScreenBuffer[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x60, 0x60, 0x20, 0x20, 0x20, 0x20, 0x60,
	0x40, 0xc0, 0xc0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0xe0, 0xe0, 0xe0, 0x20, 0x20, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xf8, 0xfe, 0xff, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x20, 0x60, 0xe1, 0xe7, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x38, 0xf8, 0xf8, 0xc8, 0x00, 0x00,
	0x00, 0x00, 0xc8, 0x78, 0x08, 0x00, 0x00, 0xc0, 0xe0, 0x70, 0x10, 0x08, 0x08, 0x08, 0x08, 0x18,
	0x70, 0xe0, 0xc0, 0x00, 0x00, 0x10, 0xf0, 0xf8, 0xf8, 0x20, 0x10, 0x18, 0x18, 0x38, 0xf8, 0xf0,
	0x00, 0x00, 0x00, 0x00, 0xf0, 0xd8, 0x88, 0x08, 0x08, 0x08, 0x38, 0x00, 0x00, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x03, 0x0f, 0x1f, 0x3e, 0x70, 0x60, 0x40, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80,
	0xc0, 0x60, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x3e, 0xf8,
	0x70, 0x0e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0x7e, 0x60, 0xc0, 0x80, 0x80, 0x80, 0xc0,
	0x60, 0x3f, 0x1f, 0x02, 0x00, 0x80, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff,
	0x80, 0x00, 0x00, 0x00, 0xe1, 0x83, 0x83, 0x87, 0x86, 0x8e, 0x7c, 0x38, 0x00, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x38, 0x30, 0x18, 0x06, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xff, 0xff, 0x06, 0x06, 0x06,
	0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6,
	0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6, 0xf6,
	0xf6, 0xf6, 0xf6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0xff, 0xff, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xff, 0xff, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x1f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
	0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
	0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c,
	0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c,
	0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1f, 0x1f, 0x1f, 0x1f, 0x00
};

// 'small image', 20x20px vertical addressing
uint8_t smallImage  [] = {
	0xff, 0x3f, 0x0f, 0x07, 0x03, 0x13, 0x33, 0x39, 0x39, 0x79, 0xf9, 0xf9, 0xfb, 0xf3, 0xf7, 0xe3,
	0x87, 0x0f, 0x1f, 0xff, 0xf9, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f,
	0x1d, 0x19, 0x10, 0x19, 0x0f, 0x00, 0xc0, 0xf0, 0x0f, 0x0f, 0x0f, 0x0e, 0x0c, 0x0c, 0x08, 0x08,
	0x08, 0x00, 0x00, 0x08, 0x08, 0x08, 0x0c, 0x0c, 0x0e, 0x0f, 0x0f, 0x0f
};

 // 'small Bitmap', 20x20px bitmap bi-colour Vertical addressed Test 3
const uint8_t  smallBitmap [60] = {
	0xff, 0x3f, 0x0f, 0x07, 0x03, 0x13, 0x33, 0x39, 0x39, 0x79, 0xf9, 0xf9, 
	0xfb, 0xf3, 0xf7, 0xe3, 0x87, 0x0f, 0x1f, 0xff, 0xf9, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x1d, 0x19, 0x10, 0x19, 
	0x0f, 0x00, 0xc0, 0xf0, 0x0f, 0x0f, 0x0f, 0x0e, 0x0c, 0x0c, 0x08, 0x08,
	0x08, 0x00, 0x00, 0x08, 0x08, 0x08, 0x0c, 0x0c, 0x0e, 0x0f, 0x0f, 0x0f
};

 // 'small BitmapHA', 20x20px bitmap bi-colour horizontal addressed Test 4
const uint8_t smallBitmapHa[60] = {
	0xff, 0xff, 0xf0, 0xfe, 0x0f, 0xf0, 0xf0, 0x02, 0xf0, 0xe1, 0xf8, 0x70,
	0xc7, 0xfe, 0x30, 0xc3, 0xff, 0x10, 0x80, 0x7f, 0x10, 0x80, 0x3f, 0x90,
	0x80, 0x3d, 0x80, 0x00, 0x30, 0x80, 0x00, 0x18, 0x80, 0x80, 0x1d, 0x80,
	0x80, 0x0f, 0x10, 0x80, 0x00, 0x10, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0x30,
	0xe0, 0x00, 0x70, 0xf0, 0x00, 0xf0, 0xfc, 0x03, 0xf0, 0xff, 0x9f, 0xf0
};

void EndTest(void)
{
	myOLED.OLEDPowerDown();
	bcm2835_close(); // Close the library, 
	printf("OLED End\r\n");
}


void setup()
{
	printf("OLED Begin\r\n");
	bcm2835_delay(50);
	myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
	myOLED.OLEDFillScreen(0xFF); // Clears screen
	bcm2835_delay(2000);
	myOLED.OLEDFillScreen(0x00); 
}

void myLoop()
{
	Test1(); // Method (1) OLED bitmap method, writes to screen directly
	Test2(); // Method (2) Assign bitmap to a buffer at init
	Test3(); // Method (3) Drawbitmap to buffer method, vertical addressing
	Test4(); // Method (4) Drawbitmap to buffer method, horizontal addressing
}


void Test1(void)
{
	// Method (1) OLED bitmap method, write bitmap directly to screen
	myOLED.OLEDBitmap(5, 5 , 20, 20, smallImage );
	bcm2835_delay(5000);
	myOLED.OLEDFillScreen(0x00); 
}


void Test2(void)
{
	// Method (2) assign bitmap to a buffer at init
	MultiBuffer Whole_screen;
	// Intialise that struct with buffer details (&struct,  buffer, w, h, x-offset,y-offset)
	myOLED.OLEDinitBufferStruct(&Whole_screen, fullScreenBuffer, myOLEDwidth, myOLEDheight, 0, 0);
	
	myOLED.ActiveBuffer = &Whole_screen;
	
	myOLED.OLEDupdate();
	bcm2835_delay(5000);
	myOLED.OLEDFillScreen(0x00); 
}


void Test3(void)
{
	MultiBuffer MyStruct;
	// Intialise that struct (&struct,buffer,w,h,x,y)
	myOLED.OLEDinitBufferStruct(&MyStruct, fullScreenBuffer, 128, 64, 0, 0);  
	myOLED.ActiveBuffer = &MyStruct;
	myOLED.OLEDclearBuffer();   // Clear active buffer

	myOLED.setDrawBitmapAddr(true); // for Bitmap Data Vertical  addressed
	myOLED.drawBitmap(0, 0, smallBitmap, 20, 20, FOREGROUND, BACKGROUND);
	myOLED.drawBitmap(30, 20, smallBitmap, 20, 20, BACKGROUND, FOREGROUND);

	myOLED.OLEDupdate();
	bcm2835_delay(5000);
}

void Test4(void)
 {
	MultiBuffer MyStruct;
	// Intialise that struct (&struct,buffer,w,h,x,y)
	myOLED.ActiveBuffer = &MyStruct;
	myOLED.OLEDinitBufferStruct(&MyStruct, fullScreenBuffer, 128, 64, 0, 0);  // Intialise that struct (&struct,buffer,w,h,x,y)
	myOLED.ActiveBuffer = &MyStruct;
	myOLED.OLEDclearBuffer();   // Clear active buffer

	myOLED.setDrawBitmapAddr(false); // for Bitmap Data Horziontal addressed
	myOLED.drawBitmap(10, 25, smallBitmapHa, 20, 20, FOREGROUND, BACKGROUND);
	myOLED.drawBitmap(100, 20, smallBitmapHa, 20, 20, BACKGROUND, FOREGROUND);
	myOLED.drawBitmap(60, 20, smallBitmapHa, 20, 20, BACKGROUND, FOREGROUND);
	myOLED.OLEDupdate();
	bcm2835_delay(5000);
}
