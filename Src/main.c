/*------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include <math.h>
/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//~~~~~~~~~~~~  GLOBAL VARIABLES  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static const float pi = 3.1415926535; 
static const float pi_p5 = 1.570796327; //pi* .5
static const float pi_1p5 = 4.71238898; //pi* 1.5
static const float little = 0.0000001; 
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
osThreadId LEDThread3Handle;
osThreadId MathThread1Handle,UxThread1Handle;

/* Private function prototypes -----------------------------------------------*/
static void LED_Thread3(void const *argument);
static void Math_Thread1(void const *argument);
static void Ux_Thread1(void const *argument);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int mcnt=0;

int main(void)
{


  HAL_Init();
/* Configure LED3 and LED4 */
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  /* Configure the system clock to 168 MHz */
  SystemClock_Config();

TIM_Configuration();
 uart_config();
  
 
   
  /* Thread definitions */  
  osThreadDef(LED3, LED_Thread3, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  osThreadDef(math1, Math_Thread1, osPriorityLow, 0, configMINIMAL_STACK_SIZE);
  osThreadDef(Ux1, Ux_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
  
  /* Start threads */
  LEDThread3Handle = osThreadCreate (osThread(LED3), NULL);
  MathThread1Handle = osThreadCreate (osThread(math1), NULL);
  UxThread1Handle = osThreadCreate (osThread(Ux1), NULL);
  
  /* Start scheduler */
  osKernelStart();

  /* Infinite loop */
  while (1)
  { 
  }
}

/**
  * @brief  Toggle LED3 and LED4 thread
  * @param  thread not used
  * @retval None
  */
static void LED_Thread3(void const *argument)
{
  uint32_t count = 0;
  (void) argument;
    uint8_t hb_cnt=7; // Heart Beat Counter
  
  for(;;)
  {
    osStatus status;   
    //BSP_LED_Toggle(LED3);
    status = osDelay(125);

    hb_cnt = hb_cnt==7 ? 0: hb_cnt+1;

    if ((hb_cnt==0)|(hb_cnt==2)){
        BSP_LED_On(LED3);
    }else{
        BSP_LED_Off(LED3);
    }    
    
  }

}
/**
  * @brief  Toggle LED3 and LED4 thread
  * @param  thread not used
  * @retval None
  */
static void Ux_Thread1(void const *argument)
{
  uint32_t count = 0;
  (void) argument;
  uint8_t cnt=0;
  uint32_t pcnt=0;
  
  for(;;)
  {
    osStatus status;   
    BSP_LED_Toggle(LED4);
    status = osDelay(500);   
    if (cnt == 0) {
    //
    float result = 100.0*sin((pcnt++)*pi/180.0); 
    for(int i=0;i<10;i++){ 
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
    for (int j=0;j<20;j++)
    result = 100.0*sin((result)*pi/180.0);  
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET); 
    for (int j=0;j<20;j++) 
    result = 100.0*sin((result)*pi/180.0);  
    }
    //  
    pcnt++;  
    if (result>0.1)
   uxprintf("UUUUUUU World!!!\r\n");
   cnt=1;
    }else{
    cnt=0;
    
     /*##-4- Put UART peripheral in reception process ###########################*/  
     
    uxscanf();
    
    }
    
  }

}

/**
  * @brief  Toggle LED3 and LED4 thread
  * @param  thread not used
  * @retval None
  */
static void Math_Thread1(void const *argument)
{
  uint32_t count = 0;
  (void) argument;
  uint8_t cnt=0;
  for(;;)
  {
    osStatus status;   
    //BSP_LED_Toggle(LED4);
    
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);    
    status = osDelay(1);           
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
    status = osDelay(1);

    //HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_1);
  }

}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
