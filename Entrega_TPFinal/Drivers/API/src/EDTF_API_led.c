#include <EDTF_API_led.h>

void initiateLed (BoardLed_t led)
{
	BSP_LED_Init(led);
}

void turnLed(BoardLed_t led, BoardLedState_t state)
{
	if (On == state)
	{
		BSP_LED_On(led);
	}
	else
	{
		BSP_LED_Off(led);
	}
}

void toggleLed(BoardLed_t led)
{
	BSP_LED_Toggle(led);
}

void toggleLedOnInterval(BoardLed_t led, uint intervalInMs)
{
	//TODO: Implement.
}
