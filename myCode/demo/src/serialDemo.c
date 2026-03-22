#include <stdio.h>
#include <driver/uart.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void DEMO_job(void *arg)
{   
    (void)arg; // Avoid unused parameter warning

    while(1) 
    {
        uart_write_bytes(UART_NUM_0, "Hello João\n", 13);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
}