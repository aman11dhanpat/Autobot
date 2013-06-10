#ifndef __IRC_MANAGER__
#define __IRC_MANAGER__

#include <stdlib.h>
#include <assert.h>

#include <connection_manager.h>

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

int irc_connect (IRC* irc);

int irc_disconnect (IRC* irc);


#endif
