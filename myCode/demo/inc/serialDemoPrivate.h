#define RESET_TERMINAL "\033[2J\033[H"
typedef enum
{
    DEMO_OPTION_1,
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
    uint32_t numberOfChilds;
    void (*func)(void *arg);
} DEMO_node_t;

