#include "Arduino.h"
#include SKETCH_FILE

int main(int argc, char** argv) {

	setup();

	while (1) {
		loop();
		delay(5);
	}

	return 0;
}
