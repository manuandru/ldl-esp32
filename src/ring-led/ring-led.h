#ifndef RING_LED_H
#define RING_LED_H

class RingLed {
public:
  RingLed();
  void onCredentialsMissing();
  void onSiteConnected();
  void onCredentialsProvided();
  void onWifiError();
  void onWifiConnected();
};

#endif