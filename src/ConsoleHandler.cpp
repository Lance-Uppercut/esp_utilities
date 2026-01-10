// Implementation of ConsoleHandler methods
#include "ConsoleHandler.h"

#include <stdlib.h>

ConsoleHandler::ConsoleHandler(char* componentName, char* theVersion, Stream *stream)
  : stream(stream), theVersion(theVersion), componentName(componentName), DEBUG_OUTPUT_SIZE(2048) {
  _debugOutputBuffer = (char*)calloc(DEBUG_OUTPUT_SIZE, sizeof(char));
}

ConsoleHandler::~ConsoleHandler() {
  if (_debugOutputBuffer) free(_debugOutputBuffer);
}

void ConsoleHandler::handle() {
  if (this->stream->available() > 0) {
    char inChar = stream->read();
    switch (inChar) {
      case 'r':
        stream->println(F("Restarting......."));
        stream->flush();
        ESP.restart();
        break;
      case 'i':
        SaveCrash.print(_debugOutputBuffer, DEBUG_OUTPUT_SIZE);
        stream->println(F("--- BEGIN of crash info from buffer ---"));
        stream->print(_debugOutputBuffer);
        stream->println(F("--- END of crash info from buffer ---"));
        break;
      case 'c':
        SaveCrash.clear();
        stream->println(F("Crash information cleared"));
        break;
      case 'o':
        stream->print(F("I am the"));
        stream->print(componentName);
        stream->print(F(" in version "));
        stream->println(theVersion);
        stream->println(F("r: restart"));
        stream->println(F("i: get crash output"));
        stream->println(F("c: clear crash infomation"));
        break;
      case 0xa:
      case 0xd:
        break;
      default:
        stream->printf("%c typed\n", inChar);
        break;
    }
  }
}
