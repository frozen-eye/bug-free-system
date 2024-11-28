#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

void main() {
  while (true) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
