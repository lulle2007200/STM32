.thumb
.syntax	unified
.cpu	cortex-m4
.fpu	softvfp

.section .interrupt_vector_table,"a", %progbits

.word		stack_end

.word		Reset_Handler

.word		NMI_Handler
.weak		NMI_Handler
.thumb_set	NMI_Handler,Default_Handler

.word		HardFault_Handler
.weak		HardFault_Handler
.thumb_set	HardFault_Handler,Default_Handler

.word		MemManage_Handler
.weak		MemManage_Handler
.thumb_set	MemManage_Handler,Default_Handler

.word		BusFault_Handler
.weak		BusFault_Handler
.thumb_set	BusFault_Handler,Default_Handler

.word		UsageFault_Handler
.weak		UsageFault_Handler
.thumb_set	UsageFault_Handler,Default_Handler

.word		0
.word		0
.word		0
.word		0

.word		SVC_Handler
.weak		SVC_Handler
.thumb_set	SVC_Handler,Default_Handler

.word		DebugMon_Handler
.weak		DebugMon_Handler
.thumb_set	DebugMon_Handler,Default_Handler

.word		0

.word		PendSV_Handler
.weak		PendSV_Handler
.thumb_set	PendSV_Handler,Default_Handler

.word		SysTick_Handler
.weak		SysTick_Handler
.thumb_set	SysTick_Handler,Default_Handler

.word		WWDG_IRQHandler
.weak		WWDG_IRQHandler
.thumb_set	WWDG_IRQHandler,Default_Handler

.word		PVD_PVM_IRQHandler
.weak		PVD_PVM_IRQHandler
.thumb_set	PVD_PVM_IRQHandler,Default_Handler

.word		TAMP_STAMP_IRQHandler
.weak		TAMP_STAMP_IRQHandler
.thumb_set	TAMP_STAMP_IRQHandler,Default_Handler

.word		RTC_WKUP_IRQHandler
.weak		RTC_WKUP_IRQHandler
.thumb_set	RTC_WKUP_IRQHandler,Default_Handler

.word		FLASH_IRQHandler
.weak		FLASH_IRQHandler
.thumb_set	FLASH_IRQHandler,Default_Handler

.word		RCC_IRQHandler
.weak		RCC_IRQHandler
.thumb_set	RCC_IRQHandler,Default_Handler

.word		EXTI0_IRQHandler
.weak		EXTI0_IRQHandler
.thumb_set	EXTI0_IRQHandler,Default_Handler

.word		EXTI1_IRQHandler
.weak		EXTI1_IRQHandler
.thumb_set	EXTI1_IRQHandler,Default_Handler

.word		EXTI2_IRQHandler
.weak		EXTI2_IRQHandler
.thumb_set	EXTI2_IRQHandler,Default_Handler

.word		EXTI3_IRQHandler
.weak		EXTI3_IRQHandler
.thumb_set	EXTI3_IRQHandler,Default_Handler

.word		EXTI4_IRQHandler
.weak		EXTI4_IRQHandler
.thumb_set	EXTI4_IRQHandler,Default_Handler

.word		DMA1_Channel1_IRQHandler
.weak		DMA1_Channel1_IRQHandler
.thumb_set	DMA1_Channel1_IRQHandler,Default_Handler

.word		DMA1_Channel2_IRQHandler
.weak		DMA1_Channel2_IRQHandler
.thumb_set	DMA1_Channel2_IRQHandler,Default_Handler

.word		DMA1_Channel3_IRQHandler
.weak		DMA1_Channel3_IRQHandler
.thumb_set	DMA1_Channel3_IRQHandler,Default_Handler

.word		DMA1_Channel4_IRQHandler
.weak		DMA1_Channel4_IRQHandler
.thumb_set	DMA1_Channel4_IRQHandler,Default_Handler

.word		DMA1_Channel5_IRQHandler
.weak		DMA1_Channel5_IRQHandler
.thumb_set	DMA1_Channel5_IRQHandler,Default_Handler

.word		DMA1_Channel6_IRQHandler
.weak		DMA1_Channel6_IRQHandler
.thumb_set	DMA1_Channel6_IRQHandler,Default_Handler

.word		DMA1_Channel7_IRQHandler
.weak		DMA1_Channel7_IRQHandler
.thumb_set	DMA1_Channel7_IRQHandler,Default_Handler

.word		ADC1_2_IRQHandler
.weak		ADC1_2_IRQHandler
.thumb_set	ADC1_2_IRQHandler,Default_Handler

.word		0
.word		0
.word		0
.word		0

.word		EXTI9_5_IRQHandler
.weak		EXTI9_5_IRQHandler
.thumb_set	EXTI9_5_IRQHandler,Default_Handler

.word		TIM1_BRK_TIM15_IRQHandler
.weak		TIM1_BRK_TIM15_IRQHandler
.thumb_set	TIM1_BRK_TIM15_IRQHandler,Default_Handler

.word		TIM1_UP_TIM16_IRQHandler
.weak		TIM1_UP_TIM16_IRQHandler
.thumb_set	TIM1_UP_TIM16_IRQHandler,Default_Handler

.word		TIM1_TRG_COM_IRQHandler
.weak		TIM1_TRG_COM_IRQHandler
.thumb_set	TIM1_TRG_COM_IRQHandler,Default_Handler

.word		TIM1_CC_IRQHandler
.weak		TIM1_CC_IRQHandler
.thumb_set	TIM1_CC_IRQHandler,Default_Handler

.word		TIM2_IRQHandler
.weak		TIM2_IRQHandler
.thumb_set	TIM2_IRQHandler,Default_Handler

.word		0
.word		0

.word		I2C1_EV_IRQHandler
.weak		I2C1_EV_IRQHandler
.thumb_set	I2C1_EV_IRQHandler,Default_Handler

.word		I2C1_ER_IRQHandler
.weak		I2C1_ER_IRQHandler
.thumb_set	I2C1_ER_IRQHandler,Default_Handler

.word		I2C2_EV_IRQHandler
.weak		I2C2_EV_IRQHandler
.thumb_set	I2C2_EV_IRQHandler,Default_Handler

.word		I2C2_ER_IRQHandler
.weak		I2C2_ER_IRQHandler
.thumb_set	I2C2_ER_IRQHandler,Default_Handler

.word		SPI1_IRQHandler
.weak		SPI1_IRQHandler
.thumb_set	SPI1_IRQHandler,Default_Handler

.word		SPI2_IRQHandler
.weak		SPI2_IRQHandler
.thumb_set	SPI2_IRQHandler,Default_Handler

.word		USART1_IRQHandler
.weak		USART1_IRQHandler
.thumb_set	USART1_IRQHandler,Default_Handler

.word		USART2_IRQHandler
.weak		USART2_IRQHandler
.thumb_set	USART2_IRQHandler,Default_Handler

.word		USART3_IRQHandler
.weak		USART3_IRQHandler
.thumb_set	USART3_IRQHandler,Default_Handler

.word		EXTI15_10_IRQHandler
.weak		EXTI15_10_IRQHandler
.thumb_set	EXTI15_10_IRQHandler,Default_Handler

.word		RTC_Alarm_IRQHandler
.weak		RTC_Alarm_IRQHandler
.thumb_set	RTC_Alarm_IRQHandler,Default_Handler

.word		0
.word		0
.word		0
.word		0
.word		0
.word		0
.word		0
.word		0
.word		0
.word		0
.word		0
.word		0

.word		TIM6_IRQHandler
.weak		TIM6_IRQHandler
.thumb_set	TIM6_IRQHandler,Default_Handler

.word		0

.word		DMA2_Channel1_IRQHandler
.weak		DMA2_Channel1_IRQHandler
.thumb_set	DMA2_Channel1_IRQHandler,Default_Handler

.word		DMA2_Channel2_IRQHandler
.weak		DMA2_Channel2_IRQHandler
.thumb_set	DMA2_Channel2_IRQHandler,Default_Handler

.word		DMA2_Channel3_IRQHandler
.weak		DMA2_Channel3_IRQHandler
.thumb_set	DMA2_Channel3_IRQHandler,Default_Handler

.word		DMA2_Channel4_IRQHandler
.weak		DMA2_Channel4_IRQHandler
.thumb_set	DMA2_Channel4_IRQHandler,Default_Handler

.word		DMA2_Channel5_IRQHandler
.weak		DMA2_Channel5_IRQHandler
.thumb_set	DMA2_Channel5_IRQHandler,Default_Handler

.word		0
.word		0
.word		0

.word		COMP_IRQHandler
.weak		COMP_IRQHandler
.thumb_set	COMP_IRQHandler,Default_Handler

.word		LPTIM1_IRQHandler
.weak		LPTIM1_IRQHandler
.thumb_set	LPTIM1_IRQHandler,Default_Handler

.word		LPTIM2_IRQHandler
.weak		LPTIM2_IRQHandler
.thumb_set	LPTIM2_IRQHandler,Default_Handler

.word		USB_IRQHandler
.weak		USB_IRQHandler
.thumb_set	USB_IRQHandler,Default_Handler

.word		DMA2_Channel6_IRQHandler
.weak		DMA2_Channel6_IRQHandler
.thumb_set	DMA2_Channel6_IRQHandler,Default_Handler

.word		DMA2_Channel7_IRQHandler
.weak		DMA2_Channel7_IRQHandler
.thumb_set	DMA2_Channel7_IRQHandler,Default_Handler

.word		LPUART1_IRQHandler
.weak		LPUART1_IRQHandler
.thumb_set	LPUART1_IRQHandler,Default_Handler

.word		QUADSPI_IRQHandler
.weak		QUADSPI_IRQHandler
.thumb_set	QUADSPI_IRQHandler,Default_Handler

.word		I2C3_EV_IRQHandler
.weak		I2C3_EV_IRQHandler
.thumb_set	I2C3_EV_IRQHandler,Default_Handler

.word		I2C3_ER_IRQHandler
.weak		I2C3_ER_IRQHandler
.thumb_set	I2C3_ER_IRQHandler,Default_Handler

.word		0
.word		0
.word		0

.word		TSC_IRQHandler
.weak		TSC_IRQHandler
.thumb_set	TSC_IRQHandler,Default_Handler

.word		0

.word		AES_IRQHandler
.weak		AES_IRQHandler
.thumb_set	AES_IRQHandler,Default_Handler

.word		RNG_IRQHandler
.weak		RNG_IRQHandler
.thumb_set	RNG_IRQHandler,Default_Handler

.word		FPU_IRQHandler
.weak		FPU_IRQHandler
.thumb_set	FPU_IRQHandler,Default_Handler

.word		CRS_IRQHandler
.weak		CRS_IRQHandler
.thumb_set	CRS_IRQHandler,Default_Handler


.section	.text.default_handler
.weak		Default_Handler
.type		Default_Handler, %function
.thumb_func
Default_Handler:
	ldr		r3, NVIC_INT_CTRL_CONST
	ldr 	r2, [r3, #0]
	uxtb	r2, r2
	b		Infinite_Loop

.align	4
NVIC_INT_CTRL_CONST: .word 0xe000ed04