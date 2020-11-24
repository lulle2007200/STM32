#include "stm32l4xx.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_pwr.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_i2c.h"
#include "stm32l4xx_ll_bus.h"
#include "backlight.h"
#include "is31fl3733.h"
#include "cdc.h"
#include <stdint.h>
#include <stm32l422xx.h>

#include "usb.h"
#include "usb_cdc.h"

void SystemClockCfg(void);
void i2cInit(void);
void GpioInit(void);


int main(void){
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  	SystemClockCfg();
  	GpioInit();

  	// BacklightInit();
  	// BacklightEnable();
  	// BacklightSetColor(0x888888);
  	// BacklightUpdate();
  	//
  	USBDInit();
  	//usb_start();
    while(1) {
    }


	return(1);
}

void GpioInit(void){
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
	LL_GPIO_InitTypeDef GpioInitStruct = {0};

	GpioInitStruct.Pin = LL_GPIO_PIN_0;
	GpioInitStruct.Alternate = LL_GPIO_AF_0;
	GpioInitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GpioInitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GpioInitStruct.Pull = LL_GPIO_PULL_DOWN;
	GpioInitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	LL_GPIO_Init(GPIOA, &GpioInitStruct);
	LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_0);

	LL_GPIO_InitTypeDef GpioInitStruct1 = {0};

	GpioInitStruct1.Pin = LL_GPIO_PIN_11 | LL_GPIO_PIN_12;
	GpioInitStruct1.Alternate = LL_GPIO_AF_10;
	GpioInitStruct1.Mode = LL_GPIO_MODE_OUTPUT;
	LL_GPIO_Init(GPIOA, &GpioInitStruct1);

}

void SystemClockCfg(void){
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);

	LL_RCC_HSI_Enable();
	while(LL_RCC_HSI_IsReady() != 1){};
	LL_RCC_HSI_SetCalibTrimming(16);

	LL_RCC_PLL_SetMainSource(LL_RCC_PLLSOURCE_HSI);
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_1,
	                            18, LL_RCC_PLLR_DIV_4);
	LL_RCC_PLL_EnableDomain_SYS();
	LL_RCC_PLL_Enable();
	while(LL_RCC_PLL_IsReady() != 1){};

	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL){};

	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_SYSCLK_DIV_1);

	LL_SetSystemCoreClock(72000000);
	LL_Init1msTick(72000000);

	LL_RCC_HSI48_Enable();
	while(LL_RCC_HSI48_IsReady() != 1){};
	LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_HSI48);

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	LL_PWR_EnableVddUSB();
}

void Error_Handler(void){
	return;
}