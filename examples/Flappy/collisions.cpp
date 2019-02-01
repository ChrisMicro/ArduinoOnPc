#include "collisions.h"
#include "constants.h"
#include "TFT_LinuxWrapper.h" // TFT

void checkCollision(
    int fx, int fy,
    int pillarPos, int gapPos,
    int score,
    bool *crashed,
    bool *running,
    TFT_LinuxWrapper tft) {
  // Collision with ground
  if (fy > 206) *crashed = true;

  // Collision with pillar
  if (fx + 34 > pillarPos && fx < pillarPos + 50)
    if (fy < gapPos || fy + 24 > gapPos + 90)
      *crashed = true;

  if (*crashed) {
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.setCursor(75, 75);
    tft.print("Game Over!");
    tft.setCursor(75, 125);
    tft.print("Score:");
    tft.setCursor(220, 125);
    tft.print(score);

    // stop animation
    *running = false;

    // delay to stop any last minute clicks from restarting immediately
    delay(1000);
  }
}