/*****************************************************************************************
 *                                                                                       *
 * MIT License                                                                           *
 *                                                                                       *
 * Copyright (c) 2016 Maxime Pinard                                                      *
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

#ifndef PFC_LOG_H
#define PFC_LOG_H


#ifdef __cplusplus
extern "C" {
#endif

#ifdef LOGGER_ENABLED
#undef LOGGER_ENABLED
#define LOGGER_ENABLED 1
#else
#define LOGGER_ENABLED 0
#endif

#define LOG_DEBUG(...) lg_log(__FILE__, __LINE__, __func__, DEBUG_LV, ## __VA_ARGS__)
#define LOG_INFO(...) lg_log(__FILE__, __LINE__, __func__, INFO_LV, ## __VA_ARGS__)
#define LOG_WARN(...) lg_log(__FILE__, __LINE__, __func__, WARN_LV, ## __VA_ARGS__)
#define LOG_ERROR(...) lg_log(__FILE__, __LINE__, __func__, ERROR_LV, ## __VA_ARGS__)
#define LOG_FATAL(...) lg_log(__FILE__, __LINE__, __func__, FATAL_LV, ## __VA_ARGS__)

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdarg.h>

typedef enum {
	DEBUG_LV = 0x1,
	INFO_LV = 0x2,
	WARN_LV = 0x4,
	ERROR_LV = 0x8,
	FATAL_LV = 0x10
} cc_LogLevel;

/*-------------------------------------------------------------------------*//**
 * @brief      Set the logger output stream, if NULL, stderr is used.
 *
 * @details    Default value is NULL, stderr is used.
 *
 * @param      outputStream  The logger output stream
 */
void lg_setOutputStream(FILE* outputStream);

/*-------------------------------------------------------------------------*//**
 * @brief      Set if the logger is enabled or not.
 *
 * @param[in]  enabled  True for enabled, false for disabled
 */
void lg_setEnabled(bool enabled);

/*-------------------------------------------------------------------------*//**
 * @brief      Set the processed logging levels.
 *
 * @details    Default value: DEBUG_LV | INFO_LV | WARN_LV | ERROR_LV | FATAL_LV
 *
 * @param[in]  levels  The levels, a binary mask with DEBUG_LV, INFO_LV,
 *                     WARN_LV, ERROR_LV and FATAL_LV
 */
void lg_setLevels(unsigned int levels);

/*-------------------------------------------------------------------------*//**
 * @brief      Add logging levels from the processed logging levels.
 *
 * @param[in]  levels  The levels, a binary mask with DEBUG_LV, INFO_LV,
 *                     WARN_LV, ERROR_LV and FATAL_LV
 */
void lg_addLevels(unsigned int levels);

/*-------------------------------------------------------------------------*//**
 * @brief      Remove logging levels from the processed logging levels.
 *
 * @param[in]  levels  The levels, a binary mask with DEBUG_LV, INFO_LV,
 *                     WARN_LV, ERROR_LV and FATAL_LV
 */
void lg_removeLevels(unsigned int levels);

/*-------------------------------------------------------------------------*//**
 * @brief      Set the log printer function to use.
 *
 * @details    The functions parameters are (output stream, log instant timeinfo
 *             struct, file of the log, line of the log, function of the log,
 *             level of the log, format of the log message, arguments of the log
 *             message). Default value: &lg_simpleLogPrinter
 *
 * @param      logPrinter  The log printer function
 */
void lg_setLogPrinter(void (* logPrinter)
	(FILE*, struct tm*, const char*, const int, const char*, const char*, const char*, va_list));

/*-------------------------------------------------------------------------*//**
 * @brief      Log a message with the configured log printer.
 *
 * @details    Use the LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL
 *             macros functions to automatically fill the file, line, func and
 *             level parameters
 *
 * @param[in]  file       The file of the log (where the log happened not where
 *                        it should be print)
 * @param[in]  line       The line of the log
 * @param[in]  func       The function of the log
 * @param[in]  level      The level of the log
 * @param[in]  format     The format of the log message
 * @param[in]  ...        The arguments of the log message
 */
void lg_log(const char* file, int line, const char* func, cc_LogLevel level, const char* format, ...);

/*-------------------------------------------------------------------------*//**
 * @brief      Simple log printer
 *
 * @details    Format: moment - [LEVEL] function - message
 *
 * @param      outputStream  The log output stream
 * @param      timeinfo      The timeinfo of the moment the log happened
 * @param[in]  file          The file of the log (where the log happened not
 *                           where it should be print)
 * @param[in]  line          The line of the log
 * @param[in]  func          The function of the log
 * @param[in]  level         The level of the log
 * @param[in]  format        The format of the log message
 * @param[in]  args          The arguments of the log message
 */
void lg_simpleLogPrinter(FILE* outputStream, struct tm* timeinfo, const char* file, int line, const char* func,
                         const char* level, const char* format, va_list args);

/*-------------------------------------------------------------------------*//**
 * @brief      Complete log printer
 *
 * @details    Format: moment - [LEVEL] function (path_to_file:line) - message
 *
 * @param      outputStream  The log output stream
 * @param      timeinfo      The timeinfo of the moment the log happened
 * @param[in]  file          The file of the log (where the log happened not
 *                           where it should be print)
 * @param[in]  line          The line of the log
 * @param[in]  func          The function of the log
 * @param[in]  level         The level of the log
 * @param[in]  format        The format of the log message
 * @param[in]  args          The arguments of the log message
 */
void lg_completeLogPrinter(FILE* outputStream, struct tm* timeinfo, const char* file, int line, const char* func,
                           const char* level, const char* format, va_list args);

#ifdef __cplusplus
}
#endif

#endif //PFC_LOG_H
