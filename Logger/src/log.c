/*****************************************************************************************
 *                                                                                       *
 * MIT License                                                                           *
 *                                                                                       *
 * Copyright (c) 2017 Maxime Pinard                                                      *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy          *
 * of this software and associated documentation files (the "Software"), to deal         *
 * in the Software without restriction, including without limitation the rights          *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell             *
 * copies of the Software, and to permit persons to whom the Software is                 *
 * furnished to do so, subject to the following conditions:                              *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all        *
 * copies or substantial portions of the Software.                                       *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR            *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,              *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE           *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER                *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,         *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE         *
 * SOFTWARE.                                                                             *
 *                                                                                       *
 *****************************************************************************************/

#include <log.h>

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

typedef struct {
	FILE* outputStream;
	bool enabled;
	unsigned int levels;
	void (* logPrinter)(FILE*, struct tm*, const char*, int, const char*, const char*, const char*, va_list);
} log_config;

log_config loggerConfig = {
	NULL, // default: stderr
	LOGGER_ENABLED,
	DEBUG_LV | INFO_LV | WARN_LV | ERROR_LV | FATAL_LV,
	&lg_simpleLogPrinter
};

const char* getLevelText(cc_LogLevel level);

const char* getLevelText(cc_LogLevel level) {
	switch(level) {
		case DEBUG_LV:
			return "DEBUG";
		case INFO_LV:
			return "INFO";
		case WARN_LV:
			return "WARN";
		case ERROR_LV:
			return "ERROR";
		case FATAL_LV:
			return "FATAL";
		default:
			return "OTHER";
	}
}

void lg_setOutputStream(FILE* outputStream) {
	loggerConfig.outputStream = outputStream;
}

void lg_setEnabled(bool enabled) {
	loggerConfig.enabled = enabled;
}

void lg_setLevels(unsigned int levels) {
	loggerConfig.levels = levels;
}

void lg_addLevels(unsigned int levels) {
	loggerConfig.levels |= levels;
}

void lg_removeLevels(unsigned int levels) {
	loggerConfig.levels &= ~levels;
}

void lg_setLogPrinter(void (* logPrinter)
	(FILE*, struct tm*, const char*, int, const char*, const char*, const char*, va_list)) {
	loggerConfig.logPrinter = logPrinter;
}

void lg_log(const char* file, int line, const char* func, cc_LogLevel level, const char* format, ...) {
	if(loggerConfig.enabled) {
		if(level & loggerConfig.levels) {
			va_list args;
			va_start(args, format);

			time_t rawtime;
			time(&rawtime);
			struct tm* timeinfo = localtime(&rawtime);

			loggerConfig.logPrinter(loggerConfig.outputStream != NULL ? loggerConfig.outputStream : stderr,
			                        timeinfo, file, line, func, getLevelText(level), format, args);
			va_end(args);
		}
	}
}

void lg_simpleLogPrinter(FILE* outputStream, struct tm* timeinfo, const char* UNUSED(file), int UNUSED(line),
                         const char* func, const char* level, const char* format, va_list args) {
	char buffer[20];
	strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", timeinfo);

	fprintf(outputStream, "%s - [%-5s] %s - ", buffer, level, func);
	vfprintf(outputStream, format, args);
	fprintf(outputStream, "\n");
	fflush(outputStream);
}

void lg_completeLogPrinter(FILE* outputStream, struct tm* timeinfo, const char* file, int line,
                           const char* func, const char* level, const char* format, va_list args) {
	char buffer[20];
	strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", timeinfo);

	fprintf(outputStream, "%s - [%-5s] %s (%s:%d) - ", buffer, level, func, file, line);
	vfprintf(outputStream, format, args);
	fprintf(outputStream, "\n");
	fflush(outputStream);
}
