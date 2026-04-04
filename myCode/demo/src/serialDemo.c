#include <stdio.h>
#include "uart.h"
#include "serialDemo.h"
#include "serialDemoPrivate.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define DEMO_MESSAGE_SIZE (256)
static uint8_t demoBuffer[DEMO_MESSAGE_SIZE];
static DEMO_options_t demoOptions[DEMO_OPTION_MAX] =
{
    DEMO_OPTION_1
};

static DEMO_node_t demoTree[DEMO_OPTION_MAX] =
{
    {DEMO_OPTION_1, demoOptions, 0, NULL}
};

static DEMO_state_t demoState = DEMO_STATE_PRINT_MENU;

void DEMO_uartJob(void *arg)
{   
    (void)arg; // Avoid unused parameter warning
    uint32_t length = 0;
    while(1)
    {
        UART_read(demoBuffer, &length);

        if((length > 0) && (demoState == DEMO_STATE_ECHO))
        {
            for(uint32_t i = 0; i < length; i++)
            {
                if(demoBuffer[i] == '\r' || demoBuffer[i] == '\n')
                {
                    length = i; // Update length to exclude newline characters
                    demoState = DEMO_STATE_NEW_INPUT; // Update state to indicate new input received
                    break;
                }
            }
            UART_write((const char *)demoBuffer, length);
        }

        vTaskDelay(pdMS_TO_TICKS(1)); 
    }
}

void DEMO_printMenu()
{
    UART_write(RESET_TERMINAL, sizeof(RESET_TERMINAL) - 1); // Clear terminal and move cursor to home position
    const char *menu = "Menu:\n1. Option 1\n2. Option 2\n3. Option 3\n";
    UART_write(menu, sizeof(menu) - 1);
}

void DEMO_handlerJob(void *arg)
{
    while(1)
    {
        switch (demoState)
        {  
            case DEMO_STATE_PRINT_MENU:
                // Handle print menu state
                DEMO_printMenu();
                demoState = DEMO_STATE_ECHO;
                break;
            case DEMO_STATE_ECHO:
                //Do nothing for now
                // Handle echo state
                break;
            case DEMO_STATE_NEW_INPUT:
                demoState = DEMO_STATE_PRINT_MENU;    
                // Handle new input state
                break;
            default:
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}