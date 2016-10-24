#define BUILD_SUCCESS   0
#define BUILD_FAIL      1
#define BUILD_ABORTED   2
#define BUILD_UNSTABLE  3
#define BUILD_UNKNOWN   4
#define BUILD_UPDATING  8

short stringToStatus(const char* str) {
  if (strcmp("SUCCESS", str) == 0) {
    return BUILD_SUCCESS;
  }
  if (strcmp("UNSTABLE", str) == 0) {
    return BUILD_UNSTABLE;
  }
  if (strcmp("FAILURE", str) == 0) {
    return BUILD_FAIL;
  }
  if (strcmp("ABORTED", str) == 0) {
    return BUILD_ABORTED;
  }
  return BUILD_UNKNOWN;
}

void statusColor(short ledno, short status) {
  switch (status) {
    case BUILD_SUCCESS:
      setRgbLed(ledno,CRGB::Green);
      break;
    case BUILD_FAIL:
      setRgbLed(ledno,CRGB::Red);
      break;
    case BUILD_ABORTED:
      setRgbLed(ledno,CRGB::LightSalmon);
      break;
    case BUILD_UNSTABLE:
      setRgbLed(ledno,CRGB::Yellow);
      break;
    default:
      setRgbLed(ledno,CRGB::Black);
      break;
  }
  FastLED.show();
}

