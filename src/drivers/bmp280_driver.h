/**
 * Copyright (c) 2024 FrozenEye
 *
 * SPDX-License-Identifier: MIT License
 * @file bmp280_driver.h
 **/

#pragma once

#include <stdint.h>

/**
 * @brief BMP280 initialization function.
 *
 * @return int PICO_ERROR_NONE if successful, PICO_ERROR_GENERIC otherwise.
 */
int bmp280_init(void);

/**
 * @brief Reset the BMP280 sensor.
 *
 * @return int PICO_ERROR_NONE if successful, PICO_ERROR_GENERIC otherwise.
 */
int bmp280_reset(void);

/**
 * @brief Read the temperature and pressure data from the BMP280 sensor.
 *
 * @param temperature Pointer to the temperature data.
 * @param pressure Pointer to the pressure data.
 *
 * @return int PICO_ERROR_NONE if successful, PICO_ERROR_GENERIC otherwise.
 */
int bmp280_read_data(int32_t* temperature, int32_t* pressure);
