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
	if (connection->state != ConnectionState_Disconnected)
	{
		connection_disconnect (connection);
	}
	free (connection);
}

ConnectionState connection_connect (Connection* connection)
{
	if (!connection)
		return ConnectionState_Invalid;
	if (connection->state == ConnectionState_Connected)
		return connection->state;
	//TODO: Connect to the host.
	return ConnectionState_Disconnected;
}

void connection_disconnect (Connection* connection)
{
	if (!connection)
		return;
	//TODO: Disconnect from host.
}
