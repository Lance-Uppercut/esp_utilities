// ConsoleHandler interface and members
#pragma once

#include <Arduino.h>
#include "EspSaveCrash.h"

class ConsoleHandler {
private:
  Stream *stream;
  EspSaveCrash SaveCrash;
  char* theVersion;
  char* componentName;
  int DEBUG_OUTPUT_SIZE;
  char *_debugOutputBuffer;

public:
  ConsoleHandler(char* componentName, char* theVersion, Stream *stream);
  ~ConsoleHandler();
  void handle();
};
