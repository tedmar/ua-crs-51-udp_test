/*
 *  clserv.h
 *      Conversation between client and server
 *      client sends a key and if key is correct, server responds
 */

/*
 *  key_valid:
 *      Receives string from client to validate and
 *      return as true coincidence with master_key
 */

int key_valid( char *key_rec );

/*
 *  toanswer:
 *      Return answer string to send to client
 */

char *toanswer(void);


