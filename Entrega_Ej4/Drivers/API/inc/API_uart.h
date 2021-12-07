#include <stdbool.h>

typedef bool bool_t;
#ifndef NULL
	#define NULL 0
#endif

bool_t uartInit(void);
void uartSendString(uint8_t *);
int __io_putchar(int);
