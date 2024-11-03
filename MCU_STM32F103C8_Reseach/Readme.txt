- MCU_STM32F103C8_Research:	
	+ Configure Clock
		HSE 8MHZ PLL -> AHB 40MHZ -> ABP1 and ABP2 10MHZ
	+ flash led by interrupt timer
		Timer2 (Interrupt 1ms)
	+ USART
		USART1 communicate with Hercules software
		Capable of getting string data
	+ SPI
		SPI1 communicate SPI2
		Capable of getting string data
