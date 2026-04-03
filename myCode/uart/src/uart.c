#include <driver/uart.h>
#include <hal/uart_hal.h>

#define UART_DRIVER_BUFF_SIZE (256)
#define UART_QUEUE_EVENT_SIZE (20)
uint8_t uartBuffer[UART_DRIVER_BUFF_SIZE];
QueueHandle_t uartQueue;

bool UART_init(void)
{
    // Initialize UART driver and set up the UART event queue
    if (uart_driver_install(UART_NUM_0, UART_DRIVER_BUFF_SIZE, UART_DRIVER_BUFF_SIZE, 20, &uartQueue, 0) != ESP_OK)
    {
        return false; // Return false if initialization failed
    }
    return true; // Return true if initialization was successful
}

bool UART_read(uint8_t *buffer, uint32_t *length)
{
    uart_event_t event;
    if(buffer == NULL || length == 0)
    {
        return false; // Return false if buffer is null or length is zero
    }

    if (xQueueReceive(uartQueue, (void *)&event, (TickType_t)(portMAX_DELAY)) == pdPASS)
    {
        switch (event.type)
        {
        case UART_DATA:
            *length = uart_read_bytes(UART_NUM_0, buffer, event.size, 0);
            break;

        case UART_FIFO_OVF:
            uart_flush_input(UART_NUM_0);
            xQueueReset(uartQueue);
            break;

        default:
            break;
        }
    }

    //Check if anything was read
    if(length <= 0)
    {
        return false; // Return false if no data was read
    }

    return true; // Return true if data was read successfully
}

void UART_write(const char *data, size_t size)
{
    if(data == NULL || size == 0)
    {
        return; // Return if data is null or size is zero
    }

    uart_write_bytes(UART_NUM_0, data, size);
}