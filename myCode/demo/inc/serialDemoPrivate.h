#define RESET_TERMINAL "\033[2J\033[H"
#define DEMO_OPTION_TEXT_SIZE (32)
#define DEMO_MESSAGE_SIZE LOG_BUFFER_SIZE

typedef enum
{
    DEMO_OPTION_ROOT,
    DEMO_OPTION_TEST1,
    DEMO_OPTION_MAX,
} DEMO_options_t;

typedef enum
{
    DEMO_STATE_PRINT_MENU,
    DEMO_STATE_ECHO,
    DEMO_STATE_NEW_INPUT,
    DEMO_STATE_MAX,
} DEMO_state_t;

typedef struct
{
    DEMO_options_t parentNode;
    DEMO_options_t *childNodes;
    uint32_t numChildNodes;
    void (*func)(void *arg);
    char terminalOption[DEMO_OPTION_TEXT_SIZE];
} DEMO_node_t;

typedef struct 
{
    DEMO_state_t state;
    DEMO_node_t nodeArray[DEMO_OPTION_MAX];
    DEMO_options_t currentOption; 
} DEMO_tree_t;

