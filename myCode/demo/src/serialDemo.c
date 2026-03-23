#include <stdio.h>
#include <driver/uart.h>
#include <hal/uart_hal.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define UART_DRIVER_BUFF_SIZE (256)
uint8_t uart_buffer[UART_DRIVER_BUFF_SIZE];
void DEMO_job(void *arg)
{   
    (void)arg; // Avoid unused parameter warning
    uint32_t bytes_read = 0;
    if(uart_driver_install(UART_NUM_0, UART_DRIVER_BUFF_SIZE, UART_DRIVER_BUFF_SIZE, 0, NULL, 0) == ESP_OK)
    {
        while(1) 
        {
            bytes_read = uart_read_bytes(UART_NUM_0, uart_buffer, UART_DRIVER_BUFF_SIZE, 100 / portTICK_PERIOD_MS);
            if(bytes_read > 0) // Clear the RX buffer
            {
                uart_write_bytes(UART_NUM_0, uart_buffer, bytes_read);
            }
        }
    }    
}