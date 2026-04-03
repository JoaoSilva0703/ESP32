bool UART_init(void);
void UART_write(const char *data, size_t size);
bool UART_read(uint8_t *buffer, uint32_t *length);