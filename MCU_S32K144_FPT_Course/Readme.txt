MOCK_C_Module:
	Read data from a CSV file and based on a template text file to generate a header file serving for S32K144 registers such as GPIO, Interrupt, Clock, Timer, UART, SPI...


-------------------------------------------------------------------
BT_Overview:
	GPIO--------------------------------------
		1. Viết chương trình thỏa mãn yêu cầu sau:
			Khi nhấn nút nhấn tại PTC12 thì đèn PTD16 sáng. Khi nhả nút nhấn PTC12 thì đèn PTD16 tắt.

		2. Viết chương trình thỏa mãn yêu cầu sau:
			Khi nhấn nút nhấn tại PTC12  thì đèn PTD0 sáng. 
			Khi nhấn nút nhấn tại PTC13 thì đèn PTD0 tắt. 

		3. Viết chương trình thỏa mãn yêu cầu sau:
			Khi nhấn nút nhấn tại PTC12 lần đầu thì đèn PTD15 sáng. Khi nhấn nút nhấn tại PTC12 lần nữa thì đèn PTD15 tắt.

		4. Viết chương trình thỏa mãn yêu cầu sau:
			Khi nhấn nút nhấn tại PTC12  thì đèn PTD16 nhấp nháy với tần số  khoảng 5s (Không cần đúng chính xác 5s, tương đối là được). 
			Khi nhấn nút nhấn tại PTC13 thì đèn PTD16 dừng nhấp nháy và sáng luôn.


	Clock-------------------------------------------
		Viết chương trình Blink led với tần số sáng 500ms, tắt 500ms với các trường hợp sau:
			ex1: Dùng Clock ngoài từ thạch anh 8Mhz, tạo ra clock core tần số 80Mhz, bus clock 40Mhz
			ex2: Dùng Clock ngoài từ thạch anh 8Mhz, tạo ra clock core tần số 8Mhz, bus clock 4Mhz
			ex3: Dùng Clock ngoài từ thạch anh 8Mhz, tạo ra clock core tần số 48Mhz, bus clock 16Mhz
			ex4: Dùng Clock bên trong chip FIRC 48Mhz, tạo ra clock core tần số 24Mhz
			ex5: Dùng Clock bên trong chip SIRC 8Mhz, tạo ra clock core tần số 8Mhz,


	System Tick Timer-------------------------------
		ex1: Viết chương trình chớp tắt led PTD16 với thời gian sáng là 500ms và tắt là 500ms. Sử dụng system tick timer, không dùng interrupt của system tick timer
		ex2: Viết chương trình chớp tắt led PTD16 với thời gian sáng là 500ms và tắt là 500ms. Sử dụng system tick timer,  có interrupt của system tick timer
		ex3: Viết chương trình chớp tắt led PTD16 với thời gian sáng là 2s và tắt là 1s. Sử dụng system tick timer, không dùng interrupt của system tick timer
		ex4: Viết chương trình chớp tắt led PTD16 với thời gian sáng là 1s  và tắt là 2s. Sử dụng system tick timer,  có interrupt của system tick timer
		ex5: Tính thời gian thực thi vòng lặp for sau:
			volatile int i = 0;
			for( i = 0; i <250; i++);


	Timer--------------------------------------------
		Dùng Clock ngoài từ thạch anh 8Mhz, tạo ra clock core tần số 80Mhz, bus clock 40Mhz, Flash clock 26.67Mhz
		Viết chương trình Blink led với chu kỳ sáng TON ms, tắt TOFF ms sử dụng timer channel X với các trường hợp sau:
			ex1: TON = 500 ms, TOFF = 500 ms, Dùng Timer Channel 0, Mode 32 bits
			ex2: TON = 250 ms, TOFF = 750 ms, Dùng Timer Channel 1, Mode 32 bits
			ex3: TON = 2 s, TOFF = 1.5 s, Dùng Timer Channel 2, Mode 32 bits
			ex4: TON = 1.5 s, TOFF = 0.5 s, Dùng Timer Channel 3, Mode 32 bits
			ex5: TON = 1s, TOFF = 1s, Dùng Timer Channel 0, Mode Dual 16 bits
			ex6: TON = 3s, TOFF = 3s, Dùng Timer Channel 1, Mode 32 bits, Chain mode

---------------------------------------------------------
ASM1_GPIO_(Use Interrupt)

---------------------------------------------------------
ASM2_UART
	Write a program: Sum of two large numbers follow 4 SRS (Software Requirement Specification)
		SRS 1: Clock core 48MHz from clock source crystal 8MHz
		SRS 2: Setting for LPUART1.
			Baud rate: 19200, 8 bit data, odd parity, 1 bit stop.
		SRS 3:
			SRS 3-1: After power up, the terminal display:
				“[YourFullName] – UART Mini Project”
				“Enter expression with format [Operand 1 + Operand 2 =]”
			SRS 3-2: Format send: 
				Characters used: 0→9, ‘=’, ‘+’
		SRS 4: Response message
			SRS 4-1: if the format send is correct, the response is the result
			SRS 4-2: else the response is ”Wrong format\r\n”

--------------------------------------------------------------------------------------
MOCK_Final
	SRS 1: Clock core 72MHz from clock source crystal 8MHz
	SRS 2: Setting for LPUART1. Pin PTC6, Pin PTC7
		SRS 2-1: Baud rate: 38400, 8-bits data, even parity, 1-bit stop.
		SRS 2-2: UART clock is SPLL Div2
	SRS 3: Setting for SPI using Pin 0, Pin E1, Pin E2, Pin E6
	SRS 4: After power on, display the time: 18-00-00 (date: 01.01.1991), the LED Green status is OFF
	SRS 5: Setting date, time, alarm by UART1 serial communication.
	SRS 6: Select mode display via the button
		Press Button 1
			SRS 6-1: Display the date
			SRS 6-2: Display the time
		Press Button 2
			Decrease bright of LED 7 SEG which 5 level from maximum to off the Led
	SRS 7: When alarm occurred, the LED Green blink with period 0.5 (s) in alarm time 10 (s).
		In alarm time, if pressed any button, the LED Green is OFF immediately.
















