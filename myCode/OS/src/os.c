#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdbool.h>
#include "serialDemo.h"
#include "os.h"

static bool OS_createTasks();

task_t myTasks[MAX_TASKS] = {
    //Function pointer, name, stack size, priority
    {DEMO_handlerJob, "DEMO Task", 2048, 5},
    {DEMO_uartJob, "UART Task", 2048, 5}
};

bool OS_init()
{
    OS_createTasks();
    return true; // Return true if initialization was successful, false otherwise
}

static bool OS_createTasks()
{
    uint8_t taskIndex;
    for(taskIndex = 0; taskIndex < MAX_TASKS; taskIndex++)
    {
        xTaskCreate(myTasks[taskIndex].function, myTasks[taskIndex].name, myTasks[taskIndex].stackSize, NULL, myTasks[taskIndex].priority, NULL);
    }
    return true;
}