#include <logger.h>

const char* log_level_to_string (LogLevel level)
{
	switch (level)
	{
		case LOG_NOTIFY:
			return "NOTIFY   : ";
		case LOG_ALERT:
			return "ALERT    : ";
		case LOG_CRITICAL:
			return "CRITICAL : ";
		default:
			return "";
	}
	return "";
}

Logger* logger_new (const char* file_name, LogLevel max_log_level)
{
	Logger* new;
	new = (Logger*) malloc (sizeof (Logger));
	//TODO: Handle errors.
	assert (new != NULL);
	new->file = stderr;
	if (file_name)
		//TODO: Handle errors.
		assert ((new->file = fopen (file_name, "a")) != NULL);
	new->max_log_level = max_log_level;
	return new;
}

void logger_log (Logger* logger, LogLevel level, char* message, ...)
{
	va_list list;
	//TODO: Handle errors.
	if (level <= logger->max_log_level && message && logger)
	{
		fprintf (logger->file, "%s", log_level_to_string (level));
		va_start (list, message);
		vfprintf (logger->file, message, list);
		va_end (list);
		fprintf (logger->file, "\n");
	}
}

void logger_destroy (Logger* logger)
{
	//TODO: Handle errors.
	assert (logger);
	assert (fclose (logger->file) == 0);
	free (logger);
}
