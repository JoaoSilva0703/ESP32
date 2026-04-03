#include <stdio.h>
#include "os.h"
#include "uart.h"

void app_main(void)
{    
    UART_init();
    OS_init();
}
