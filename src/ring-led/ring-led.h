#ifndef RING_LED_H
#define RING_LED_H

class RingLed {
public:
  RingLed();
  void onStart();
  void onCredentialsMissing();
  void onSiteConnected();
  void onCredentialsProvided();
  void onWifiError();
  void onWifiConnected();
  void onWaitingForInteraction();
};

#endif
