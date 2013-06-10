#ifndef __IRC_MANAGER__
#define __IRC_MANAGER__

#include <stdlib.h>
#include <assert.h>

#include <connection_manager.h>

#define NICK_LEN 64
#define CHAN_LEN 512

typedef enum
{
	IRCState_Invalid,
	IRCState_Connected,
	IRCState_Disconnected,
} IRCState;

typedef struct
{
	Connection* connection;
	char nick [NICK_LEN];
	char channel [CHAN_LEN];
	IRCState state;
} IRC;

IRC* irc_new (char* host, char* port, char* nick, char* channel);

void irc_destroy (IRC* irc);

IRCState irc_connect (IRC* irc);

void irc_disconnect (IRC* irc);


#endif
