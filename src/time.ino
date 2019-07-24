void timeTick() {
  if (wifiConnected) {    
    if (timeTimer.isReady()) {
      timeClient.update();
      byte thisDay = timeClient.getDay();
      if (thisDay == 0) thisDay = 7;  // воскресенье это 0
      thisDay--;
      thisTime = timeClient.getHours() * 60 + timeClient.getMinutes();

      // проверка рассвета
      if (my_alarm[thisDay].state &&                                       // день будильника
          thisTime >= (my_alarm[thisDay].time - dawnOffsets[dawnMode]) &&  // позже начала
          thisTime < (my_alarm[thisDay].time + DAWN_TIMEOUT) ) {                      // раньше конца + минута
        if (!manualOff) {
          // величина рассвета 0-255
          int dawnPosition = 255 * ((float)(thisTime - (my_alarm[thisDay].time - dawnOffsets[dawnMode])) / dawnOffsets[dawnMode]);
          dawnPosition = constrain(dawnPosition, 0, 255);
          CHSV dawnColor = CHSV(map(dawnPosition, 0, 255, 10, 35),
                                map(dawnPosition, 0, 255, 255, 170),
                                map(dawnPosition, 0, 255, 10, DAWN_BRIGHT));
          fill_solid(leds, NUM_LEDS, dawnColor);
          FastLED.setBrightness(255);
  if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
          FastLED.show();
          dawnFlag = true;
        }
      } else {
        if (dawnFlag) {
          dawnFlag = false;
          manualOff = false;
          FastLED.setBrightness(modes[currentMode].brightness);
  if (CURRENT_LIMIT > 0) FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
        }
      }

    }
  }
}
