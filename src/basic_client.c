#include <irc_manager.h>
#include <stdio.h>
#include <unistd.h>
#include <settings_manager.h>

int main()
{
	char name[100];
	char pass[100];
	char chan[100];
	char server[1024];
	char port[100];
	char buff[1024];
	IRC* irc;
	int tmp;
	Settings* settings;
	fd_set readfds;
	settings = settings_import ();
	strcpy (name, settings_get_value (settings, "IRC.NICK"));
	if (strlen (name) == 0 || name [0] == SPLIT_CHAR)
	{
		printf ("IRC.NICK : ");
		scanf ("%s", name);
	}
	strcpy (pass, settings_get_value (settings, "IRC.PASS"));
	if (pass [0] == SPLIT_CHAR)
	{
		printf ("IRC.PASS : ");
		scanf ("%s", pass);
	}
	strcpy (chan, settings_get_value (settings, "IRC.CHAN"));
	if (chan [0] == SPLIT_CHAR)
	{
		printf ("IRC.CHAN : ");
		scanf ("%s", chan);
	}
	strcpy (server, settings_get_value (settings, "IRC.SERVER"));
	if (strlen (server) == 0 || server [0] == SPLIT_CHAR)
	{
		strcpy (server, "irc.freenode.net");
	}
	strcpy (port, settings_get_value (settings, "IRC.PORT"));
	if (strlen (port) == 0 || port [0] == SPLIT_CHAR)
	{
		strcpy (port, "6667");
	}
	irc = irc_new (server, port, name, pass, chan);
	assert (irc_connect (irc) == IRCState_Connected);
	settings_destroy (settings);
	while (1)
	{
		FD_ZERO (&readfds);
		FD_SET (0, &readfds);
		FD_SET (irc->connection->connection_fd, &readfds);
		select (irc->connection->connection_fd + 1, &readfds, NULL, NULL, NULL);
		if (FD_ISSET (0, &readfds))
		{
			tmp = read (0, buff, 1000);
			buff [tmp] = '\0';
			if (strncmp (buff, "QUIT", 4) == 0)
				break;
			printf ("%d bytes written\n",irc_send_raw (irc, "%s\r\n", buff));
		}
		if (FD_ISSET (irc->connection->connection_fd, &readfds))
		{
			tmp = read (irc->connection->connection_fd, buff, 1000);
			if (tmp == 0)
				break;
			buff [tmp] = '\0';
			if (strncmp (buff, "PING", 4) == 0)
			{
				printf ("\n>>%s\n", buff);
				buff [1] = 'O';
				printf ("%d bytes written\n",irc_send_raw (irc, "%s\r\n", buff));
			}
			printf ("\n>>%s\n", buff);
		}
	}
	irc_disconnect (irc);
	irc_destroy (irc);
	return 0;
}
