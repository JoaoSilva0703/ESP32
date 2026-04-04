#include <stdio.h>
#include "uart.h"
#include "logs.h"
#include "serialDemo.h"
#include "serialDemoPrivate.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void DEMO_dummyFunction(void *arg);
static uint8_t demoBuffer[DEMO_MESSAGE_SIZE];
static DEMO_options_t mainOptions[DEMO_OPTION_MAX] =
{
    DEMO_OPTION_TEST1
};

static DEMO_tree_t demoTree = 
{
    .state = DEMO_STATE_PRINT_MENU,
    .currentOption = DEMO_OPTION_ROOT,
    .nodeArray = 
    {
        // OPTION ENUM      |   CHILD NODES |   NUMBER OF CHILD NODES | FUNCTION POINTER |  TERMINAL OPTION STRING
        {DEMO_OPTION_ROOT,      mainOptions,    1,                      NULL,               "Main Menu"},
        {   DEMO_OPTION_ROOT,   NULL,           0,                      DEMO_dummyFunction, "Test Option 1"},
    }
};

void DEMO_dummyFunction(void *arg)
{
    (void)arg; // Avoid unused parameter warning
    // This is a dummy function for demonstration purposes
    printf("Dummy function called with argument: %p\n", arg);
}

void DEMO_uartJob(void *arg)
{   
    (void)arg; // Avoid unused parameter warning
    uint32_t length = 0;
    DEMO_state_t *demoState = &demoTree.state;
    while(1)
    {
        if((UART_read(demoBuffer, &length) == true) && ((*demoState) == DEMO_STATE_ECHO))
        {
            for(uint32_t i = 0; i < length; i++)
            {
                if(demoBuffer[i] == '\r' || demoBuffer[i] == '\n')
                {
                    demoBuffer[i] = '\0'; // Replace newline characters with null terminator
                    *demoState = DEMO_STATE_NEW_INPUT; // Update state to indicate new input received
                    break;
                }
            }
            LOG((char *)demoBuffer);
        }

        vTaskDelay(pdMS_TO_TICKS(1)); 
    }
}

void DEMO_printMenu()
{
    //Check were we are now
    DEMO_node_t     currentNode = demoTree.nodeArray[demoTree.currentOption];
    DEMO_options_t  currentOption = demoTree.currentOption;
    uint32_t        numberOfChildren = currentNode.numChildNodes;

    LOG(RESET_TERMINAL); // Clear terminal and move cursor to home position
    for(int i = 0; i <= numberOfChildren; i++)
    {
        LOG("[%d] - %s\r\n", i, demoTree.nodeArray[currentOption + i].terminalOption);        
    }
}

void DEMO_handlerJob(void *arg)
{
     DEMO_state_t *demoState = &demoTree.state;
    while(1)
    {
        switch (*demoState)
        {  
            case DEMO_STATE_PRINT_MENU:
                // Handle print menu state
                DEMO_printMenu();
                *demoState = DEMO_STATE_ECHO;
                break;
            case DEMO_STATE_ECHO:
                //Do nothing for now
                // Handle echo state
                break;
            case DEMO_STATE_NEW_INPUT:
                *demoState = DEMO_STATE_PRINT_MENU;    
                // Handle new input state
                break;
            default:
                break;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}