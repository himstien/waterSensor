#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;

int WiFiStatus;

enum WIFISTATUS {WIFI_UNAVAILABLE, WIFI_CONNECTED, WIFI_DISCONNECTED};

// WIFI SETTINGS
const char *ssidLab =  "RevengeOfPizzaDay";     // replace with your wifi ssid and password
const char *passLab =  "m0nkeycm0nkeyd0";

// WIFI SETTINGS HOME
const char *ssidHome =  "Sher, Lock Homes";     // replace with your wifi ssid and password
const char *passHome =  "it$,element@ry";
