#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_i2c.h"
#include "stm32l4xx_ll_dma.h"
#include "is31fl3733.h"
#include "is31fl3733_config.h"


typedef struct is31fl3733_s{
	uint8_t CurrentPage;
	uint8_t Config;
	uint16_t LEDRegister[12];
	uint8_t PWMRegister[12][16];
	uint8_t ModeRegister[12][16];
}is31fl3733_t;



static is31fl3733_t gIs31fl3733State[IS31FL3733_COUNT] = {0};
static const uint8_t gIs31fl3733Address[IS31FL3733_COUNT] = IS31FL3733_ADDRESS;

void Is31fl3733SendCommand(uint8_t pIndex, uint8_t pRegister, uint8_t pValue){
	LL_I2C_HandleTransfer(IS31FL3733_I2C, gIs31fl3733Address[pIndex], LL_I2C_ADDRSLAVE_7BIT, 2, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
	while(!LL_I2C_IsActiveFlag_TXIS(IS31FL3733_I2C)){};
	LL_I2C_TransmitData8(IS31FL3733_I2C, pRegister);
	while(!LL_I2C_IsActiveFlag_TXIS(IS31FL3733_I2C)){};
	LL_I2C_TransmitData8(IS31FL3733_I2C, pValue);
	while(!LL_I2C_IsActiveFlag_STOP(IS31FL3733_I2C));
	LL_I2C_ClearFlag_STOP(IS31FL3733_I2C);
}

void Is31fl3733SendBuffer(uint8_t pIndex, uint8_t pRegister, uint8_t *pBuffer, uint8_t pBufferSize){
	LL_I2C_HandleTransfer(IS31FL3733_I2C, gIs31fl3733Address[pIndex], LL_I2C_ADDRSLAVE_7BIT, pBufferSize + 1, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
	while(!LL_I2C_IsActiveFlag_TXIS(IS31FL3733_I2C)){};
	LL_I2C_TransmitData8(IS31FL3733_I2C, pRegister);
	uint8_t *current = pBuffer;
	while(!LL_I2C_IsActiveFlag_STOP(IS31FL3733_I2C)){
		if(LL_I2C_IsActiveFlag_TXIS(IS31FL3733_I2C)){
			LL_I2C_TransmitData8(IS31FL3733_I2C, *current);
			current++;
		}
	}
	LL_I2C_ClearFlag_STOP(IS31FL3733_I2C);
}

void Is31fl3733SendBufferDMA(uint8_t pIndex, uint8_t *pBuffer, uint8_t pBufferSize){
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_4, (uint32_t)pBuffer);
	

}

void Is31fl3733UnlockPageRegister(uint8_t pIndex){
	Is31fl3733SendCommand(pIndex, IS31FL3733_CRWL_REG, IS31FL3733_CRWL_UNLOCK_KEY);
}

void Is31fl3733SetPage(uint8_t pIndex, uint8_t pPage){
	if(gIs31fl3733State[pIndex].CurrentPage != pPage){
		Is31fl3733UnlockPageRegister(pIndex);
		Is31fl3733SendCommand(pIndex, IS31FL3733_PGSELECT_REG, pPage);
		gIs31fl3733State[pIndex].CurrentPage = pPage;
	}
}

void Is31fl3733SetConfig(uint8_t pIndex, uint8_t pConfig){
	Is31fl3733SetPage(pIndex, IS31FL3733_PGSELECT_PG3);
	Is31fl3733SendCommand(pIndex, IS31FL3733_CFG_REG, pConfig);
	gIs31fl3733State[pIndex].Config = pConfig;
}

void Is31fl3733SetItMask(uint8_t pIndex, uint8_t pInterrupts){
	Is31fl3733SendCommand(pIndex, IS31FL3733_ITMASK_REG, pInterrupts);
}

void Is31fl3733LEDEnable(uint8_t pIndex, uint8_t pCS, uint8_t pSW){
	gIs31fl3733State[pIndex].LEDRegister[pSW] |= (0b1 << pCS);
}

void Is31fl3733LEDDisable(uint8_t pIndex, uint8_t pCS, uint8_t pSW){
	gIs31fl3733State[pIndex].LEDRegister[pSW] &= (~(0b1 << pCS));
}

void Is31fl3733LEDToggle(uint8_t pIndex, uint8_t pCS, uint8_t pSW){
	gIs31fl3733State[pIndex].LEDRegister[pSW] ^= (0b1 << pCS);
}

void Is31fl3733LEDSetBrightness(uint8_t pIndex, uint8_t pCS, uint8_t pSW, uint8_t pBrightness){
	gIs31fl3733State[pIndex].PWMRegister[pSW][pCS] = pBrightness;
}

void Is31fl3733LEDSetMode(uint8_t pIndex, uint8_t pCS, uint8_t pSW, uint8_t pMode){
	gIs31fl3733State[pIndex].ModeRegister[pSW][pCS] = pMode;
}

void Is31fl3733AutoBreathEnable(uint8_t pIndex){
	gIs31fl3733State[pIndex].Config |= IS31FL3733_CFG_BEN;
	Is31fl3733SetPage(pIndex, IS31FL3733_PGSELECT_PG3);
	Is31fl3733SendCommand(pIndex, IS31FL3733_CFG_REG, gIs31fl3733State[pIndex].Config);
}

void Is31fl3733AutoBreathDisable(uint8_t pIndex){
	gIs31fl3733State[pIndex].Config |= (~IS31FL3733_CFG_BEN);
	Is31fl3733SetPage(pIndex, IS31FL3733_PGSELECT_PG3);
	Is31fl3733SendCommand(pIndex, IS31FL3733_CFG_REG, gIs31fl3733State[pIndex].Config);
}

void Is31fl3733GlobalBrightnessSet(uint8_t pIndex, uint8_t pBrightness){
	Is31fl3733SetPage(pIndex, IS31FL3733_PGSELECT_PG3);
	Is31fl3733SendCommand(pIndex, IS31FL3733_GCC_REG, pBrightness);
}

void Is31fl3733SWPullUpSet(uint8_t pIndex, uint8_t pPullUp){
	Is31fl3733SetPage(pIndex, IS31FL3733_PGSELECT_PG3);
	Is31fl3733SendCommand(pIndex, IS31FL3733_SW_PUR_REG, pPullUp);
}

void Is31fl3733CSPullDownSet(uint8_t pIndex, uint8_t pPullDown){
	Is31fl3733SetPage(pIndex, IS31FL3733_PGSELECT_PG3);
	Is31fl3733SendCommand(pIndex, IS31FL3733_SW_PUR_REG, pPullDown);
}

void Is31fl3733UpdateMatrix(uint8_t pIndex){
	Is31fl3733SetPage(pIndex, IS31FL3733_PGSELECT_PG1);
	Is31fl3733SendBuffer(pIndex, IS31FL3733_PWM_REG, (uint8_t *)gIs31fl3733State[pIndex].PWMRegister, 144);
	Is31fl3733SetPage(pIndex, IS31FL3733_PGSELECT_PG0);
	Is31fl3733SendBuffer(pIndex, IS31FL3733_PWM_REG, (uint8_t *)gIs31fl3733State[pIndex].LEDRegister, 24);
}




void Is31fl3733DMAConfig(void){
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	NVIC_SetPriority(DMA1_Channel4_IRQn, 0x04);
	NVIC_EnableIRQ(DMA1_Channel4_IRQn);

	LL_DMA_ConfigTransfer(DMA1, LL_DMA_CHANNEL_4, 
	                      LL_DMA_DIRECTION_MEMORY_TO_PERIPH |	\
	                      LL_DMA_MODE_NORMAL |					\
	                      LL_DMA_PERIPH_NOINCREMENT |			\
	                      LL_DMA_MEMORY_INCREMENT |				\
	                      LL_DMA_MDATAALIGN_BYTE |				\
	                      LL_DMA_PDATAALIGN_BYTE |				\
	                      LL_DMA_PRIORITY_HIGH);

	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_4, LL_DMA_REQUEST_3);

	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_4, (uint32_t)&(I2C2->TXDR));

	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_4);
}

void Is31fl3733I2CConfig(void){
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_10, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_10, LL_GPIO_AF_4);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_10, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_10, LL_GPIO_OUTPUT_OPENDRAIN);
	LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_10, LL_GPIO_PULL_NO);

	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_11, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_11, LL_GPIO_AF_4);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_11, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_11, LL_GPIO_OUTPUT_OPENDRAIN);
	LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_11, LL_GPIO_PULL_NO);


	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);

	LL_RCC_SetI2CClockSource(LL_RCC_I2C2_CLKSOURCE_SYSCLK);

	LL_I2C_SetTiming(I2C2, 0x00e12573);

	LL_I2C_SetMode(I2C2, LL_I2C_MODE_I2C);

	//LL_I2C_EnableDMAReq_TX(I2C2);

	LL_I2C_Enable(I2C2);	
}

void Is31fl3733GPIOConfig(void){
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_13, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_13, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_13, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_13, LL_GPIO_PULL_NO);
}

void Is31fl3733Enable(void){
	#ifdef IS31FL3733_HW_SHUTDOWN
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_13);
	#else
	for(uint8_t Index = 0; Index < IS31FL3733_COUNT; Index++){
		gIs31fl3733State[Index].Config |= IS31FL3733_CFG_SSD;
		Is31fl3733SetPage(Index, IS31FL3733_PGSELECT_PG3);
		Is31fl3733SendCommand(Index, IS31FL3733_CFG_REG, gIs31fl3733State[Index].Config);
	}
	#endif
}

void Is31fl3733Disable(void){
	#ifdef IS31FL3733_HW_SHUTDOWN
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_13);
	#else
	for(uint8_t Index = 0; Index < IS31FL3733_COUNT; Index++){
		gIs31fl3733State[Index].Config &= (~IS31FL3733_CFG_SSD);
		Is31fl3733SetPage(Index, IS31FL3733_PGSELECT_PG3);
		Is31fl3733SendCommand(Index, IS31FL3733_CFG_REG, gIs31fl3733State[Index].Config);
	}
	#endif
}

void Is31fl3733Deinit(void){

}

void Is31fl3733Init(void){
	Is31fl3733I2CConfig();

	#ifdef IS31FL3733_HW_SHUTDOWN
	Is31fl3733GPIOConfig();
	#endif

	for(uint8_t i = 0; i < IS31FL3733_COUNT; i++){
		gIs31fl3733State[i].CurrentPage = IS31FL3733_PGSELECT_NOT_SET;
		#ifdef IS31FL3733_HW_SHUTDOWN
		Is31fl3733SetConfig(i, IS31FL3733_CFG_SYNC_SLAVE | IS31FL3733_CFG_SSD | IS31FL3733_CFG_BEN);
		#else
		Is31fl3733SetConfig(i, IS31FL3733_CFG_SYNC_SLAVE | IS31FL3733_CFG_BEN);
		#endif
		Is31fl3733SWPullUpSet(i, IS31FL3733_SW_PULL_UP);
		Is31fl3733CSPullDownSet(i, IS31FL3733_CS_PULL_DOWN);
		Is31fl3733GlobalBrightnessSet(i, 255);
	}
	Is31fl3733SetConfig(0, IS31FL3733_CFG_SYNC_MASTER | IS31FL3733_CFG_SSD | IS31FL3733_CFG_BEN);
}