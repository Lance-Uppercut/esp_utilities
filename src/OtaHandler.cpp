// OtaHandlerImpl implementation
#include "OtaHandlerImpl.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <string.h>

OtaHandlerImpl::OtaHandlerImpl(WiFiClient *wifiClient, char *deviceId, char *user, char *password, Stream *debugStream)
  : host((char*)"soeren.herokuapp.com"), deviceId(deviceId), user(user), password(password), wifiClient(wifiClient), debugStream(debugStream) {}

int OtaHandlerImpl::getLastError() {
  return ESPhttpUpdate.getLastError();
}

String OtaHandlerImpl::getLastErrorString() {
  return ESPhttpUpdate.getLastErrorString();
}

void OtaHandlerImpl::doOtaIfNeeded(char *fileName, char *theVersion) {
  char *result = strstr(fileName, theVersion);
  boolean needToUpdate = (result == NULL);
  if (needToUpdate) {
    char buf[100];
    sprintf(buf, "http://%s/api/devices/%s/images", host, deviceId);
    String fwv = String(fileName);
    String url = String(buf);

    ESPhttpUpdate.setAuthorization(user, password);
    t_httpUpdate_return ret = ESPhttpUpdate.update(*wifiClient, url, fwv);

    switch (ret) {
      case HTTP_UPDATE_FAILED: {
        int lastError = ESPhttpUpdate.getLastError();
        const char *lastErrorString = ESPhttpUpdate.getLastErrorString().c_str();
        char error[100];
        sprintf(error, "[update] Update failed (%d): %s", lastError, lastErrorString);
        break;
      }
      case HTTP_UPDATE_NO_UPDATES:
        break;
      case HTTP_UPDATE_OK:
        break;
    }
  }
}