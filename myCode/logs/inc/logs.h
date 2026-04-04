void LOG_send(const char *format, ...);

#define LOG(...) LOG_send(__VA_ARGS__)
#define LOG_BUFFER_SIZE 256