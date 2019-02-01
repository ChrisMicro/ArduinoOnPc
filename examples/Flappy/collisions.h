#include <stdbool.h>
#include "TFT_LinuxWrapper.h" // TFT

void checkCollision (
    int fx, int fy,
    int pillarPos, int gapPos,
    int score,
    bool *crashed,
    bool *running,
    TFT_LinuxWrapper tft
);