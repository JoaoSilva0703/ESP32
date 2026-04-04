#include "serialDemo.h"

typedef enum
{
    DEMO_TASK,
    UART_TASK,
    MAX_TASKS
}tasksName_t;

typedef struct
{
    void (*function)(void *arg);
    char name[40];
    uint32_t stackSize;
    uint32_t priority;
} task_t;

bool OS_init();
