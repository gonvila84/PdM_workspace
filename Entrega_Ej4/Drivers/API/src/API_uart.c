#include "main.h" //Incluido por problemas con los drivers
#include "API_uart.h"


#define UART_INSTANCE					USARTx
#define UART_BAUDRATE					9600
#define UART_WORDLENGTH					UART_WORDLENGTH_8B
#define UART_STOPBITS					UART_STOPBITS_1
#define UART_PARITY						UART_PARITY_ODD
#define UART_HWFLOWCTL					UART_HWCONTROL_NONE
#define UART_MODE						UART_MODE_TX_RX
#define UART_OVERSAMPLING				UART_OVERSAMPLING_16


#define TRANSMISSION_TIMEOUT			30000
#define TRANSMISSION_SIZE				1


static UART_HandleTypeDef uartHandler;

static const bool_t SHOW_PARAMETERS_ON_INIT = true;

void Error_Handler(void);

bool_t uartInit()
{
	uartHandler.Instance 			= UART_INSTANCE;
	uartHandler.Init.BaudRate 		= UART_BAUDRATE;
	uartHandler.Init.WordLength 	= UART_WORDLENGTH;
	uartHandler.Init.StopBits 		= UART_STOPBITS;
	uartHandler.Init.Parity			= UART_PARITY;
	uartHandler.Init.HwFlowCtl 		= UART_HWFLOWCTL;
	uartHandler.Init.Mode 			= UART_MODE;
	uartHandler.Init.OverSampling 	= UART_OVERSAMPLING;

	if (HAL_UART_Init(&uartHandler) != HAL_OK)
	{
		Error_Handler();
	}

	if (SHOW_PARAMETERS_ON_INIT)
	{
/*
		uartSendString("Instance = ");
		uartSendString(UART_INSTANCE);
		uartSendString("\n\r");

		uartSendString("BaudRate = ");
		uartSendString("WordLength = ");
		uartSendString("StopBits = ");
		uartSendString("Parity = ");
		uartSendString("HwFlowCtl = ");
		uartSendString("Mode = ");
		uartSendString("OverSampling = ");
*/
	}
}

void uartSendString(uint8_t *pstring)
{
	HAL_UART_Transmit(&uartHandler, pstring, TRANSMISSION_SIZE , TRANSMISSION_TIMEOUT);
}

void Error_Handler()
{
	while(1)
	{

	}
}

int __io_putchar(int ch)
{
	uartSendString ((uint8_t *)(&ch));
	setbuf(stdout,NULL);
}
