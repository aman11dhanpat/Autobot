#include <irc_manager.h>

IRC* irc_new (char* host, char* port, char* nick, char* channel)
{
	IRC* new;
	new = (IRC*) malloc (sizeof (IRC));
	assert (new != NULL);
	new->connection = connection_new (host, port);
	if (nick)
		strncpy (new->nick, nick, NICK_LEN - 1);
	new->nick [NICK_LEN - 1] = '\0';
	if (channel)
		strncpy (new->channel, channel, CHAN_LEN - 1);
	new->channel [CHAN_LEN - 1] = '\0';
	new->state = IRCState_Disconnected;
	return new;
}

void irc_destroy (IRC* irc)
{
	assert (irc);
	if (irc->state != IRCState_Disconnected)
		irc_disconnect (irc);
	if (irc->connection)
		connection_destroy (irc->connection);
	free (irc);
}

int irc_connect ()
{
	assert (connection_connect (irc->connection) == ConnectionState_Connected);
	//TODO: Connect to IRC server.
}

void irc_disconnect ()
{
	//TODO: Disconnect from IRC server.
	connection_disconnect (irc->connection);
}
