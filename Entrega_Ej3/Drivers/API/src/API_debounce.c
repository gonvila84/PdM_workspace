#include "main.h" //Incluido por problemas con el editor
#include "API_debounce.h"
#include "API_delay.h"
#include <stdint.h>
#include <stdbool.h>

/* Private define --------------------------------------------------------------------------------------------------------------------------------------*/
#define DELAY_TIME 40

/* Private typedef -------------------------------------------------------------------------------------------------------------------------------------*/

typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
} debounce_t;

/* Private macro ---------------------------------------------------------------------------------------------------------------------------------------*/

/* Private variables -----------------------------------------------------------------------------------------------------------------------------------*/
static delay_t delay;
static debounce_t debounceState;
static bool_t buttonPressedEvent = false;
static bool_t buttonReleasedEvent = true;
static uint32_t buttonPressedCounter = 0;

/* Private function prototypes -------------------------------------------------------------------------------------------------------------------------*/

void buttonPressed (void);
void buttonReleased (void);

bool_t debounceInit(void){
	debounceState = BUTTON_UP;
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	delayInit(&delay, DELAY_TIME);
	//BSP_LED_Init(LED1);
	//BSP_LED_Init(LED2);
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

void buttonPressed(){
	//BSP_LED_Toggle(LED1);
	buttonPressedEvent = true;
	buttonReleasedEvent = false;
	buttonPressedCounter++;
}

void buttonReleased(){
	//BSP_LED_Toggle(LED2);
	buttonReleasedEvent = true;
	buttonPressedEvent = false;
}

uint32_t buttonPressedCount(){
	return buttonPressedCounter;
}

bool_t isButtonPressedEvent(){
	if (buttonPressedEvent)
	{
		return true;
	}
	return false;
}

bool_t isButtonReleasedEvent(){
	if (buttonReleasedEvent)
	{
		return true;
	}
	return false;
}
