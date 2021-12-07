#include <stdio.h>
#include <stdint.h>

typedef enum {
	Green_Led,
	Blue_Led,
	Red_Led
}BoardLed_t;

typedef enum {
	On,
	Off
}BoardLedState_t;

//---Public Functions Prototypes------------------------------------------------------------------------------------------------------------

//Esta funcion inicializa el led.
void initiateLed(BoardLed_t led);

//Esta funcion enciende o apaga el led.
void turnLed(BoardLed_t led,BoardLedState_t state);

//Esta funcion hace un toggle del led.
void toggleLed(BoardLed_t led);

//Esta funcion hace un toggle del led en un determinado intervalo.
void toggleLedOnInterval(BoardLed_t led, uint intervalInMs);

//Esta funcion devuelve estadisticas sobre el uso del led. Cuantas veces se lo prendio.
uint getLedOnStatistics (BoardLed_t led);

//Esta funcion devuelve estadisticas sobre el uso del led. Cuantas veces se lo apago.
uint getLedOffStatistics (BoardLed_t led);

//Esta funcion devuelve estadisticas sobre el uso del led. Cuantas veces se hizo toggle.
uint getLedToggleStatistics (BoardLed_t led);
