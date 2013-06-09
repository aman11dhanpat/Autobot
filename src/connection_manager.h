#ifndef __CONNECTION_MANAGER__
#define __CONNECTION_MANAGER__


#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NICK_LEN 32
#define CHAN_LEN 512
#define HOST_LEN 1024
#define PORT_LEN 8


typedef enum
{
	ConnectionState_Disconnected,
	ConnectionState_Connected,
} ConnectionState;

typedef struct
{
	int connection_fd;
	char nick [NICK_LEN];
	char channel [CHAN_LEN];
	char host [HOST_LEN];
	char port [PORT_LEN];
	ConnectionState state;
} Connection;

Connection* connection_new ();

void connection_destroy (Connection* connection);

int connection_connect (Connection* connection);

void connection_disconnect (Connection* connection);

#endif
