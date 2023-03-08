/* USER CODE BEGIN Header */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "spi.h"
#include "ST7735.h"
#include "GFX_FUNCTIONS.h"
#include "keyboard.h"
#include "limits.h"
#include "screen.h"
#include "utils.h"
#include "calibration.h"
#include "alt_main.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t b_kernel_up=0;
volatile char aTxBuffer[64]="SENDTHISSENDTHIS";
volatile char aRxBuffer[64]="EMPTEMPTEMPTEMPT";
uint32_t dummy=0;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */



volatile uint8_t limit_status=0;
volatile int32_t counter[3]={0,0,0};
volatile int32_t velocity[3]={0,0,0};
volatile uint8_t emagnet=0;
volatile uint8_t b_demo=0;
volatile uint8_t controller_calibration_mode=0;
volatile uint8_t hdr_received;


//			  (*pT5)= (uint32_t)TIM5->CNT;
//			  (*pT2)= (uint32_t)TIM2->CNT;
void TransmitTest(uint8_t* testdata, uint32_t size);
void InitTargetPos();

uint8_t signal=0;

volatile int16_t vPWMX=0;
volatile int16_t vPWMY=0;
volatile uint8_t vFreqDiv=3;
volatile uint8_t b_startcalib;

ScreenInfo screeninfo = {0};

uint32_t frame=0;
//float total_error_I=0;

//volatile float target[2]={0};
//volatile float target_v[2]={0};


/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	alt_main();
	  printf("LCD Init:%i\n",counter[0]);

	  ST7735_Init(1);

	  HAL_GPIO_WritePin(LCD_LED_GPIO_Port, LCD_LED_Pin, GPIO_PIN_RESET);

      ST7735_FillRectangle(0, 0, 162, 82, BLACK);

	  int16_t y=2;
	  while(y>-39)
	  {
		  if(y>0)
		  {
			  ST7735_DrawImage(0,y, 162, 38, logo);
			  ST7735_DrawImage(0,82-y - 38, 162, 38, logo);

			  ST7735_DrawImage(0,82-y-39, 162, 1, logo + 162*37); //black line
		  }
		  else
		  {
			  ST7735_DrawImage(0,0, 162, 38+y, logo - 162*y);

			  if(y==-10)
			  {
				  ST7735_WriteString(0,40-18/2, "Palans --> SP", Font_11x18, WHITE, BLACK);
			  }

			  ST7735_DrawImage(0,82-y-38, 162, 38+y, logo);
			  ST7735_DrawImage(0,82-y-39, 162, 1, logo + 162*37); //black line
		  }
		  if(y==2)osDelay(500);
		  osDelay(20);
		  y--;
	  }

      uint8_t last_b_changed=0;

	  uint32_t cnt=0;
	  for(;;)
	  {
		    SystemCoreClockUpdate();

			scanKeyboard();

			if(!b_demo)
			{
				vPWMX=0;
				vPWMY=0;
				if(keyPressed('6'))
				{
					vPWMX=12000;
				}
				if(keyPressed('4'))
				{
					vPWMX=-12000;
				}
				if(keyPressed('2'))
				{
					vPWMY=5000;
				}
				if(keyPressed('8'))
				{
					vPWMY=-5000;
				}
			}

			if(keyClicked('#'))
			{
				screeninfo.page = (screeninfo.page+1)%2;
			}


			if(screeninfo.page==0)
			{
				if(keyClicked('A')){emagnet=100;}
				if(keyClicked('B')){emagnet=0;}
			}
			else
			{

/*				if(keyClicked('A'))
				{
					vFreqDiv=4;
				}
				if(keyClicked('B'))
				{
					vFreqDiv=5;
				}
				if(keyClicked('C'))
				{
					vFreqDiv=10;
				}
				if(keyClicked('D'))
				{
					vFreqDiv=20;
				}*/
			}

			if(keyClicked('D'))
			{
				b_demo = (b_demo+1)%2;
				if(b_demo)
				{
//					startCalibration();
					startDemo();
//					InitTargetPos();
				}
				else
				{
					stopDemo();
					vPWMX=0;
					vPWMY=0;
				}
			}

			if(keyClicked('*'))
			{
				b_startcalib=1;
			}


			for(int i=0;i<3;++i)
			{
				screeninfo.counter[i] = counter[i];
				screeninfo.velocity[i] = velocity[i];
			}
			screeninfo.header_char = hdr_received;
			screeninfo.freq_update = 20000/vFreqDiv;
			screeninfo.emagnet = emagnet;
			screeninfo.limit_status = limit_status;
			screeninfo.pwm[0]=vPWMX;
			screeninfo.pwm[1]=vPWMY;
		//	screeninfo.target[0]=target[0];
		//	screeninfo.target[1]=target[1];
			screeninfo.b_controlloop = isCalibratingMode(controller_calibration_mode);
			{
				screeninfo.target[0]= ((float)screeninfo.counter[0])*PPR_TO_DISTANCE_X;
				screeninfo.target[1]= ((float)screeninfo.counter[1])*PPR_TO_DISTANCE_Y;
			}
			screeninfo.calibration_mode = controller_calibration_mode;// getCalibrationMode();

			if(b_demo)
			{
				screeninfo.calibration_mode= getCalibrationMode();
			}

//			for(int i=0;i<2;++i)
//			{
//				screeninfo.target[i]=target[i];
//			}

			updateScreen(&screeninfo);

//			HAL_Delay(10);
//		    osDelay(5);
//			for(uint32_t i=0;i<4000;i++)dummy+=i;
		//  osDelay(1);
	  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/*

float getDt()
{
	return 1.f/ ( (float)( 20000/vFreqDiv));
}

uint32_t getCyclesPerSecond()
{
	return 20000/vFreqDiv;
}

void InitTargetPos()
{
	frame=0;
	target[0]=0;
	target_v[0]=1.;
}

void ComputeTargetPos(uint32_t frame)
{
	if(frame%10000<5000)
	{
		target[0]=1;
		target[1]=0;
	}
	else
	{
		target[0]=-1;
		target[1]=0;
	}

	float dt = getDt();

	target[0]+=target_v[0]*dt;

	if(target[0]>2.5f)target_v[0]*=-1.f;
	if(target[0]<-2.5f)target_v[0]*=-1.f;

}

#define PPM_X 4000.f

void UpdateControlLoop()
{
	if(!b_demo)return;

	frame++;

	ComputeTargetPos(frame);

	float dt = getDt();

	float v_x = ( (float)velocity[0] )/ (dt* PPM_X);
	float p_x =  ((float)counter[0]) / PPM_X;

	float target_p_x = target[0];
	float target_v_x = target_v[0];


	float error_P = target_p_x - p_x;
	float error_D = target_v_x - v_x;
	total_error_I += error_P*dt;

#define K_P 10.f
#define K_I 3.f
#define K_D .5f

	float pwm_output = error_P*(K_P)+ error_D*(K_D);

	int32_t vPWMX_out = (int32_t)(pwm_output*12000);

	if(vPWMX_out>10000)vPWMX_out=10000;
	if(vPWMX_out<-10000)vPWMX_out=-10000;

	vPWMX = vPWMX_out;
}*/

uint8_t cnt2=0;

/*
void SPI1_Transfer(uint8_t *outp, uint8_t *inp, int count) {
    while(count--) {
        while(!(SPI1->SR & SPI_SR_TXE))
            ;
        *(volatile uint8_t *)&SPI1->DR = *outp++;
        while(!(SPI1->SR & SPI_SR_RXNE))
            ;
        *inp++ = *(volatile uint8_t *)&SPI1->DR;
    }
}*/


/*
void SPI_Transmit(uint8_t *data, int size)
{

	/************** STEPS TO FOLLOW *****************
	1. Wait for the TXE bit to set in the Status Register
	2. Write the data to the Data Register
	3. After the data has been transmitted, wait for the BSY bit to reset in Status Register
	4. Clear the Overrun flag by reading DR and SR
	************************************************/
/*
	int i=0;
	while (i<size)
	{
	   while (!((SPI1->SR)&(1<<1))) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
	   SPI1->DR = data[i];  // load the data into the Data Register
	   i++;
	}


/*During discontinuous communications, there is a 2 APB clock period delay between the
write operation to the SPI_DR register and BSY bit setting. As a consequence it is
mandatory to wait first until TXE is set and then until BSY is cleared after writing the last
data.
*//*
	while (!((SPI1->SR)&(1<<1))) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
	while (((SPI1->SR)&(1<<7))) {};  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication

	//  Clear the Overrun flag by reading DR and SR
	uint8_t temp = SPI1->DR;
					temp = SPI1->SR;

}*/


void TransmitTest(uint8_t* testdata, uint32_t size)
{
	// data to be transmitted
//	uint8_t testdata = 'U';

	// This value will point limit to HW's counter
	SPI1->CR2 |= (SPI_CR2_TSIZE & size);

	// SPI enable
	SPI1->CR1 |= SPI_CR1_SPE;

	/*

				If global SPI interrupt needed
				- Enable it here, after SPI enable (errata)
				  and before CSTART

	*/

	// start transmission
	SPI1->CR1 |= SPI_CR1_CSTART;


	for(int a=0;a<size;++a)
	{

		// if TxFIFO has enough free location to host 1 data packet
		// --> put data to TXDR
		if(((SPI1->SR) & SPI_SR_TXP) == SPI_SR_TXP){
			*((__IO uint8_t*)&SPI1->TXDR) = testdata[a];

		}
	}

	// wait end of the transmission
	while(((SPI1->SR) & SPI_SR_EOT) != SPI_SR_EOT){};

	// SPI disable (errata)
	SPI1->CR1 |= SPI_CR1_SPE;
}


#pragma GCC optimize ("O0")

void SlowThisDown()
{
	for(uint32_t i=0;i<2;i++)dummy+=dummy+1;
}
#pragma GCC pop_options


void SPITransmitReceive()
{
	HAL_GPIO_WritePin(CSS_GPIO_Port, CSS_Pin, GPIO_PIN_RESET);

	SlowThisDown();

	uint8_t* pHDR=(uint8_t*)(aTxBuffer);
	uint8_t* pCMD=(uint8_t*)(aTxBuffer+1);
	uint8_t* pEMG=(uint8_t*)(aTxBuffer+2);
	uint16_t* pPWMX=(uint16_t*)(aTxBuffer+12);
	uint16_t* pPWMY=(uint16_t*)(aTxBuffer+14); //Write these last! So we can compute them in the middle of the message!

	uint8_t vCMD=1;
	if(b_startcalib)
	{
		vCMD=2;
		b_startcalib=0;
	}
	*pHDR='C';
	*pCMD=vCMD;
	*pEMG=emagnet;

	HAL_StatusTypeDef state = HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)aTxBuffer, (uint8_t*)aRxBuffer, 8, 100);


	{ //Update counter x and y.
		int32_t* pT5 = (int32_t*)(aRxBuffer);
		int32_t* pT2 = (int32_t*)(aRxBuffer+4);

		uint32_t old_counter[2];
		for(int i=0;i<2;++i)old_counter[i]=counter[i];

		counter[0]=*pT5;
		counter[1]=*pT2;

		for(int i=0;i<2;++i)velocity[i] = counter[i]-old_counter[i];
	}


	if(b_demo)
	{
		int32_t rPWM[2];
		updateCalibration(counter, velocity, limit_status, &rPWM);

		vPWMX = rPWM[0];
		vPWMY = rPWM[1];
	}
	*pPWMX=vPWMX;
	*pPWMY=vPWMY;

	state = HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)(aTxBuffer+8), (uint8_t*)(aRxBuffer+8), 8, 100);
	HAL_GPIO_WritePin(CSS_GPIO_Port, CSS_Pin, GPIO_PIN_SET);

	int16_t* pT3 = (int16_t*)(aRxBuffer+8);
    pHDR = (uint8_t*)(aRxBuffer+10);
	uint8_t* plimit = (uint8_t*)(aRxBuffer+11);
	uint8_t* pcalibrationmode = (uint8_t*)(aRxBuffer+12);
	uint8_t* pvFreqDiv = (uint8_t*)(aRxBuffer+13);

	hdr_received = *pHDR;

	if(*pHDR=='C')
	{
		uint32_t old_counter[3];
		for(int i=2;i<3;++i)old_counter[i]=counter[i];

//		counter[0]=*pT5; //0 and 1 are being updated before the transmission of the second group of 8 characters.
//		counter[1]=*pT2; // so only update the angle Theta counter. (Which will be one frame late to the control loop, but this is not critical.
		counter[2]=*pT3;

		for(int i=2;i<3;++i)velocity[i]=counter[i]-old_counter[i];

		limit_status=*plimit;
		controller_calibration_mode = *pcalibrationmode;
		vFreqDiv = *pvFreqDiv;

		if(vFreqDiv==0)vFreqDiv=1;
	}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == SPULSE_Pin)
	{
		SPITransmitReceive();
	}

/*	if(GPIO_Pin == CSS_Pin)
	{


	}*/
}



float getDt()
{
	return 1.f/ ( (float)( 20000/vFreqDiv));
}

float getOneOverDt()
{
	return ( (float)( 20000/vFreqDiv));
}

//Can't do that from here! For compatibility with calibration.c
void resetCounter()
{
}

//same
void setCounter(uint8_t id_tim, int32_t value)
{
}

/* USER CODE END Application */

