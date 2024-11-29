/**
 * SPDX-FileCopyrightText: 2024 FrozenEye
 * SPDX-License-Identifier: MIT License
 * @file main.c
 */

#include <pico/stdlib.h>
#include <stdint.h>
#include <stdio.h>

// add the FreeRTOS headers
#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <hardware/i2c.h>
#include <task.h>

#include "common.h"
// #include "drivers/nrf24_driver.h"
#include "drivers/bmp280_driver.h"

#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
#error "I2C is not configured"
#endif

/**
 * @brief I2C task function that runs indefinitely.
 *
 * @param pvParameters Pointer to the parameters passed to the task (not used).
 */
void i2c_task(void *pvParameters) {
  // Get task name
  const char *task_name = pcTaskGetName(NULL);

  // Set the I2C baud rate
  i2c_init(i2c_default, 100000);

  // Set up our I2C pins
  gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);

  // Set the pull-up resistors
  gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
  gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

  if (i2c_probe(0x76) != PICO_ERROR_NONE) {
    LOGE(task_name, "BMP280 sensor not found");
  }

  if (bmp280_init() != PICO_ERROR_NONE) {
    LOGE(task_name, "Failed to initialize BMP280 sensor");
  }

  // Forever loop
  while (true) {
    vTaskDelay(pdMS_TO_TICKS(1000));

    int32_t temperature = 0, pressure = 0;
    if (bmp280_read_data(&temperature, &pressure) == PICO_ERROR_NONE) {
      LOGI(task_name, "t: %.2f C, p: %.2f hPa", temperature / 100.0f, pressure / 100.0f);
    }
  }
}

/**
 * @brief SPI task function that runs indefinitely.
 *
 * @param pvParameters Pointer to the parameters passed to the task (not used).
 */
void spi_task(void *pvParameters) {
  while (true) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

/**
 * @brief Main task function that runs indefinitely.
 *
 * @param pvParameters Pointer to the parameters passed to the task (not used).
 */
void main_task(void *pvParameters) {
  while (true) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

/**
 * @brief Entry point of the program.
 *
 * This function creates the main task and starts the FreeRTOS scheduler.
 */
void main() {
  static const char *TAG = "main";

  stdio_init_all();

  // if (xTaskCreate(main_task, "main_task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
  //   LOGE(TAG, "Failed to create main task");
  // }

  if (xTaskCreate(i2c_task, "i2c_task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    LOGE(TAG, "Failed to create i2c task");
  }

  // if (xTaskCreate(spi_task, "spi_task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
  //   LOGE(TAG, "Failed to create spi task");
  // }

  // Start the FreeRTOS scheduler
  vTaskStartScheduler();

  // Should never reach here
  return;
}
