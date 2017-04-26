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


#ifdef LOGGER_ENABLED
#undef LOGGER_ENABLED
#define LOGGER_ENABLED 1
#else
#define LOGGER_ENABLED 0
#endif

#include <stdio.h>

#define LOG_ERR(format, ...) if(LOGGER_ENABLED) fprintf(stderr, "[ERROR]%s:%d in %s: " format "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__)
#define LOG_WARN(format, ...) if(LOGGER_ENABLED) fprintf(stderr, "[WARNING]%s:%d in %s: " format "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__)
#define LOG_INFO(format, ...) if(LOGGER_ENABLED) fprintf(stderr, "[INFO]%s:%d in %s: " format "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__)
#define LOG(format, ...) if(LOGGER_ENABLED) fprintf(stderr, "[LOG]%s:%d in %s: " format "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__)
//Previous macro can be used without variadic arguments (ex:LOG("msg");) but ISO C99 requires all arguments to be used so prefer using the following macros
#define SLOG_ERR(message) if(LOGGER_ENABLED) fprintf(stderr, "[ERROR]%s:%d in %s: " message "\n", __FILE__, __LINE__, __func__)
#define SLOG_WARN(message) if(LOGGER_ENABLED) fprintf(stderr, "[WARNING]%s:%d in %s: " message "\n", __FILE__, __LINE__, __func__)
#define SLOG_INFO(message) if(LOGGER_ENABLED) fprintf(stderr, "[INFO]%s:%d in %s: " message "\n", __FILE__, __LINE__, __func__)
#define SLOG(message) if(LOGGER_ENABLED) fprintf(stderr, "[LOG]%s:%d in %s: " message "\n", __FILE__, __LINE__, __func__)

#endif //PFC_LOG_H
