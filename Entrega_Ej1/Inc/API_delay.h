#include <stdint.h>
#include <stdbool.h>

typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

#ifndef NULL
	#define NULL 0
#endif

void delayInit (delay_t *, tick_t);
bool_t delayRead (delay_t *);
void delayWrite (delay_t *, tick_t);
void configureDelayErrorHandler (void (*p)(void));
