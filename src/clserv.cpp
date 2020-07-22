/*
 *  clserv.cpp
 *      Conversation between client and server
 *      client sends a key and if key is correct, server responds
 */

/*
 *  System includes
 */

#include <Arduino.h>

/*
 *  General includes
 */

#include "utils.h"

/*
 *  Project includes
 */

#include "clserv.h"

/*
 *  Constants
 */

static const char *master_key = "geheim";

/*
 *  Static variables
 */

static char ans_buff[255];

/*
 *  Public functions
 */

/*
 *  key_valid:
 *      Receives string from client to validate and
 *      return as true coincidence with master_key
 */

int
key_valid( char *key_rec )
{
    debprint(Serial.println(key_rec);)
    return strcmp(key_rec,master_key) == 0;
}

/*
 *  toanswer:
 *      Return answer string to send to client
 */

char *
toanswer( void )
{
    sprintf(ans_buff, "Seconds since boot: %lu\n\r", millis() / 1000);
    return ans_buff;
}



