/*
 *  wifi_mgr.cpp
 *      Manages connection and disconnection of WiFi
 */

/*
 *  System includes
 */

#include <Arduino.h>
#include <WiFi.h>

/*
 *  Project includes
 */

#include "wifi_mgr.h"

/*
 *  Constants taken from platformio.ini
 *  or defined elsewhere
 */

/*
    MY_SSID: ssid of WiFi used
    MY_PWD: password of WiFi used
*/

/*
 *  Global variables
 */

int connected;

/*
 *  Static functions
 */

/*
 *  wifi event handler:
 *      Callback function for WiFi
 *      Receives event
 */

static void
WiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {
        case SYSTEM_EVENT_STA_GOT_IP:   // When connected
            Serial.print("WiFi connected! IP address: ");
            Serial.println(WiFi.localIP());
            connected = true;
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Serial.println("WiFi lost connection");
            connected = false;
            break;
        default:
            break;
    }
}

/*
 *  connectToWiFi:
 *      Register WiFi callback, 
 *      requires WiFi connection and
 *      ends functions
 */


static void
connectToWiFi(const char *ssid, const char *pwd)
{
    Serial.println("Connecting to WiFi network: " + String(ssid));
    WiFi.disconnect(true);      // delete old WiFiconfig
    WiFi.onEvent(WiFiEvent);    // register event handler
    WiFi.begin(ssid, pwd);      // Initiate connection
    Serial.println("Waiting for WIFI connection...");
}

/*
 *  Public functions
 */

/*
 *  wifi_connect:
 *      Requires connection to WiFi
 */

void
wifi_connect( void )
{
    connectToWiFi(MY_SSID,MY_PWD);
}


