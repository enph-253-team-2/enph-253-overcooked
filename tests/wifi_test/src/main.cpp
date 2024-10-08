#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

const char* ssid = "Raymond";
const char* password = "enphteamtwo";
long lastOTATime = millis();

WiFiServer server(23);
WiFiClient remoteClient;

void wifiPrintln(String msg);
bool wifiInput();

void setup() {
  Serial.begin(9600);
<<<<<<< Updated upstream
  Serial.println("Hello");
=======
>>>>>>> Stashed changes

  // Wifi setup
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    // ESP.restart();
  }

  server.begin();
  Serial.println("Server started");
  Serial.println("IP Address: " + WiFi.localIP().toString());

  // OTA setup
  // ArduinoOTA
  // .onStart([]() {
  //   String type;
  //   if (ArduinoOTA.getCommand() == U_FLASH)
  //     type = "sketch";
  //   else
  //     type = "filesystem";

  //   Serial.println("Start updating " + type);
  // })
  // .onEnd([]() {
  //   Serial.println("\nEnd");
  // })
  // .onProgress([](unsigned int progress, unsigned int total) {
  //   Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  // })
  // .onError([](ota_error_t error) {
  //   Serial.printf("Error[%u]: ", error);
  //   if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
  //   else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
  //   else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
  //   else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
  //   else if (error == OTA_END_ERROR) Serial.println("End Failed");
  // });

  // ArduinoOTA.begin();
}

void loop() {
  // while (!wifiInput()) {
  //   Serial.println("Waiting");
  //   delay(100);
  // }
  // Serial.println("Resetting");
  // delay(100);

  // OTA check
  // if (millis() - lastOTATime > 1000) {
  //   ArduinoOTA.handle();
  //   lastOTATime = millis();
  // }
}

void wifiPrintln(String msg) {
  if (server.hasClient()) {
    if (remoteClient.connected()) {
      Serial.println("Connection rejected: already connected");
      server.available().stop();
    } else {
      Serial.println("Connection accepted");
      remoteClient = server.available();
    }
  }
  if (remoteClient.connected()) {
    remoteClient.println(msg);
  }
}

bool wifiInput() {
  if (server.hasClient()) {
    if (remoteClient.connected()) {
      Serial.println("Connection rejected: already connected");
      server.available().stop();
    } else {
      Serial.println("Connection accepted");
      remoteClient = server.available();
    }
  }
  if (remoteClient.connected() && remoteClient.available()) {
    String message = remoteClient.readStringUntil('\n');
    if (message.length() > 0) {
      Serial.println("Received: " + message);
      wifiPrintln("Echo:" + message);
      return true;
    }
  }
  return false;
}
