EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:General
LIBS:stm32
LIBS:infineon
LIBS:LaserBodyRoll-cache
EELAYER 26 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 3 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L FTSH-105-01-L-DV-K J2
U 1 1 59E96382
P 1700 1200
F 0 "J2" H 1725 1647 60  0000 C CNN
F 1 "FTSH-105-01-L-DV-K" H 1725 1541 60  0000 C CNN
F 2 "KicadFootprint:FTSH-105-01-L-DV-K" H 1850 1200 60  0001 C CNN
F 3 "" H 1850 1200 60  0001 C CNN
F 4 "SAM8799-ND" H 1700 1200 60  0001 C CNN "Digikey"
	1    1700 1200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 59E96769
P 1250 1500
F 0 "#PWR08" H 1250 1250 50  0001 C CNN
F 1 "GND" H 1255 1327 50  0000 C CNN
F 2 "" H 1250 1500 50  0001 C CNN
F 3 "" H 1250 1500 50  0001 C CNN
	1    1250 1500
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR07
U 1 1 5A80F440
P 1150 850
F 0 "#PWR07" H 1150 700 50  0001 C CNN
F 1 "VCC" H 1167 1023 50  0000 C CNN
F 2 "" H 1150 850 50  0001 C CNN
F 3 "" H 1150 850 50  0001 C CNN
	1    1150 850 
	1    0    0    -1  
$EndComp
Text Label 2200 1400 0    60   ~ 0
STM_RES
NoConn ~ 2150 1200
$Comp
L Test_Point TP1
U 1 1 5A122F3D
P 2500 1400
F 0 "TP1" H 2558 1520 50  0000 L CNN
F 1 "Test_Point" H 2558 1429 50  0000 L CNN
F 2 "Connectors_TestPoints:Test_Point_Pad_d2.0mm" H 2700 1400 50  0001 C CNN
F 3 "" H 2700 1400 50  0001 C CNN
	1    2500 1400
	-1   0    0    1   
$EndComp
Text Label 550  1100 0    60   ~ 0
STM_SWDIO
Text Label 550  1300 0    60   ~ 0
STM_SWDCLK
Text Label 2250 1000 0    60   ~ 0
SWDV
$Comp
L GND #PWR09
U 1 1 5A80F442
P 2700 1500
F 0 "#PWR09" H 2700 1250 50  0001 C CNN
F 1 "GND" H 2705 1327 50  0000 C CNN
F 2 "" H 2700 1500 50  0001 C CNN
F 3 "" H 2700 1500 50  0001 C CNN
	1    2700 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1000 1150 1000
Wire Wire Line
	1150 1000 1150 850 
Wire Wire Line
	550  1100 1300 1100
Wire Wire Line
	550  1300 1300 1300
Wire Wire Line
	2150 1000 2650 1000
Wire Wire Line
	2150 1400 2500 1400
Wire Wire Line
	2150 1100 2700 1100
Wire Wire Line
	2700 1100 2700 1500
Wire Wire Line
	2150 1300 2700 1300
Connection ~ 2700 1300
Text GLabel 1850 5800 0    60   Input ~ 0
SCL
Text GLabel 1850 6000 0    60   Input ~ 0
SDA
Text GLabel 1800 7050 0    60   Input ~ 0
FLASH_SCLK
Text GLabel 1800 6750 0    60   Input ~ 0
FLASH_MOSI
Text GLabel 1800 6650 0    60   Input ~ 0
FLASH_MISO
Text GLabel 1800 6550 0    60   Input ~ 0
FLASH_CS
Text GLabel 1600 8650 0    60   Input ~ 0
IMU_INT
Text GLabel 1600 8100 0    60   Input ~ 0
IMU_CS
Text GLabel 1600 8000 0    60   Input ~ 0
IMU_MISO
Text GLabel 1600 7900 0    60   Input ~ 0
IMU_MOSI
Text GLabel 1600 7800 0    60   Input ~ 0
IMU_SCLK
Text GLabel 1750 5250 0    60   Input ~ 0
BLUE
Text GLabel 1750 5050 0    60   Input ~ 0
GREEN
Text GLabel 1750 4850 0    60   Input ~ 0
RED
Text GLabel 1950 4000 0    60   Input ~ 0
BLE_SCLK
Text GLabel 1950 3900 0    60   Input ~ 0
BLE_CS
Text GLabel 1950 3800 0    60   Input ~ 0
BLE_MISO
Text GLabel 1950 3700 0    60   Input ~ 0
BLE_MOSI
Text Label 1750 5250 0    60   ~ 0
BLUE
Text Label 1750 5050 0    60   ~ 0
GREEN
Text Label 1750 4850 0    60   ~ 0
RED
$Comp
L STM32F303RETx U3
U 1 1 5A8095C8
P 8050 5250
F 0 "U3" H 7836 7428 50  0000 C CNN
F 1 "STM32F303RETx" H 7836 7337 50  0000 C CNN
F 2 "LQFP64" H 13150 7125 50  0001 R TNN
F 3 "" H 8050 5250 50  0001 C CNN
	1    8050 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1200 1250 1200
Wire Wire Line
	1250 1200 1250 1500
Wire Wire Line
	1300 1400 1250 1400
Connection ~ 1250 1400
$EndSCHEMATC
