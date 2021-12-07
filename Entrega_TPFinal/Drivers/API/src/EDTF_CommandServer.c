#include <EDTF_API_debounce.h>
#include <EDTF_API_delay.h>
#include <EDTF_API_led.h>
#include <EDTF_API_uart.h>
#include <EDTF_CommandServer.h>
#include <string.h>

#define EXEC_BUFFER_MAX_COMM_NUMBER							5

#define CMD0_DELAY_MS										9999
#define CMD1_DELAY_MS										9000
#define CMD2_DELAY_MS										8800
#define CMD3_DELAY_MS										7000
#define CMD4_DELAY_MS										3000

#define CMD0_PID											0
#define CMD1_PID											1
#define CMD2_PID											2
#define CMD3_PID											3
#define CMD4_PID											4

typedef uint8_t serverpid_t;

typedef enum {
	Listen_Command,
	Blink_Start_Signal,
	Exec_Command,
	Send_Result,
	Blink_Finish_Signal,
} CommandServerState_t;

typedef struct {
	serverpid_t 		pid;
	bool_t  			finishedProcessing;
}process_t;

typedef struct {
	process_t 			processes [EXEC_BUFFER_MAX_COMM_NUMBER];
	bool_t 				isbufferReadyForProcessing;
}processBuffer_t;

static processBuffer_t processBuffer;

//Esta variable gobierna el estado de la FSM
static CommandServerState_t currentCommandServerState;

// Creo 5 delays para los comandos individuales.
static delay_t cmd0Delay;
static delay_t cmd1Delay;
static delay_t cmd2Delay;
static delay_t cmd3Delay;
static delay_t cmd4Delay;

static bool_t showPrompt;

void initCommandServer (void);
void updateCommandServerState (void);
void initCommandBuffer(void);
void updateBatchReadiness (void);
void finishProcess (serverpid_t processNumber);
void simulateWorkload (void);
void commandServerErrorHandler(void);
void printBatchProcessesStatus(void);

bool_t isBatchReadyForProcessing (void);
bool_t isProcessFinished (serverpid_t processNumber);
bool_t isPidValid (serverpid_t processNumber);

void initCommandServer ()
{
	//El modulo command server realiza la gestion integral de los procesos, invoca la inicializacion de otros modulos.

	initCommandBuffer();

	delayInit(&cmd0Delay,CMD0_DELAY_MS);
	delayInit(&cmd1Delay,CMD1_DELAY_MS);
	delayInit(&cmd2Delay,CMD2_DELAY_MS);
	delayInit(&cmd3Delay,CMD3_DELAY_MS);
	delayInit(&cmd4Delay,CMD4_DELAY_MS);

	uartInit();

	BoardLed_t greenLed = Green_Led;
	initiateLed (greenLed);

	BoardLed_t redLed = Red_Led;
	initiateLed (redLed);

	debounceInit();
	showPrompt = true;
	currentCommandServerState = Listen_Command;
}

void updateCommandServerState ()
{
	switch(currentCommandServerState)
	{
		case Listen_Command:
			debounceUpdate();

			if (consumeSinglePressEvent() && (!isBatchReadyForProcessing())) //Ante la presion del boton se simula la llegada de nuevos comandos. Solo si el lote esta listo (si el estado processing es false).
			{
				simulateWorkload();
			}

			//Verifico si el lote de comandos esta listo para la ejecucion.
			if (isBatchReadyForProcessing())
			{
				showPrompt = true;
				currentCommandServerState = Blink_Start_Signal;
			}
			else
			{
				if (showPrompt)
				{
					printf("Presione el boton para ejecutar otro lote de procesos.\r\n");
					showPrompt = false;
				}
				currentCommandServerState = Listen_Command;
			}
			break;

		case Blink_Start_Signal:
			turnLed(Green_Led, On);
			currentCommandServerState = Exec_Command;
			break;

		case Exec_Command:

			// Le doy una cuota de ejecucion a cada uno
			// Si alcanzaron la cuota actualizan su flag propio
			if (!isProcessFinished(CMD0_PID))
			{
				if (delayRead(&cmd0Delay)){finishProcess (CMD0_PID);};
			}
			if (!isProcessFinished(CMD1_PID))
			{
				if (delayRead(&cmd1Delay)){finishProcess (CMD1_PID);};
			}
			if (!isProcessFinished(CMD2_PID))
			{
				if (delayRead(&cmd2Delay)){finishProcess (CMD2_PID);};
			}
			if (!isProcessFinished(CMD3_PID))
			{
				if (delayRead(&cmd3Delay)){finishProcess (CMD3_PID);};
			}
			if (!isProcessFinished(CMD4_PID))
			{
				if (delayRead(&cmd4Delay)){finishProcess (CMD4_PID);};
			}

			//Actualizo el flag general de verificacion del lote
			updateBatchReadiness();
			currentCommandServerState = Send_Result;
			break;

		case Send_Result:

			printBatchProcessesStatus();
			//Imprimo el estado del flag de cada proceso.
			currentCommandServerState = Blink_Finish_Signal;
			break;

		case Blink_Finish_Signal:
			turnLed(Green_Led, Off);
			currentCommandServerState = Listen_Command;
			break;
	}
}

/* Funciones de ayuda para CommandServer*/

bool_t isProcessFinished (serverpid_t processNumber)
{
	if (!isPidValid(processNumber))
	{
		commandServerErrorHandler();
	}
	bool_t isFinished = false;
	if (processBuffer.processes[processNumber].finishedProcessing)
	{
		isFinished = true;
	}
	return isFinished;
}

void finishProcess (serverpid_t processNumber)
{
	if (!isPidValid(processNumber))
	{
		commandServerErrorHandler();
	}
	processBuffer.processes[processNumber].finishedProcessing = true;
}

void runProcess (serverpid_t processNumber)
{
	if (!isPidValid(processNumber))
	{
		commandServerErrorHandler();
	}

	processBuffer.processes[processNumber].finishedProcessing = false;

	switch (processNumber)
	{
		case CMD0_PID:
			delayWrite (&cmd0Delay, CMD0_DELAY_MS);
			break;
		case CMD1_PID:
			delayWrite (&cmd1Delay, CMD1_DELAY_MS);
			break;
		case CMD2_PID:
			delayWrite (&cmd2Delay, CMD2_DELAY_MS);
			break;
		case CMD3_PID:
			delayWrite (&cmd3Delay, CMD3_DELAY_MS);
			break;
		case CMD4_PID:
			delayWrite (&cmd4Delay, CMD4_DELAY_MS);
			break;
	}
	updateBatchReadiness();
}


void initCommandBuffer()
{
	for (serverpid_t i = 0; i < EXEC_BUFFER_MAX_COMM_NUMBER; i++)
	{
		processBuffer.processes[i].pid = i;
		processBuffer.processes[i].finishedProcessing = false;
	}
	processBuffer.isbufferReadyForProcessing = false;
}

bool_t isBatchReadyForProcessing ()
{
	return processBuffer.isbufferReadyForProcessing;
}


void updateBatchReadiness (void)
{
	uint8_t numberOfFinishedProcesses = 0;
	for (serverpid_t i = 0; i < EXEC_BUFFER_MAX_COMM_NUMBER; i++)
	{
		if (isProcessFinished(i))
		{
			numberOfFinishedProcesses ++;
		}
	}

	if (EXEC_BUFFER_MAX_COMM_NUMBER == numberOfFinishedProcesses)
	{
		processBuffer.isbufferReadyForProcessing = false;
	}
	else
	{
		processBuffer.isbufferReadyForProcessing = true;
	}
}



void printBatchProcessesStatus()
{
	printf("Cycle : ( ");
	for (serverpid_t i = 0; i < EXEC_BUFFER_MAX_COMM_NUMBER; i++)
	{
		if (true == processBuffer.processes[i].finishedProcessing)
		{
			switch(i)
			{
				case CMD0_PID:
					printf(" PROCESS 0: FINISHED |");
					break;
				case CMD1_PID:
					printf(" PROCESS 1: FINISHED |");
					break;
				case CMD2_PID:
					printf(" PROCESS 2: FINISHED |");
					break;
				case CMD3_PID:
					printf(" PROCESS 3: FINISHED |");
					break;
				case CMD4_PID:
					printf(" PROCESS 4: FINISHED  ");
					break;
			}
		}
		else
		{
			switch(i)
			{
				case CMD0_PID:
					printf(" PROCESS 0: RUNNING  |");
					break;
				case CMD1_PID:
					printf(" PROCESS 1: RUNNING  |");
					break;
				case CMD2_PID:
					printf(" PROCESS 2: RUNNING  |");
					break;
				case CMD3_PID:
					printf(" PROCESS 3: RUNNING  |");
					break;
				case CMD4_PID:
					printf(" PROCESS 4: RUNNING   ");
					break;
			}
		}
	}
	printf(" )\r\n");
}

void simulateWorkload ()
{
	for (serverpid_t i=0;i<EXEC_BUFFER_MAX_COMM_NUMBER;i++)
	{
		runProcess(i);
	}
}

bool_t isPidValid (serverpid_t processNumber)
{
	bool_t validPid = false;
	if (processNumber >= 0 && processNumber <= EXEC_BUFFER_MAX_COMM_NUMBER) //Verifico que el pid este en el rango valido
	{
		validPid = true;
	}
	return validPid;
}

void commandServerErrorHandler()
{
	turnLed(Red_Led, On);
	while (1)
	{
	}
}
