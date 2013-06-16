#include <settings_manager.h>

static int setting_split (char* input, char* attribute, char* value)
{
	char* split_point;
	int len;
	//TODO: Handle errors.
	if (!input || !attribute || !value)
		return 0;
	split_point = strchr (input, ':');
	if (!split_point)
		return 0;
	len = split_point - input;
	strncpy (attribute, input, len);
	attribute [len] = '\0';
	len = strlen (split_point);
	strncpy (value, split_point + 1, len);
	value [len] = '\0';
	return 1;
}

static void settings_insert_setting (Settings* settings, char* attribute, char* value)
{
	assert (settings);
	settings->settings = (Setting*) realloc (settings->settings, sizeof (Setting) * (settings->settings_count + 1));
	//TODO: Handle errors.
	assert (settings->settings);
	strncpy (settings->settings [settings->settings_count].attribute, attribute, ATTR_LEN);
	strncpy (settings->settings [settings->settings_count].value, value, VAL_LEN);
	settings->settings_count++;
}

Settings* settings_import ()
{
	int file;
	int len;
	char buffer [1280];
	char attribute [ATTR_LEN];
	char value [VAL_LEN];
	Settings* new;
	new = (Settings*) malloc (sizeof (Settings));
	//TODO: Handle errors.
	assert (new);
	new->settings = NULL;
	new->settings_count = 0;
	file = open (SETTINGS_FILE_NAME, O_RDONLY);
	assert (file != -1);
	while (1)
	{
		if ((len = read (file, buffer, 1280)) == 0)
			break;
		buffer [len] = '\0';
		if (setting_split (buffer, attribute, value))
		{
			settings_insert_setting (new, attribute, value);
		}
	}
	close (file);
	return (new);
}

char* settings_get_value (Settings* settings, const char* attribute)
{
	int l;
	int len = strlen (attribute);
	if (!len)
		return NULL;
	for (l = 0; l < settings->settings_count; l++)
	{
		if (strncmp (settings->settings [l].attribute, attribute, len) == 0)
			return settings->settings [l].value;
	}
	return NULL;
}

void settings_destroy (Settings* settings)
{
	assert (settings);
	if (settings->settings_count > 0)
		free (settings->settings);
	free (settings);
}
