This project acquires data from an accelerometer at 4 kHz and transfers the data to PC through USB cable. 
  
Hardware platform: 
1. STM32F103C8
2. mpu9250 or mpu6500 (SPI interface)
  
To compile and debug this project, please have the software listed below installed. 
1. Keil 5 for ARM
2. CUBE MX (optional)
3. Driver for Jlink2
4. Driver for STM virtual COM port (windows version only)
You can easily migrate this project on other 32bit MCUs from ST with USB and SPI interface, or develop this project using other tool chains.