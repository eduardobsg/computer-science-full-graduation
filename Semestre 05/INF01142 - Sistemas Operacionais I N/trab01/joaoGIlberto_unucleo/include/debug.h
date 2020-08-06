int __debug_step_counter = 1;
int __debug_on = 0;
#define DEBUG() printf("\nDEBUG%d\n", __debug_step_counter++)
#define SET_DEBUG_MODE_ON() (__debug_on = 1)
#define SET_DEBUG_MODE_OFF() (__debug_on = 0)
#define debug(fmt, ...) { if (__debug_on) printf(fmt, ##__VA_ARGS__); }
