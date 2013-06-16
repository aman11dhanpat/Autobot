#ifndef __SETTINGS_MANAGER__
#define __SETTINGS_MANAGER__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>

#define ATTR_LEN 128
#define VAL_LEN 1024

#define SETTINGS_FILE_NAME "autobot.conf"

typedef struct
{
	char attribute [ATTR_LEN];
	char value [VAL_LEN];
} Setting;

typedef struct
{
	int settings_count;
	Setting* settings;
} Settings;

Settings* settings_import ();

char* settings_get_value (Settings* settings, const char* attribute);

void settings_destroy (Settings* settings);

#endif
