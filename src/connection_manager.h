#ifndef __CONNECTION_MANAGER__
#define __CONNECTION_MANAGER__


#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

#define HOST_LEN 1024
#define PORT_LEN 8

#define BUFF_LEN 8192

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

int connection_printf (Connection* connection, char* format, ...);

int connection_vprintf (Connection* connection, char* format, va_list list);

#endif
