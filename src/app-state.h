#ifndef APP_STATE_H
#define APP_STATE_H

class AppState {
public:
  virtual void setup() = 0;
  virtual void loop() = 0;
};

#endif