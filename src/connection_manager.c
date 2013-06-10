#include <connection_manager.h>

Connection* connection_new (char* host, char* port)
{
	Connection *new = (Connection*) malloc (sizeof (Connection));
	assert (new != NULL);
	new-> connection_fd = -1;
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
	assert (connection);
	if (connection->state != ConnectionState_Disconnected)
	{
		connection_disconnect (connection);
	}
	free (connection);
}

ConnectionState connection_connect (Connection* connection)
{
	struct addrinfo hints, *resolved;
	if (!connection)
		return ConnectionState_Invalid;
	if (connection->state == ConnectionState_Connected)
		return connection->state;
	memset (&hints, 0, sizeof (struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	//TODO: Handle errors.
	assert (getaddrinfo (connection->host, connection->port, &hints, &resolved) == 0);
	connection->connection_fd = socket (resolved->ai_family, resolved->ai_socktype, resolved->ai_protocol);
	assert (connection->connection_fd != -1);
	assert (connect (connection->connection_fd, resolved->ai_addr, resolved->ai_addrlen) == 0);
	free (resolved);
	connection->state = ConnectionState_Connected;
	return ConnectionState_Connected;
}

void connection_disconnect (Connection* connection)
{
	if (!connection)
		return;
	//TODO: Handle errors.
	if (connection->state == ConnectionState_Connected)
		close (connection->connection_fd);
	connection->state = ConnectionState_Disconnected;
}

int connection_printf (Connection* connection, char* format, ...)
{
	va_list list;
	int ret;
	va_start (list, format);
	ret = connection_vprintf (connection, format, list);
	va_end (list);
	return ret;
}

int connection_vprintf (Connection* connection, char* format, va_list list)
{
	char buffer [BUFF_LEN];
	vsnprintf (buffer, BUFF_LEN, format, list);
	if (connection->state != ConnectionState_Connected)
		return 0;
	return write (connection->connection_fd, buffer, strlen (buffer));
}
