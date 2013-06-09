#include <connection_manager.h>

Connection* connection_new (char* nick, char* channel, char* host, char* port)
{
	Connection *new = (Connection*) malloc (sizeof (Connection));
	assert (new != NULL);
	new-> connection_fd = -1;
	if (nick)
		strncpy (new->nick, nick, NICK_LEN - 1);
	new->nick [NICK_LEN - 1] = '\0';
	if (channel)
		strncpy (new->channel, channel, CHAN_LEN - 1);
	new->channel [CHAN_LEN - 1] = '\0';
	if (host)
		strncpy (new->host, host, HOST_LEN - 1);
	new->host [HOST_LEN - 1] = '\0';
	if (port)
		strncpy (new->port, port, PORT_LEN - 1);
	new->port [PORT_LEN - 1] = '\0';
	new->state = ConnectionState_Disconnected;
	return new;
}

void connection_destroy (Connection* connection)
{
	if (connection->state == ConnectionState_Connected)
	{
		connection_disconnect (connection);
	}
	free (connection);
}

int connection_connect (Connection* connection)
{
	if (!connection)
		return 0;
	return 0;
}

void connection_disconnect (Connection* connection)
{
	if (!connection)
		return;
}
