#ifndef __CONNECTION_MANAGER__
#define __CONNECTION_MANAGER__


#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define HOST_LEN 1024
#define PORT_LEN 8


typedef enum
{
	ConnectionState_Invalid,
	ConnectionState_Disconnected,
	ConnectionState_Connected,
} ConnectionState;

typedef struct
{
	int connection_fd;
	char host [HOST_LEN];
	char port [PORT_LEN];
	ConnectionState state;
} Connection;

Connection* connection_new (char* host, char* port);

void connection_destroy (Connection* connection);

ConnectionState connection_connect (Connection* connection);

void connection_disconnect (Connection* connection);

#endif
