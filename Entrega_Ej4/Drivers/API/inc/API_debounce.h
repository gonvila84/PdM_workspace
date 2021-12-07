#include <stdint.h>
#include <stdbool.h>

typedef bool bool_t;

#ifndef NULL
	#define NULL 0
#endif

bool_t debounceInit(void);
void debounceUpdate(void);
bool_t consumeSinglePressEvent(void);
