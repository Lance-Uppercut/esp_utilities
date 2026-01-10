#pragma once

#include <Arduino.h>
#include "OtaHandler.h"
class WiFiClient;

class OtaHandlerImpl : public OtaHandler {
private:
  char *host;
  char *deviceId;
  char *user;
  char *password;
  WiFiClient *wifiClient;
  Stream *debugStream;
public:
  OtaHandlerImpl(WiFiClient *wifiClient, char *deviceId, char *user, char *password, Stream *debugStream);
  int getLastError() override;
  String getLastErrorString() override;
  void doOtaIfNeeded(char *fileName, char *theVersion) override;
};
