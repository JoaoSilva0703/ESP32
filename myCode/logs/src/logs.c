#include <stdarg.h>
#include <stdio.h>
#include "logs.h"
#include "uart.h"

void LOG_send(const char *message, ...) {
    char buffer[LOG_BUFFER_SIZE]; // Buffer para armazenar a string formatada
    va_list args;
    int length;

    va_start(args, message);
    length = vsnprintf(buffer, sizeof(buffer), message, args);
    va_end(args);

    if(length > 0)
    {
        UART_write(buffer, length);
    }
};