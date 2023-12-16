#ifndef AP_WEBSERVER_H
#define AP_WEBSERVER_H

#include "../app-state.h"
#include <WebServer.h>
#include <ring-led/ring-led.h>

class APWebServer : public AppState {
public:
  APWebServer(RingLed *ringLed);
  WebServer server{80};
  void handleRoot();
  void handleCredentialsSetup();
  void handleNotFound();

private:
  RingLed *ringLed;
  const char *ap_ssid = "ESP32-Access-Point";
  const char *ap_password = "12345678";

  String html = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: sans-serif;
        }

        form {
            margin: 10% auto;
            width: 80%;
            height: 80vh;
            display: flex;
            justify-content: center;
            align-items: center;
            flex-direction: column;
            background-color: rgba(102, 51, 153, 0.5);
            border-radius: 20px;
            border: 1px solid black;
        }

        h1 {
            font-size: 3em;
            margin-bottom: 80px;
        }

        label {
            margin: 10px 0;
            font-size: 2em;
        }

        input {
            width: 80%;
            height: 50px;
            font-size: 1.5em;
            border-radius: 10px;
            border: 1px solid black;
            padding: 0 10px;
        }

        input[type="submit"] {
            width: 50%;
            height: 50px;
            margin-top: 100px;
            background-color: rgba(102, 51, 153, 1);
            color: white;
            font-size: 1.5em;
            border: none;
            border-radius: 10px;
            cursor: pointer;
        }
    </style>
</head>
<body>
    <form action="/setup" method="post">
        <h1>Wi-Fi Setup</h1>

        <label for="ssid">Wi-Fi Name</label>
        <input type="text" id="ssid" name="ssid" placeholder="Wi-Fi Name" />

        <label for="password">Wi-Fi Password</label>
        <input type="text" id="password" name="password" placeholder="Wi-Fi Password" />

        <input type="submit" value="Submit" />
    </form>
</body>
</html>
    )";

  String okHtml = R"(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: sans-serif;
        }

        div {
            margin: 40% auto;
            width: 80%;
            height: 40vh;
            display: flex;
            justify-content: center;
            align-items: center;
            flex-direction: column;
            background-color: rgba(102, 51, 153, 0.5);
            border-radius: 20px;
            border: 1px solid black;
        }

        h1 {
            font-size: 2.5em;
        }

        p {
            font-size: 1em;
        }
    </style>
</head>

<body>
    <div>
        <h1>Credentials Set</h1>
        <p>You can close this page...</p>
    </div>
</body>

</html>
    )";
};

#endif