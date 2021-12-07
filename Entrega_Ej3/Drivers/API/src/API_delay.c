#include "API_delay.h"

#define MIN_DURATION_IN_MS		0
#define MAX_DURATION_IN_MS		10000

void (*delayErrorHandler)(void)= NULL;

bool_t isDurationValid(tick_t duration);


void delayInit ( delay_t * delay, tick_t duration)
{
	if (delay == NULL || !isDurationValid(duration))
	{
		(*delayErrorHandler)();
	}

	delay->duration = duration;
}

bool_t delayRead ( delay_t * delay)
{
	if (delay == NULL)
	{
		(*delayErrorHandler)();
	}

	bool_t timeOut = false;
	if (!delay->running)
	{
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	else
	{
		if (((tick_t)HAL_GetTick() - delay->startTime) >= delay->duration)
		{
			timeOut = true;
			delay->running = false;
		}
	}
	return timeOut;
}

void delayWrite ( delay_t * delay, tick_t duration)
{
	if (delay == NULL || !isDurationValid(duration))
	{
		(*delayErrorHandler)();
	}
	delay->duration = duration;
}

void configureDelayErrorHandler (void (*errorHandler)(void))
{
	delayErrorHandler = errorHandler;
}


bool_t isDurationValid(tick_t duration)
{
	bool_t validDuration = false;
	if (duration >= MIN_DURATION_IN_MS && duration <= MAX_DURATION_IN_MS)
	{
		validDuration = true;
	}
	return validDuration;
}
