#include <stdio.h>
#include "uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define DEMO_MESSAGE_SIZE (256)
uint8_t demoBuffer[DEMO_MESSAGE_SIZE];

void DEMO_job(void *arg)
{   
    (void)arg; // Avoid unused parameter warning
    uint32_t length = 0;
    while(1)
    {
        UART_read(demoBuffer, &length);

        if(length > 0)
        {
            UART_write((const char *)demoBuffer, length);
        }
        vTaskDelay(pdMS_TO_TICKS(1)); // Delay for 1 second
    }
}