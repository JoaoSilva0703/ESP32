#include <stdio.h>
#include <serialDemo.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void app_main(void)
{    
    xTaskCreate(DEMO_job, "demo_task", 4096, NULL, 5, NULL);
    
}
