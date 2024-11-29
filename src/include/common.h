/**
 * SPDX-FileCopyrightText: 2024 FrozenEye
 * SPDX-License-Identifier: MIT License
 *
 * @file common.h
 */

#pragma once

#include <stdint.h>

#define LOG_LEVEL_VERBOSE 5
#define LOG_LEVEL_DEBUG   4
#define LOG_LEVEL_INFO    3
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_ERROR   1
#define LOG_LEVEL_NONE    0

#ifndef LOGV
#if LOG_LEVEL >= LOG_LEVEL_VERBOSE
#define LOGV(tag, format, ...) printf("[%s] VER: " format "\n", tag, ##__VA_ARGS__)
#else
#define LOGV(tag, format, ...)
#endif  // LOG_LEVEL
#endif  // LOGI

#ifndef LOGD
#if LOG_LEVEL >= LOG_LEVEL_DEBUG
#define LOGD(tag, format, ...) printf("[%s] DBG: " format "\n", tag, ##__VA_ARGS__)
#else
#define LOGD(tag, format, ...)
#endif  // LOG_LEVEL
#endif  // LOGD

#ifndef LOGI
#if LOG_LEVEL >= LOG_LEVEL_INFO
#define LOGI(tag, format, ...) printf("[%s] INF: " format "\n", tag, ##__VA_ARGS__)
#else
#define LOGI(tag, format, ...)
#endif  // LOG_LEVEL
#endif  // LOGI

#ifndef LOGW
#if LOG_LEVEL >= LOG_LEVEL_WARNING
#define LOGW(tag, format, ...) printf("[%s] WRN: " format "\n", tag, ##__VA_ARGS__)
#else
#define LOGW(tag, format, ...)
#endif  // LOG_LEVEL
#endif  // LOGW

#ifndef LOGE
#if LOG_LEVEL >= LOG_LEVEL_ERROR
#define LOGE(tag, format, ...) printf("[%s] ERR: " format "\n", tag, ##__VA_ARGS__)
#else
#define LOGE(tag, format, ...)
#endif  // LOG_LEVEL
#endif  // LOGE

typedef enum pico_error_codes pico_error_t;

/**
 * @brief Probe i2c bus for a device.
 *
 * @param addr The address of the device to probe.
 * @return pico_error_t The error code. PICO_ERROR_NONE if successful.
 */
pico_error_t i2c_probe(uint8_t addr);
