#include <ESP8266HTTPClient.h>
#include "ConsoleHandler.h"
#include <TelnetStream.h>
#include "OtaHandler.h"
#include "OtaHandlerImpl.h"

char *theVersion = (char*)"the version";
char *componentName = (char*)"the component name";

WiFiClient http;
char user[] = "q1672933475805";
char socketPassword[] = "bc863bc7-33f2-4198-a4a0-31bc66ebfdf7";

ConsoleHandler *serialConsoleHandler = new ConsoleHandler(componentName, theVersion, &Serial);
ConsoleHandler *telnetConsoleHandler = new ConsoleHandler(componentName, theVersion, &TelnetStream);
OtaHandlerImpl* otaHandler = new OtaHandlerImpl(&http, (char*)"deviceId", user, socketPassword, &Serial);

void setup() {
}

void loop() {
  serialConsoleHandler->handle();
  telnetConsoleHandler->handle();
}
