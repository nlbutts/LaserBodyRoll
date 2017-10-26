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
LIBS:LaserBodyRoll-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
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
L CY8C4A25LQI-473 U2
U 1 1 59E95B73
P 2350 3550
F 0 "U2" H 2350 4937 60  0000 C CNN
F 1 "CY8C4A25LQI-473" H 2350 4831 60  0000 C CNN
F 2 "" H 2350 3550 60  0001 C CNN
F 3 "" H 2350 3550 60  0001 C CNN
	1    2350 3550
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 59E95C3F
P 4450 5350
F 0 "C10" H 4565 5396 50  0000 L CNN
F 1 "0.1u" H 4565 5305 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4488 5200 50  0001 C CNN
F 3 "" H 4450 5350 50  0001 C CNN
	1    4450 5350
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 59E95FD6
P 3650 5350
F 0 "C2" H 3765 5396 50  0000 L CNN
F 1 "0.1u" H 3765 5305 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3688 5200 50  0001 C CNN
F 3 "" H 3650 5350 50  0001 C CNN
	1    3650 5350
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 59E96031
P 4050 5350
F 0 "C9" H 4165 5396 50  0000 L CNN
F 1 "1u" H 4165 5305 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4088 5200 50  0001 C CNN
F 3 "" H 4050 5350 50  0001 C CNN
	1    4050 5350
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 59E96161
P 4050 4450
F 0 "C3" H 4165 4496 50  0000 L CNN
F 1 "1u" H 4165 4405 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4088 4300 50  0001 C CNN
F 3 "" H 4050 4450 50  0001 C CNN
	1    4050 4450
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 59E96183
P 3650 4450
F 0 "C1" H 3765 4496 50  0000 L CNN
F 1 "0.1u" H 3765 4405 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 3688 4300 50  0001 C CNN
F 3 "" H 3650 4450 50  0001 C CNN
	1    3650 4450
	1    0    0    -1  
$EndComp
$Comp
L FTSH-105-01-L-DV-K J2
U 1 1 59E96382
P 1550 1350
F 0 "J2" H 1575 1797 60  0000 C CNN
F 1 "FTSH-105-01-L-DV-K" H 1575 1691 60  0000 C CNN
F 2 "KicadFootprint:FTSH-105-01-L-DV-K" H 1700 1350 60  0001 C CNN
F 3 "" H 1700 1350 60  0001 C CNN
	1    1550 1350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 59E96769
P 1000 1600
F 0 "#PWR09" H 1000 1350 50  0001 C CNN
F 1 "GND" H 1005 1427 50  0000 C CNN
F 2 "" H 1000 1600 50  0001 C CNN
F 3 "" H 1000 1600 50  0001 C CNN
	1    1000 1600
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR012
U 1 1 59E9676F
P 1000 1000
F 0 "#PWR012" H 1000 850 50  0001 C CNN
F 1 "VCC" H 1017 1173 50  0000 C CNN
F 2 "" H 1000 1000 50  0001 C CNN
F 3 "" H 1000 1000 50  0001 C CNN
	1    1000 1000
	1    0    0    -1  
$EndComp
Text Label 3400 2450 0    60   ~ 0
SWDIO
Text Label 3400 2550 0    60   ~ 0
SWDCLK
Text Label 3400 2650 0    60   ~ 0
XRES
Text Label 2050 1150 0    60   ~ 0
SWDIO
Text Label 2050 1250 0    60   ~ 0
SWDCLK
Text Label 2050 1550 0    60   ~ 0
XRES
$Comp
L VL53L0X U6
U 1 1 59EDA2BE
P 9650 1750
F 0 "U6" H 9650 2337 60  0000 C CNN
F 1 "VL53L0X" H 9650 2231 60  0000 C CNN
F 2 "KicadFootprint:VL53L0x" H 9650 1750 60  0001 C CNN
F 3 "" H 9650 1750 60  0001 C CNN
	1    9650 1750
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR035
U 1 1 59EDA32E
P 10550 1350
F 0 "#PWR035" H 10550 1200 50  0001 C CNN
F 1 "VCC" H 10567 1523 50  0000 C CNN
F 2 "" H 10550 1350 50  0001 C CNN
F 3 "" H 10550 1350 50  0001 C CNN
	1    10550 1350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR036
U 1 1 59EDA4F5
P 10550 2450
F 0 "#PWR036" H 10550 2200 50  0001 C CNN
F 1 "GND" H 10555 2277 50  0000 C CNN
F 2 "" H 10550 2450 50  0001 C CNN
F 3 "" H 10550 2450 50  0001 C CNN
	1    10550 2450
	1    0    0    -1  
$EndComp
$Comp
L C C19
U 1 1 59EDA84B
P 10550 1750
F 0 "C19" H 10665 1796 50  0000 L CNN
F 1 "100n" H 10665 1705 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 10588 1600 50  0001 C CNN
F 3 "" H 10550 1750 50  0001 C CNN
	1    10550 1750
	1    0    0    -1  
$EndComp
$Comp
L C C21
U 1 1 59EDA8CB
P 10950 1750
F 0 "C21" H 11065 1796 50  0000 L CNN
F 1 "4.7u" H 11065 1705 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 10988 1600 50  0001 C CNN
F 3 "" H 10950 1750 50  0001 C CNN
	1    10950 1750
	1    0    0    -1  
$EndComp
$Comp
L R R32
U 1 1 59EDADB4
P 7500 1050
F 0 "R32" H 7570 1096 50  0000 L CNN
F 1 "1.7k" H 7570 1005 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 7430 1050 50  0001 C CNN
F 3 "" H 7500 1050 50  0001 C CNN
	1    7500 1050
	1    0    0    -1  
$EndComp
$Comp
L R R31
U 1 1 59EDAE39
P 7150 1050
F 0 "R31" H 7220 1096 50  0000 L CNN
F 1 "1.7k" H 7220 1005 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 7080 1050 50  0001 C CNN
F 3 "" H 7150 1050 50  0001 C CNN
	1    7150 1050
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR028
U 1 1 59EDAFFC
P 7350 700
F 0 "#PWR028" H 7350 550 50  0001 C CNN
F 1 "VCC" H 7367 873 50  0000 C CNN
F 2 "" H 7350 700 50  0001 C CNN
F 3 "" H 7350 700 50  0001 C CNN
	1    7350 700 
	1    0    0    -1  
$EndComp
Text Label 8800 1450 0    60   ~ 0
SDA
Text Label 8800 1550 0    60   ~ 0
SCL
Text Label 8550 2050 0    60   ~ 0
VL53L0X_GP
Text Label 8300 2150 0    60   ~ 0
VL53L0X_XSHUT
$Comp
L STLM75 U7
U 1 1 59EDBBE1
P 9750 3600
F 0 "U7" H 9750 4137 60  0000 C CNN
F 1 "STLM75" H 9750 4031 60  0000 C CNN
F 2 "Housings_SSOP:TSSOP-8_3x3mm_Pitch0.65mm" H 9750 3600 60  0001 C CNN
F 3 "" H 9750 3600 60  0001 C CNN
	1    9750 3600
	1    0    0    -1  
$EndComp
$Comp
L C C17
U 1 1 59EDC48E
P 10400 3550
F 0 "C17" H 10515 3596 50  0000 L CNN
F 1 "0.1u" H 10515 3505 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 10438 3400 50  0001 C CNN
F 3 "" H 10400 3550 50  0001 C CNN
	1    10400 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 5050 3650 5050
Wire Wire Line
	3350 4950 4450 4950
Wire Wire Line
	4450 4950 4450 5200
Wire Wire Line
	3650 5050 3650 5200
Wire Wire Line
	3350 5150 3500 5150
Wire Wire Line
	3500 5150 3500 5700
Wire Wire Line
	4450 5550 4450 5500
Wire Wire Line
	3500 5550 4450 5550
Connection ~ 3500 5550
Wire Wire Line
	3650 5500 3650 5550
Connection ~ 3650 5550
Wire Wire Line
	4050 5500 4050 5550
Connection ~ 4050 5550
Wire Wire Line
	3350 4250 4050 4250
Wire Wire Line
	4050 4250 4050 4300
Wire Wire Line
	3650 4300 3650 4250
Connection ~ 3650 4250
Wire Wire Line
	3350 4350 3450 4350
Wire Wire Line
	3450 4250 3450 4450
Connection ~ 3450 4250
Wire Wire Line
	3450 4450 3350 4450
Connection ~ 3450 4350
Wire Wire Line
	3350 4750 4050 4750
Wire Wire Line
	4050 4750 4050 4600
Wire Wire Line
	3650 4600 3650 4750
Connection ~ 3650 4750
Wire Wire Line
	3350 4650 3450 4650
Wire Wire Line
	3450 4550 3450 4750
Connection ~ 3450 4750
Wire Wire Line
	3350 4550 3450 4550
Connection ~ 3450 4650
Wire Wire Line
	1150 1150 1000 1150
Wire Wire Line
	1000 1150 1000 1000
Wire Wire Line
	1000 1550 1150 1550
Wire Wire Line
	1000 1250 1000 1600
Wire Wire Line
	1150 1250 1000 1250
Connection ~ 1000 1550
Wire Wire Line
	1150 1350 1000 1350
Connection ~ 1000 1350
Wire Wire Line
	1150 1450 1000 1450
Connection ~ 1000 1450
Wire Wire Line
	3350 2450 4050 2450
Wire Wire Line
	3350 2550 4050 2550
Wire Wire Line
	3350 2650 4050 2650
Wire Wire Line
	2000 1150 2500 1150
Wire Wire Line
	2000 1250 2500 1250
Wire Wire Line
	2000 1550 2500 1550
Wire Wire Line
	10300 1450 10550 1450
Wire Wire Line
	10550 1350 10550 1600
Wire Wire Line
	10300 1550 10950 1550
Connection ~ 10550 1450
Wire Wire Line
	10300 1950 10950 1950
Wire Wire Line
	10550 1900 10550 2450
Wire Wire Line
	10300 2050 10550 2050
Connection ~ 10550 2050
Wire Wire Line
	10300 2150 10550 2150
Connection ~ 10550 2150
Wire Wire Line
	10300 2250 10550 2250
Connection ~ 10550 2250
Wire Wire Line
	10300 2350 10550 2350
Connection ~ 10550 2350
Connection ~ 10550 1550
Connection ~ 10550 1950
Wire Wire Line
	10950 1950 10950 1900
Wire Wire Line
	10950 1550 10950 1600
Wire Wire Line
	8800 1550 9000 1550
Wire Wire Line
	7150 700  7500 700 
Wire Wire Line
	7150 700  7150 900 
Wire Wire Line
	7500 700  7500 900 
Connection ~ 7350 700 
Wire Wire Line
	9000 2050 8550 2050
Wire Wire Line
	8250 2150 9000 2150
Wire Wire Line
	10100 3350 10400 3350
Wire Wire Line
	10400 3250 10400 3400
Wire Wire Line
	10100 3850 10400 3850
Wire Wire Line
	10400 3700 10400 3950
Wire Wire Line
	9400 3350 9100 3350
Wire Wire Line
	9400 3450 9100 3450
$Comp
L GND #PWR034
U 1 1 59EDC76C
P 10400 3950
F 0 "#PWR034" H 10400 3700 50  0001 C CNN
F 1 "GND" H 10405 3777 50  0000 C CNN
F 2 "" H 10400 3950 50  0001 C CNN
F 3 "" H 10400 3950 50  0001 C CNN
	1    10400 3950
	1    0    0    -1  
$EndComp
Connection ~ 10400 3850
$Comp
L VCC #PWR033
U 1 1 59EDCA19
P 10400 3250
F 0 "#PWR033" H 10400 3100 50  0001 C CNN
F 1 "VCC" H 10417 3423 50  0000 C CNN
F 2 "" H 10400 3250 50  0001 C CNN
F 3 "" H 10400 3250 50  0001 C CNN
	1    10400 3250
	1    0    0    -1  
$EndComp
Connection ~ 10400 3350
Text Label 9150 3350 0    60   ~ 0
SDA
Text Label 9150 3450 0    60   ~ 0
SCL
Text Notes 9250 2550 0    60   ~ 0
I2C address 0x29
$Comp
L R R33
U 1 1 59EDCFC4
P 8250 1800
F 0 "R33" H 8320 1846 50  0000 L CNN
F 1 "10k" H 8320 1755 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 8180 1800 50  0001 C CNN
F 3 "" H 8250 1800 50  0001 C CNN
	1    8250 1800
	1    0    0    -1  
$EndComp
$Comp
L R R34
U 1 1 59EDD002
P 8550 1800
F 0 "R34" H 8620 1846 50  0000 L CNN
F 1 "10k" H 8620 1755 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 8480 1800 50  0001 C CNN
F 3 "" H 8550 1800 50  0001 C CNN
	1    8550 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 2050 8550 1950
$Comp
L VCC #PWR030
U 1 1 59EDD281
P 8350 1500
F 0 "#PWR030" H 8350 1350 50  0001 C CNN
F 1 "VCC" H 8367 1673 50  0000 C CNN
F 2 "" H 8350 1500 50  0001 C CNN
F 3 "" H 8350 1500 50  0001 C CNN
	1    8350 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 1500 8550 1500
Wire Wire Line
	8250 1500 8250 1650
Wire Wire Line
	8550 1500 8550 1650
Connection ~ 8350 1500
$Comp
L R R35
U 1 1 59EDD7ED
P 8750 3400
F 0 "R35" H 8820 3446 50  0000 L CNN
F 1 "10k" H 8820 3355 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" V 8680 3400 50  0001 C CNN
F 3 "" H 8750 3400 50  0001 C CNN
	1    8750 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 3550 8750 3550
$Comp
L VCC #PWR031
U 1 1 59EDD981
P 8750 3150
F 0 "#PWR031" H 8750 3000 50  0001 C CNN
F 1 "VCC" H 8767 3323 50  0000 C CNN
F 2 "" H 8750 3150 50  0001 C CNN
F 3 "" H 8750 3150 50  0001 C CNN
	1    8750 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 3150 8750 3250
Text Label 8950 3550 0    60   ~ 0
TEMP_INT
Text Notes 9350 4050 0    60   ~ 0
I2C address 0x48
$Comp
L GND #PWR032
U 1 1 59EDDA91
P 9150 3950
F 0 "#PWR032" H 9150 3700 50  0001 C CNN
F 1 "GND" H 9155 3777 50  0000 C CNN
F 2 "" H 9150 3950 50  0001 C CNN
F 3 "" H 9150 3950 50  0001 C CNN
	1    9150 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 3650 9150 3650
Wire Wire Line
	9150 3650 9150 3950
Wire Wire Line
	9400 3750 9150 3750
Connection ~ 9150 3750
Wire Wire Line
	9400 3850 9150 3850
Connection ~ 9150 3850
Text Notes 8700 6350 0    60   ~ 0
I2C address 0x6A\nPlace orientation on silkscreen\n
$Comp
L C C18
U 1 1 59EDE1D3
P 10600 5150
F 0 "C18" H 10715 5196 50  0000 L CNN
F 1 "2.2U" H 10715 5105 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 10638 5000 50  0001 C CNN
F 3 "" H 10600 5150 50  0001 C CNN
	1    10600 5150
	1    0    0    -1  
$EndComp
$Comp
L C C20
U 1 1 59EDE225
P 10900 5450
F 0 "C20" H 11015 5496 50  0000 L CNN
F 1 "10N" H 11015 5405 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 10938 5300 50  0001 C CNN
F 3 "" H 10900 5450 50  0001 C CNN
	1    10900 5450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR038
U 1 1 59EDE4E9
P 10900 6100
F 0 "#PWR038" H 10900 5850 50  0001 C CNN
F 1 "GND" H 10905 5927 50  0000 C CNN
F 2 "" H 10900 6100 50  0001 C CNN
F 3 "" H 10900 6100 50  0001 C CNN
	1    10900 6100
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR037
U 1 1 59EDE51C
P 10900 4750
F 0 "#PWR037" H 10900 4600 50  0001 C CNN
F 1 "VCC" H 10917 4923 50  0000 C CNN
F 2 "" H 10900 4750 50  0001 C CNN
F 3 "" H 10900 4750 50  0001 C CNN
	1    10900 4750
	1    0    0    -1  
$EndComp
$Comp
L Raspberry_Pi_2_3 J8
U 1 1 59EDF50F
P 6800 3850
F 0 "J8" H 6800 5328 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 6800 5237 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x20" H 7800 5100 50  0001 C CNN
F 3 "" H 6850 3700 50  0001 C CNN
	1    6800 3850
	1    0    0    -1  
$EndComp
$Comp
L C C16
U 1 1 59EFD05C
P 800 4350
F 0 "C16" H 915 4396 50  0000 L CNN
F 1 "1u" H 915 4305 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 838 4200 50  0001 C CNN
F 3 "" H 800 4350 50  0001 C CNN
	1    800  4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 4150 800  4150
Wire Wire Line
	800  4150 800  4200
$Comp
L GND #PWR024
U 1 1 59EFD161
P 3500 5700
F 0 "#PWR024" H 3500 5450 50  0001 C CNN
F 1 "GND" H 3505 5527 50  0000 C CNN
F 2 "" H 3500 5700 50  0001 C CNN
F 3 "" H 3500 5700 50  0001 C CNN
	1    3500 5700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 59EFD231
P 800 4550
F 0 "#PWR013" H 800 4300 50  0001 C CNN
F 1 "GND" H 805 4377 50  0000 C CNN
F 2 "" H 800 4550 50  0001 C CNN
F 3 "" H 800 4550 50  0001 C CNN
	1    800  4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	800  4500 800  4550
Wire Wire Line
	1350 4450 1050 4450
Wire Wire Line
	1350 4550 1050 4550
Text Label 1100 4450 0    60   ~ 0
SCL
Text Label 1100 4550 0    60   ~ 0
SDA
Wire Wire Line
	3350 3000 4050 3000
Wire Wire Line
	3350 3100 4050 3100
Wire Wire Line
	3350 3200 4050 3200
Wire Wire Line
	3350 3300 4050 3300
Text Label 3400 3100 0    60   ~ 0
MISO
Text Label 3400 3000 0    60   ~ 0
MOSI
Text Label 3400 3200 0    60   ~ 0
SCLK
Text Label 3400 3300 0    60   ~ 0
SS
Text HLabel 1250 4950 0    60   Input ~ 0
CPU_ANA_IN1
Text HLabel 1250 5150 0    60   Input ~ 0
CPU_ANA_IN2
Wire Wire Line
	1250 4950 1350 4950
Wire Wire Line
	1250 5150 1350 5150
Wire Wire Line
	9000 1450 8800 1450
Wire Wire Line
	8250 1950 8250 2150
Wire Wire Line
	7500 1200 7500 1250
Wire Wire Line
	7500 1250 7850 1250
Wire Wire Line
	7150 1200 7150 1400
Wire Wire Line
	7150 1400 7850 1400
Text Label 7550 1250 0    60   ~ 0
SDA
Text Label 7550 1400 0    60   ~ 0
SCL
Text HLabel 1250 2750 0    60   Input ~ 0
CPU_ANA_OUT1
Text HLabel 1250 3550 0    60   Input ~ 0
CPU_ANA_OUT2
Wire Wire Line
	1350 2750 1250 2750
Wire Wire Line
	1350 3550 1250 3550
Text HLabel 1250 5050 0    60   Input ~ 0
CPU_FREQ_IN1
Text HLabel 1250 4850 0    60   Input ~ 0
CPU_FREQ_IN2
Wire Wire Line
	1350 4850 1250 4850
Wire Wire Line
	1350 5050 1250 5050
Text HLabel 1250 3050 0    60   Input ~ 0
CPU_FREQ_OUT1
Text HLabel 1250 2650 0    60   Input ~ 0
CPU_FREQ_OUT2
Wire Wire Line
	1250 2650 1350 2650
Wire Wire Line
	1250 3050 1350 3050
Wire Wire Line
	7700 4050 8250 4050
Wire Wire Line
	7700 3950 8250 3950
Wire Wire Line
	7700 3850 8250 3850
Wire Wire Line
	7700 3750 8250 3750
Text Label 7800 3750 0    60   ~ 0
SS
Text Label 7800 3850 0    60   ~ 0
MISO
Text Label 7800 3950 0    60   ~ 0
MOSI
Text Label 7800 4050 0    60   ~ 0
SCLK
Wire Wire Line
	7700 2950 8250 2950
Wire Wire Line
	7700 3050 8250 3050
Text Label 7800 2950 0    60   ~ 0
SDA
Text Label 7800 3050 0    60   ~ 0
SCLK
$Comp
L +5V #PWR025
U 1 1 59F00FC9
P 6600 2150
F 0 "#PWR025" H 6600 2000 50  0001 C CNN
F 1 "+5V" H 6615 2323 50  0000 C CNN
F 2 "" H 6600 2150 50  0001 C CNN
F 3 "" H 6600 2150 50  0001 C CNN
	1    6600 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 2150 6600 2550
Wire Wire Line
	6700 2350 6700 2550
Wire Wire Line
	6400 2350 6700 2350
Connection ~ 6600 2350
Text HLabel 6400 2350 0    60   Input ~ 0
5V
$Comp
L GND #PWR026
U 1 1 59F01AA0
P 6700 5400
F 0 "#PWR026" H 6700 5150 50  0001 C CNN
F 1 "GND" H 6705 5227 50  0000 C CNN
F 2 "" H 6700 5400 50  0001 C CNN
F 3 "" H 6700 5400 50  0001 C CNN
	1    6700 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 5150 6400 5300
Wire Wire Line
	6400 5300 7200 5300
Wire Wire Line
	6700 5150 6700 5400
Wire Wire Line
	7100 5300 7100 5150
Connection ~ 6700 5300
Wire Wire Line
	6500 5150 6500 5300
Connection ~ 6500 5300
Wire Wire Line
	6600 5150 6600 5300
Connection ~ 6600 5300
Wire Wire Line
	6800 5150 6800 5300
Connection ~ 6800 5300
Wire Wire Line
	6900 5150 6900 5300
Connection ~ 6900 5300
Wire Wire Line
	7000 5150 7000 5300
Connection ~ 7000 5300
Wire Wire Line
	7700 3350 8250 3350
Wire Wire Line
	7700 3450 8250 3450
Text Label 7800 3350 0    60   ~ 0
VL53L0X_GP
Text Label 7800 3450 0    60   ~ 0
VL53L0X_XSHUT
Wire Wire Line
	7700 4250 8250 4250
Text Label 7800 4250 0    60   ~ 0
TEMP_INT
Wire Wire Line
	5400 3650 5900 3650
Text Label 5450 3650 0    60   ~ 0
ICM_INT
Text HLabel 7200 5300 2    60   Input ~ 0
GND
Connection ~ 7100 5300
$Comp
L VCC #PWR027
U 1 1 59F014B2
P 6900 2150
F 0 "#PWR027" H 6900 2000 50  0001 C CNN
F 1 "VCC" H 6917 2323 50  0000 C CNN
F 2 "" H 6900 2150 50  0001 C CNN
F 3 "" H 6900 2150 50  0001 C CNN
	1    6900 2150
	1    0    0    -1  
$EndComp
Connection ~ 6900 2350
Wire Wire Line
	6900 2150 6900 2550
Connection ~ 7000 2350
Wire Wire Line
	7000 2550 7000 2350
Wire Wire Line
	6900 2350 7100 2350
Text HLabel 7100 2350 2    60   Input ~ 0
+3V3
NoConn ~ 2000 1350
NoConn ~ 2000 1450
NoConn ~ 1350 2450
NoConn ~ 1350 2550
NoConn ~ 1350 2850
NoConn ~ 1350 2950
NoConn ~ 1350 3150
NoConn ~ 1350 3450
NoConn ~ 1350 3650
NoConn ~ 1350 3750
NoConn ~ 1350 3850
NoConn ~ 1350 3950
NoConn ~ 1350 4050
NoConn ~ 1350 4650
NoConn ~ 1350 4750
Wire Wire Line
	3650 5200 4050 5200
NoConn ~ 3350 2800
NoConn ~ 3350 2900
NoConn ~ 5900 3550
NoConn ~ 5900 3750
NoConn ~ 5900 3850
NoConn ~ 5900 3950
NoConn ~ 5900 4050
NoConn ~ 5900 4250
NoConn ~ 5900 4550
NoConn ~ 5900 4650
NoConn ~ 7700 4650
NoConn ~ 7700 4550
NoConn ~ 7700 3650
NoConn ~ 7700 3150
NoConn ~ 10300 1700
$Comp
L ICM-20602 U5
U 1 1 59F1D1C3
P 9250 5250
F 0 "U5" H 9250 5887 60  0000 C CNN
F 1 "ICM-20602" H 9250 5781 60  0000 C CNN
F 2 "" H 9250 5250 60  0001 C CNN
F 3 "" H 9250 5250 60  0001 C CNN
	1    9250 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	10900 4750 10900 5300
Wire Wire Line
	10900 5600 10900 6100
Wire Wire Line
	9850 4900 10900 4900
Connection ~ 10900 4900
$Comp
L C C22
U 1 1 59F1D95C
P 10200 5150
F 0 "C22" H 10315 5196 50  0000 L CNN
F 1 "0.1u" H 10315 5105 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 10238 5000 50  0001 C CNN
F 3 "" H 10200 5150 50  0001 C CNN
	1    10200 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 5000 10900 5000
Connection ~ 10200 5000
Wire Wire Line
	9850 5800 10900 5800
Connection ~ 10900 5800
Wire Wire Line
	10600 5300 10600 5800
Connection ~ 10600 5800
Wire Wire Line
	10200 5300 10200 5800
Connection ~ 10200 5800
Wire Wire Line
	9850 5300 9950 5300
Wire Wire Line
	9950 5300 9950 5800
Connection ~ 9950 5800
Wire Wire Line
	9850 5400 9950 5400
Connection ~ 9950 5400
Wire Wire Line
	9850 5500 9950 5500
Connection ~ 9950 5500
Wire Wire Line
	9850 5600 9950 5600
Connection ~ 9950 5600
Wire Wire Line
	9850 5700 9950 5700
Connection ~ 9950 5700
Wire Wire Line
	8650 5750 8050 5750
Wire Wire Line
	8650 4900 8400 4900
Wire Wire Line
	8650 5000 8400 5000
Text Label 8450 4900 0    60   ~ 0
SCL
Text Label 8450 5000 0    60   ~ 0
SDA
$Comp
L VCC #PWR03
U 1 1 59F1E6C3
P 8250 5000
F 0 "#PWR03" H 8250 4850 50  0001 C CNN
F 1 "VCC" H 8267 5173 50  0000 C CNN
F 2 "" H 8250 5000 50  0001 C CNN
F 3 "" H 8250 5000 50  0001 C CNN
	1    8250 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 5100 8250 5100
Wire Wire Line
	8250 5000 8250 5200
Wire Wire Line
	8250 5200 8650 5200
Connection ~ 8250 5100
NoConn ~ 8650 5650
Text Label 8150 5750 0    60   ~ 0
ICM_INT
NoConn ~ 3350 3500
NoConn ~ 3350 3600
Wire Wire Line
	3350 3700 4050 3700
Wire Wire Line
	3350 3800 4050 3800
Wire Wire Line
	3350 3900 4050 3900
Wire Wire Line
	3350 4000 4050 4000
Text Label 3450 3700 0    60   ~ 0
GP1
Text Label 3450 3800 0    60   ~ 0
GP2
Text Label 3450 3900 0    60   ~ 0
GP3
Text Label 3450 4000 0    60   ~ 0
GP4
Wire Wire Line
	5900 3150 5400 3150
Wire Wire Line
	5900 3250 5400 3250
Wire Wire Line
	5900 3350 5400 3350
Wire Wire Line
	5900 3450 5400 3450
Text Label 5450 3150 0    60   ~ 0
GP1
Text Label 5450 3250 0    60   ~ 0
GP2
Text Label 5450 3350 0    60   ~ 0
GP3
Text Label 5450 3450 0    60   ~ 0
GP4
Connection ~ 10900 5000
Connection ~ 10600 5000
NoConn ~ 7700 4350
NoConn ~ 5900 4150
$EndSCHEMATC
