#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <assert.h>

typedef enum
{
	LOG_NONE,
	LOG_CRITICAL,
	LOG_ALERT,
	LOG_NOTIFY,
	LOG_ALL
} LogLevel;

typedef struct
{
	FILE* file;
	LogLevel max_log_level;
} Logger;

const char* log_level_to_string (LogLevel level);

Logger* logger_new (const char* file_name, LogLevel max_log_level);

void logger_log (Logger* logger, LogLevel level, char* message, ...);

void logger_destroy (Logger* logger);

#endif
