#include "function_init.h"

/*-------------------------- Clock -------------------------------------*/
void INIT_Clock(void){
	/*----- Configure RCC -- using cube software to see configure and compare with clock tree ---------*/
	RCC_DeInit();	//Reset RCC
	
	RCC_HSEConfig(RCC_HSE_ON); //Using HSE ---- (8MHZ)
	while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == 0);	//wait HSE ready (RCC_FLAG_HSERDY == 1)
	while (RCC_WaitForHSEStartUp() == 0){};	//wait configure HSE inform not error
	
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_5);	//Using HSE_Div1 and PLL_Mul_5 ---- (40MHZ)
	RCC_PLLCmd(ENABLE);
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == 0)		//wait PLL ready (RCC_FLAG_HSERDY == 1)
		
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);	//Choose SysClk is PLL
	RCC_HCLKConfig(RCC_SYSCLK_Div1);	//Choose AHB prescale is Div1 ---- (40MHZ)
	
	RCC_PCLK1Config(RCC_HCLK_Div4); //Choose ABP1 prescale is Div4 ---- (10MHZ) <=> Timer 2,3,4 = 20MHZ
	RCC_PCLK2Config(RCC_HCLK_Div4); //Choose ABP2 prescale is Div4 ---- (10MHZ) <=> Timer 1 = 20MHZ
}


/*-------------------------- GPIO_C_BlinkLed -------------------------------------*/
void INIT_GPIOLed(void){
	/*---------------------- configure GPIOC --------------------------*/
	GPIO_InitTypeDef init_GPIOx;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//Enable RCC for Port C
	/* Init GPIO PC13 is output PP */
	init_GPIOx.GPIO_Mode = GPIO_Mode_Out_PP;
	init_GPIOx.GPIO_Pin = GPIO_Pin_13;
	init_GPIOx.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &init_GPIOx);
}


/*-------------------------- Timer_2 -------------------------------------*/
void INIT_Timer2(void){
	/*------------------- Configure Timer ------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//Enable RCC for Timer 2
	
	/* Configure Interrupt for Timer 2 */
	NVIC_InitTypeDef init_NVIC_TIMx;
	init_NVIC_TIMx.NVIC_IRQChannel = TIM2_IRQn;	//Choose Interrupt of Timer 2 to do object
	init_NVIC_TIMx.NVIC_IRQChannelPreemptionPriority = 0;	//main Priority
	init_NVIC_TIMx.NVIC_IRQChannelSubPriority = 0;	//sub Priority
	init_NVIC_TIMx.NVIC_IRQChannelCmd = ENABLE;	//Enable
	NVIC_Init(&init_NVIC_TIMx);	//Init NVIC for Timer 2 with above specifications
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	/* Init TIMER 2 */
	TIM_TimeBaseInitTypeDef init_TIMx;
	init_TIMx.TIM_CounterMode = TIM_CounterMode_Up;	//Choose timer Counter Up (from 0 to set value)
	init_TIMx.TIM_Prescaler = 20 - 1; //	don't need to use prescale is OK
	init_TIMx.TIM_Period = 1000; // ~1ms because CLK_TIM1 = 20MHZ
	TIM_TimeBaseInit(TIM2, &init_TIMx);	//Init Timer 2 with above specifications
	TIM_Cmd(TIM2, ENABLE);	//Enable Timer 2
}


/*-------------------------- USART_1 -------------------------------------*/
void INIT_USART1(void){
	/*---------------------- configure GPIOA --------------------------*/
	GPIO_InitTypeDef init_GPIOx;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//Enable RCC for Port A
	/* Init GPIO PA9 is USART_1 Tx */
	init_GPIOx.GPIO_Pin = GPIO_Pin_9;
	init_GPIOx.GPIO_Mode = GPIO_Mode_AF_PP;
	init_GPIOx.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &init_GPIOx);
	/* Init GPIO PA10 is USART_1 Rx  */
	init_GPIOx.GPIO_Pin = GPIO_Pin_10;
	init_GPIOx.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	init_GPIOx.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &init_GPIOx);
	
	
	/*-------------------- Init UsART ---------------------------*/
	USART_DeInit(USART1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//Enable RCC for USART_1
	
	/* Configure Interrupt for USART_1 */
	NVIC_InitTypeDef init_NVIC_UARTx;
	init_NVIC_UARTx.NVIC_IRQChannel = USART1_IRQn;	//Choose Interrupt of USART_1 to do object
	init_NVIC_UARTx.NVIC_IRQChannelPreemptionPriority = 0;	//main Priority
	init_NVIC_UARTx.NVIC_IRQChannelSubPriority = 0;	//sub Priority
	init_NVIC_UARTx.NVIC_IRQChannelCmd = ENABLE;	//Enable
	NVIC_Init(&init_NVIC_UARTx);	//Init NVIC for USART_1 with above specifications
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	/* Init USART_1 */
	USART_InitTypeDef init_USARTx;
	init_USARTx.USART_BaudRate = 9600;
	init_USARTx.USART_WordLength = USART_WordLength_8b;
	init_USARTx.USART_Parity = USART_Parity_No;
	init_USARTx.USART_StopBits = USART_StopBits_1;
	init_USARTx.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
	init_USARTx.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &init_USARTx);
	USART_Cmd(USART1, ENABLE);
}

/*-------------------------- SPI_1 _ Master -------------------------------------*/
void INIT_SPI1(void){
	/*---------------------- configure GPIOA --------------------------*/
	GPIO_InitTypeDef init_GPIOx;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//Enable RCC for Port A
	/* Init GPIO PA4 is SPI_1 NSS */
	init_GPIOx.GPIO_Pin = GPIO_Pin_4;
	init_GPIOx.GPIO_Mode = GPIO_Mode_Out_PP;
	init_GPIOx.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &init_GPIOx);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	/* Init GPIO PA5 is SPI_1 SCK */
	init_GPIOx.GPIO_Pin = GPIO_Pin_5;
	init_GPIOx.GPIO_Mode = GPIO_Mode_AF_PP;
	init_GPIOx.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &init_GPIOx);
	/* Init GPIO PA6 is SPI_1 MISO */
	init_GPIOx.GPIO_Pin = GPIO_Pin_6;
	init_GPIOx.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	init_GPIOx.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &init_GPIOx);
	/* Init GPIO PA7 is SPI_1 MOSI */
	init_GPIOx.GPIO_Pin = GPIO_Pin_7;
	init_GPIOx.GPIO_Mode = GPIO_Mode_AF_PP;
	init_GPIOx.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &init_GPIOx);
	
	/*------------------------ Init SPI -------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	//Enable RCC for SPI1
	
	/* Configure Interrupt for SPI_1 */
//	NVIC_InitTypeDef init_NVIC_SPIx;
//	init_NVIC_SPIx.NVIC_IRQChannel = SPI1_IRQn;	//Choose Interrupt of SPI_1 to do object
//	init_NVIC_SPIx.NVIC_IRQChannelPreemptionPriority = 0;	//main Priority
//	init_NVIC_SPIx.NVIC_IRQChannelSubPriority = 0;	//sub Priority
//	init_NVIC_SPIx.NVIC_IRQChannelCmd = ENABLE;	//Enable
//	NVIC_Init(&init_NVIC_SPIx);	//Init NVIC for 1 with above specifications
//	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, DISABLE);
	
	SPI_InitTypeDef init_SPIx;
	init_SPIx.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	init_SPIx.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	init_SPIx.SPI_CPHA = SPI_CPHA_2Edge;
	init_SPIx.SPI_CPOL = SPI_CPOL_Low;
	init_SPIx.SPI_DataSize = SPI_DataSize_8b;
	init_SPIx.SPI_FirstBit = SPI_FirstBit_MSB;
	init_SPIx.SPI_Mode = SPI_Mode_Master;
	init_SPIx.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1, &init_SPIx);
	
	SPI_Cmd(SPI1, ENABLE);
}


/*-------------------------- SPI_2 _ Slave -------------------------------------*/
void INIT_SPI2(void){
	/*---------------------- configure GPIOB --------------------------*/
	GPIO_InitTypeDef init_GPIOx;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//Enable RCC for Port B
	/* Init GPIO PB12 is SPI_2 NSS */
	init_GPIOx.GPIO_Pin = GPIO_Pin_12;
	init_GPIOx.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	init_GPIOx.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &init_GPIOx);
	/* Init GPIO PB13 is SPI_2 SCK */
	init_GPIOx.GPIO_Pin = GPIO_Pin_13;
	init_GPIOx.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	init_GPIOx.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &init_GPIOx);
	/* Init GPIO PB14 is SPI_2 MISO */
	init_GPIOx.GPIO_Pin = GPIO_Pin_14;
	init_GPIOx.GPIO_Mode = GPIO_Mode_AF_PP;
	init_GPIOx.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &init_GPIOx);
	/* Init GPIO PB15 is SPI_2 MOSI */
	init_GPIOx.GPIO_Pin = GPIO_Pin_15;
	init_GPIOx.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	init_GPIOx.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &init_GPIOx);
	
	/*------------------------ Init SPI -------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);	//Enable RCC for SPI2
	
	/* Configure Interrupt for SPI_2 */
	NVIC_InitTypeDef init_NVIC_SPIx;
	init_NVIC_SPIx.NVIC_IRQChannel = SPI2_IRQn;	//Choose Interrupt of SPI_2 to do object
	init_NVIC_SPIx.NVIC_IRQChannelPreemptionPriority = 0;	//main Priority
	init_NVIC_SPIx.NVIC_IRQChannelSubPriority = 0;	//sub Priority
	init_NVIC_SPIx.NVIC_IRQChannelCmd = ENABLE;	//Enable
	NVIC_Init(&init_NVIC_SPIx);	//Init NVIC for SPI_2 with above specifications
	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);
//	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, DISABLE);
	
	SPI_InitTypeDef init_SPIx;
	init_SPIx.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	init_SPIx.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	init_SPIx.SPI_CPHA = SPI_CPHA_2Edge;
	init_SPIx.SPI_CPOL = SPI_CPOL_Low;
	init_SPIx.SPI_DataSize = SPI_DataSize_8b;
	init_SPIx.SPI_FirstBit = SPI_FirstBit_MSB;
	init_SPIx.SPI_Mode = SPI_Mode_Slave;
	init_SPIx.SPI_NSS = SPI_NSS_Hard;
	SPI_Init(SPI2, &init_SPIx);
	
	SPI_Cmd(SPI2, ENABLE);
}
