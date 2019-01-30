#include <Adafruit_GFX.h>
#include <FastLED.h>
#include <FastLED_NeoMatrix.h>

#define ARRAYSIZE(a) (sizeof(a) / sizeof(*a))

#define M_WIDTH 	75	// the width of the LED matrix
#define M_HEIGHT	8	// the height of the LED matrix
#define NUM_LEDS	(M_WIDTH*M_HEIGHT)

static CRGB leds[NUM_LEDS];
static FastLED_NeoMatrix matrix = FastLED_NeoMatrix(leds, M_WIDTH, M_HEIGHT, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS);

void setup()
{
	FastLED.addLeds<SDL, M_WIDTH, M_HEIGHT>(leds, NUM_LEDS);
	FastLED.setCorrection(TypicalLEDStrip);

	matrix.begin();

	Serial.println("Hello World!");
}

static const uint16_t colors[] = {
	matrix.Color(255, 0, 0),
	matrix.Color(0, 255, 0),
	matrix.Color(0, 0, 255)};

void loop()
{
	static unsigned pass;
	static int x = matrix.width();

	matrix.clear();
	matrix.setCursor(x, 0);
	matrix.print("Hello World!");

	if (--x < -(15*6)) { // roughly the width of the string
		x = matrix.width();
		if (++pass >= ARRAYSIZE(colors))
			pass = 0;
		matrix.setTextColor(colors[pass]);
	}

	matrix.show();
	delay(30);
}
