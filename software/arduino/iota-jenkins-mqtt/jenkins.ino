const uint8_t BUILD_SUCCESS = 0;
const uint8_t BUILD_FAIL = 1;
const uint8_t BUILD_UNSTABLE = 2;
const uint8_t BUILD_UNKNOWN = 3;

uint8_t getBuildStatus(char* response) {
  return stringToStatus(response);
}

uint8_t stringToStatus(const char* str) {
  if (strcmp("SUCCESS", str) == 0) {
    return BUILD_SUCCESS;
  }
  if (strcmp("UNSTABLE", str) == 0) {
    return BUILD_UNSTABLE;
  }
  if (strcmp("FAILURE", str) == 0) {
    return BUILD_FAIL;
  }
  return BUILD_UNKNOWN;
}

void statusColor(uint8_t ledno, uint8_t status) {
  switch (status) {
    case BUILD_SUCCESS:
      leds[ledno] = CRGB::Green;
      break;
    case BUILD_FAIL:
      leds[ledno] = CRGB::Red;
      break;
    case BUILD_UNSTABLE:
      leds[ledno] = CRGB::Yellow;
      break;
    default:
      leds[ledno] = CRGB::Black;
      break;
  }
  FastLED.show();
}


