#include <EDTF_API_debounce.h>
#include <EDTF_API_delay.h>
#include "main.h" //Incluido por problemas con el editor
#include <stdint.h>
#include <stdbool.h>

#define DEFAULT_DELAY_IN_MS										40

typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
} debounce_t;

static delay_t delay;
static debounce_t debounceState;
static bool_t buttonPressedEvent = false;
static bool_t buttonReleasedEvent = true;
static uint32_t buttonPressedCounter = 0;
static uint32_t buttonPressedRaiseEventCount = 0;


void buttonPressed (void);
void buttonReleased (void);

bool_t debounceInit(void){
	debounceState = BUTTON_UP;
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	delayInit(&delay, DEFAULT_DELAY_IN_MS);
	return true;
}

void debounceUpdate(){
	switch(debounceState)
	{
		case BUTTON_UP:
			if (BSP_PB_GetState(BUTTON_USER))
			{
				delayRead(&delay);
				debounceState = BUTTON_FALLING;
			}
			break;
		case BUTTON_FALLING:
			if (delayRead(&delay))
			{
				if (BSP_PB_GetState(BUTTON_USER))
				{
					buttonPressed();
					debounceState = BUTTON_DOWN;
				}
				else
				{
					debounceState = BUTTON_UP;
				}
			}
			break;
		case BUTTON_DOWN:
			if (!BSP_PB_GetState(BUTTON_USER))
			{
				delayRead(&delay);
				debounceState = BUTTON_RAISING;
			}
			break;
		case BUTTON_RAISING:
			if (delayRead(&delay))
			{
				if (!BSP_PB_GetState(BUTTON_USER))
				{
					buttonReleased();
					debounceState = BUTTON_UP;
				}
				else
				{
					debounceState = BUTTON_DOWN;
				}

			}
			break;
	}
}

void buttonPressed()
{
	ButtonPressedRaiseEvent();
}

void buttonReleased()
{

}

void ButtonPressedRaiseEvent()
{
	buttonPressedRaiseEventCount++;
}

bool_t consumeSinglePressEvent()
{
	bool_t wasEventConsumed = false;
	if (buttonPressedRaiseEventCount > 0)
	{
		buttonPressedRaiseEventCount--;
		wasEventConsumed = true;
	}
	return wasEventConsumed;
}
