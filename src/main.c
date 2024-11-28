// This project uses the CMake build system.
#include <pico/stdlib.h>

// add the FreeRTOS headers
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

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
  xTaskCreate(main_task, "main_task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
  vTaskStartScheduler();
}
