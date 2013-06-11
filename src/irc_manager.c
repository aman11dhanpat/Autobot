#include <irc_manager.h>

IRC* irc_new (char* host, char* port, char* nick, char* password, char* channel)
{
	IRC* new;
	new = (IRC*) malloc (sizeof (IRC));
	assert (new != NULL);
	new->connection = connection_new (host, port);
	if (nick)
		strncpy (new->nick, nick, NICK_LEN - 1);
	new->nick [NICK_LEN - 1] = '\0';
	if (password)
	{
		strncpy (new->password, password, PASS_LEN - 1);
		new->password [PASS_LEN - 1] = '\0';
	}
	else
	{
		new->password [0] = '\0';
	}
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

IRCState irc_connect (IRC* irc)
{
	//TODO: Handle errors.
	assert (connection_connect (irc->connection) == ConnectionState_Connected);
	if (irc->state == IRCState_Connected)
		return irc->state;
	if (strlen (irc->password) > 0)
		assert (connection_printf (irc->connection, "PASS %s\r\n", irc->password) > 0);
	assert (connection_printf (irc->connection, "NICK %s\r\n", irc->nick) > 0);
	assert (connection_printf (irc->connection, "USER %s 0 0 :%s Bot\r\n", irc->nick, irc->nick) > 0);
	irc->state = IRCState_Connected;
	return IRCState_Connected;
}

void irc_disconnect (IRC* irc)
{
	//TODO: Handle errors.
	assert (connection_printf (irc->connection, "QUIT :Going out of service.\r\n") > 0);
	connection_disconnect (irc->connection);
	irc->state = IRCState_Disconnected;
}

int irc_send_raw (IRC* irc, char* format, ...)
{
	va_list list;
	int ret;
	va_start (list, format);
	ret =  connection_vprintf (irc->connection, format, list);
	va_end (list);
	return ret;
}
