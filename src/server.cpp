/*
 *  Projecy udp-test
 *  This sketch sends random data over UDP on a ESP32 device
 *
 *  EAMartinez - Universidad Austral
 *  20200721
 *
 */

/*
 *  System includes
 */

#include <Arduino.h>
#include <WiFiUdp.h>

/*
 *  General includes
 */

#include "utils.h"

/*
 *  Project includes
 */

#include "wifi_mgr.h"
#include "clserv.h"

/*
 *  Constants taken from platformio.ini
 *  or defined elsewhere
 */

/*
    LOCAL_PORT: port where this server will get requirements
    REMOTE_PORT: forced port to client (used only for testing)
    DEBUG: 0 ? production : testing
*/

/*
 *  static variables
 */

static WiFiUDP udp;
static IPAddress client_ip;
static int client_port;
static char ip[20];

/*
 *  static functions
 */

/*
 *  receive_udp:
 *      Receives packet from any client
 *      Return pointer to string received null terminated
 *      If packet size is empty, return NULL pointer
 */

static char *
receive_udp(void)
{
    int packet_size;
    int len;
    static char buffer[255];

    packet_size = udp.parsePacket();
    if( packet_size )
    {
        Serial.println(packet_size);
        client_ip = udp.remoteIP();
        client_port = udp.remotePort();
        client_ip.toString().toCharArray(ip,16);
        Serial.printf("client ip = %s\n\r",ip);
        if( ( len = udp.read(buffer, sizeof(buffer) ) ) > 0 )
            buffer[len] = '\0';
        return buffer;
    } else
        return NULL;
}

/*
 *  transmit_udp:
 *      Transmits answer to client
 *      Receives pointer to answer to client
 */

static void
transmit_udp(char *pans)
{
    debprint(Serial.printf("Client ip = %s, client_port = %d, fixed_port = %d\n\r", ip, client_port, REMOTE_PORT);)
    udp.beginPacket(client_ip, DEBUG ? REMOTE_PORT: client_port );
    udp.printf(pans);
    udp.endPacket();
}

/*
 *  Public functions
 */

void
setup()
{
    Serial.begin(SERIAL_BAUD);
    wifi_connect();
    udp.begin(LOCAL_PORT);
}

/*
 *  loop: action is here !
 *  Manages chat between client and this server
 */

void
loop()
{
    char *pb;

    if( connected && ( pb = receive_udp() ) != NULL  && key_valid(pb) )
    {
        pb = toanswer();
        Serial.printf(pb);
        transmit_udp(pb);
    }
    delay(10);
}


