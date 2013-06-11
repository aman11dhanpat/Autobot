#include <irc_manager.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	char name[100];
	char pass[100];
	char buff[1024];
	IRC* irc;
	struct timeval tv;
	int tmp;
	fd_set readfds;
	scanf ("%s", name);
	scanf ("%s", pass);
	irc = irc_new ("irc.freenode.net", "6667", name, pass, NULL);
	assert (irc_connect (irc) == IRCState_Connected);
	while (1)
	{
		tv.tv_sec = 0;
		tv.tv_usec = 50000;
		FD_ZERO (&readfds);
		FD_SET (0, &readfds);
		FD_SET (irc->connection->connection_fd, &readfds);
		select (irc->connection->connection_fd + 1, &readfds, NULL, NULL, &tv);
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
			printf ("\n>>%s\n", buff);
		}
	}
	irc_disconnect (irc);
	irc_destroy (irc);
	return 0;
}
