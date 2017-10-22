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
L CY8C4A25LQI-473 U?
U 1 1 59E95B73
P 2450 3550
F 0 "U?" H 2450 4937 60  0000 C CNN
F 1 "CY8C4A25LQI-473" H 2450 4831 60  0000 C CNN
F 2 "" H 2450 3550 60  0001 C CNN
F 3 "" H 2450 3550 60  0001 C CNN
	1    2450 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59E95C1A
P 2550 7150
F 0 "#PWR?" H 2550 6900 50  0001 C CNN
F 1 "GND" H 2555 6977 50  0000 C CNN
F 2 "" H 2550 7150 50  0001 C CNN
F 3 "" H 2550 7150 50  0001 C CNN
	1    2550 7150
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 59E95C3F
P 4550 5350
F 0 "C?" H 4665 5396 50  0000 L CNN
F 1 "0.1u" H 4665 5305 50  0000 L CNN
F 2 "" H 4588 5200 50  0001 C CNN
F 3 "" H 4550 5350 50  0001 C CNN
	1    4550 5350
	1    0    0    -1  
$EndComp
Text GLabel 2350 6900 0    60   Input ~ 0
VCC
Wire Wire Line
	3450 5050 3750 5050
Wire Wire Line
	3450 4950 4550 4950
Wire Wire Line
	4550 4950 4550 5200
Text GLabel 2350 7150 0    60   Input ~ 0
GND
$Comp
L VCC #PWR?
U 1 1 59E95F66
P 2550 6900
F 0 "#PWR?" H 2550 6750 50  0001 C CNN
F 1 "VCC" H 2567 7073 50  0000 C CNN
F 2 "" H 2550 6900 50  0001 C CNN
F 3 "" H 2550 6900 50  0001 C CNN
	1    2550 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 5050 3750 5200
Wire Wire Line
	3750 5200 4450 5200
Wire Wire Line
	3450 5150 3600 5150
Wire Wire Line
	3600 5150 3600 5600
Wire Wire Line
	4550 5550 4550 5500
Wire Wire Line
	3600 5550 4550 5550
Connection ~ 3600 5550
$Comp
L C C?
U 1 1 59E95FD6
P 3750 5350
F 0 "C?" H 3865 5396 50  0000 L CNN
F 1 "0.1u" H 3865 5305 50  0000 L CNN
F 2 "" H 3788 5200 50  0001 C CNN
F 3 "" H 3750 5350 50  0001 C CNN
	1    3750 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 5500 3750 5550
Connection ~ 3750 5550
$Comp
L C C?
U 1 1 59E96031
P 4150 5350
F 0 "C?" H 4265 5396 50  0000 L CNN
F 1 "1u" H 4265 5305 50  0000 L CNN
F 2 "" H 4188 5200 50  0001 C CNN
F 3 "" H 4150 5350 50  0001 C CNN
	1    4150 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 5500 4150 5550
Connection ~ 4150 5550
$Comp
L C C?
U 1 1 59E96161
P 4150 4450
F 0 "C?" H 4265 4496 50  0000 L CNN
F 1 "1u" H 4265 4405 50  0000 L CNN
F 2 "" H 4188 4300 50  0001 C CNN
F 3 "" H 4150 4450 50  0001 C CNN
	1    4150 4450
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 59E96183
P 3750 4450
F 0 "C?" H 3865 4496 50  0000 L CNN
F 1 "0.1u" H 3865 4405 50  0000 L CNN
F 2 "" H 3788 4300 50  0001 C CNN
F 3 "" H 3750 4450 50  0001 C CNN
	1    3750 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 4250 4150 4250
Wire Wire Line
	4150 4250 4150 4300
Wire Wire Line
	3750 4300 3750 4250
Connection ~ 3750 4250
Wire Wire Line
	3450 4350 3550 4350
Wire Wire Line
	3550 4250 3550 4450
Connection ~ 3550 4250
Wire Wire Line
	3550 4450 3450 4450
Connection ~ 3550 4350
Wire Wire Line
	3450 4750 4150 4750
Wire Wire Line
	4150 4750 4150 4600
Wire Wire Line
	3750 4600 3750 4750
Connection ~ 3750 4750
Wire Wire Line
	3450 4650 3550 4650
Wire Wire Line
	3550 4550 3550 4750
Connection ~ 3550 4750
Wire Wire Line
	3450 4550 3550 4550
Connection ~ 3550 4650
$Comp
L FTSH-105-01-L-DV-K J?
U 1 1 59E96382
P 1550 1350
F 0 "J?" H 1575 1797 60  0000 C CNN
F 1 "FTSH-105-01-L-DV-K" H 1575 1691 60  0000 C CNN
F 2 "" H 1700 1350 60  0001 C CNN
F 3 "" H 1700 1350 60  0001 C CNN
	1    1550 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 7150 2550 7150
Wire Wire Line
	2350 6900 2550 6900
$Comp
L GND #PWR?
U 1 1 59E96769
P 1000 1600
F 0 "#PWR?" H 1000 1350 50  0001 C CNN
F 1 "GND" H 1005 1427 50  0000 C CNN
F 2 "" H 1000 1600 50  0001 C CNN
F 3 "" H 1000 1600 50  0001 C CNN
	1    1000 1600
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR?
U 1 1 59E9676F
P 1000 1000
F 0 "#PWR?" H 1000 850 50  0001 C CNN
F 1 "VCC" H 1017 1173 50  0000 C CNN
F 2 "" H 1000 1000 50  0001 C CNN
F 3 "" H 1000 1000 50  0001 C CNN
	1    1000 1000
	1    0    0    -1  
$EndComp
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
	3450 2450 4150 2450
Wire Wire Line
	3450 2550 4150 2550
Wire Wire Line
	3450 2650 4150 2650
Text Label 3500 2450 0    60   ~ 0
SWDIO
Text Label 3500 2550 0    60   ~ 0
SWDCLK
Text Label 3500 2650 0    60   ~ 0
XRES
Wire Wire Line
	2000 1150 2500 1150
Wire Wire Line
	2000 1250 2500 1250
Wire Wire Line
	2000 1550 2500 1550
Text Label 2050 1150 0    60   ~ 0
SWDIO
Text Label 2050 1250 0    60   ~ 0
SWDCLK
Text Label 2050 1550 0    60   ~ 0
XRES
$Comp
L Q_NPN_BCE Q?
U 1 1 59E9701E
P 7500 1750
F 0 "Q?" H 7691 1796 50  0000 L CNN
F 1 "Q_NPN_BCE" H 7691 1705 50  0000 L CNN
F 2 "" H 7700 1850 50  0001 C CNN
F 3 "" H 7500 1750 50  0001 C CNN
	1    7500 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 1750 6550 1750
$Comp
L GND #PWR?
U 1 1 59E9E700
P 7600 2250
F 0 "#PWR?" H 7600 2000 50  0001 C CNN
F 1 "GND" H 7605 2077 50  0000 C CNN
F 2 "" H 7600 2250 50  0001 C CNN
F 3 "" H 7600 2250 50  0001 C CNN
	1    7600 2250
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 59E9E732
P 7600 1300
F 0 "R?" H 7670 1346 50  0000 L CNN
F 1 "1k" H 7670 1255 50  0000 L CNN
F 2 "" V 7530 1300 50  0001 C CNN
F 3 "" H 7600 1300 50  0001 C CNN
	1    7600 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 1450 7600 1550
Wire Wire Line
	7600 1950 7600 2250
Connection ~ 7600 1500
$Comp
L Q_NPN_BCE Q?
U 1 1 59E9EAF8
P 9900 1750
F 0 "Q?" H 10091 1796 50  0000 L CNN
F 1 "Q_NPN_BCE" H 10091 1705 50  0000 L CNN
F 2 "" H 10100 1850 50  0001 C CNN
F 3 "" H 9900 1750 50  0001 C CNN
	1    9900 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 1750 8950 1750
$Comp
L GND #PWR?
U 1 1 59E9EAFF
P 10000 2200
F 0 "#PWR?" H 10000 1950 50  0001 C CNN
F 1 "GND" H 10005 2027 50  0000 C CNN
F 2 "" H 10000 2200 50  0001 C CNN
F 3 "" H 10000 2200 50  0001 C CNN
	1    10000 2200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 59E9EB05
P 10000 1300
F 0 "R?" H 10070 1346 50  0000 L CNN
F 1 "1k" H 10070 1255 50  0000 L CNN
F 2 "" V 9930 1300 50  0001 C CNN
F 3 "" H 10000 1300 50  0001 C CNN
	1    10000 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 1450 10000 1550
Wire Wire Line
	10000 1950 10000 2200
Connection ~ 10000 1500
Wire Wire Line
	10000 1100 10000 1100
Wire Wire Line
	10000 1100 10000 1150
Wire Wire Line
	7600 1100 7600 1100
Wire Wire Line
	7600 1100 7600 1150
Text Label 6650 1750 0    60   ~ 0
CPU_DOUT1
Text Label 9050 1750 0    60   ~ 0
CPU_DOUT2
$Comp
L Q_NPN_BCE Q?
U 1 1 59E9EF10
P 7650 4850
F 0 "Q?" H 7841 4804 50  0000 L CNN
F 1 "Q_NPN_BCE" H 7841 4895 50  0000 L CNN
F 2 "" H 7850 4950 50  0001 C CNN
F 3 "" H 7650 4850 50  0001 C CNN
	1    7650 4850
	1    0    0    1   
$EndComp
Wire Wire Line
	6450 4850 7450 4850
Text GLabel 3100 6900 0    60   Input ~ 0
12V
$Comp
L +12V #PWR?
U 1 1 59E9FE79
P 3300 6750
F 0 "#PWR?" H 3300 6600 50  0001 C CNN
F 1 "+12V" H 3315 6923 50  0000 C CNN
F 2 "" H 3300 6750 50  0001 C CNN
F 3 "" H 3300 6750 50  0001 C CNN
	1    3300 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 6900 3300 6900
Wire Wire Line
	3300 6900 3300 6750
$Comp
L +12V #PWR?
U 1 1 59E9FFAB
P 10000 1100
F 0 "#PWR?" H 10000 950 50  0001 C CNN
F 1 "+12V" H 10015 1273 50  0000 C CNN
F 2 "" H 10000 1100 50  0001 C CNN
F 3 "" H 10000 1100 50  0001 C CNN
	1    10000 1100
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR?
U 1 1 59EA00ED
P 7600 1100
F 0 "#PWR?" H 7600 950 50  0001 C CNN
F 1 "+12V" H 7615 1273 50  0000 C CNN
F 2 "" H 7600 1100 50  0001 C CNN
F 3 "" H 7600 1100 50  0001 C CNN
	1    7600 1100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59EA03EA
P 7750 5500
F 0 "#PWR?" H 7750 5250 50  0001 C CNN
F 1 "GND" H 7755 5327 50  0000 C CNN
F 2 "" H 7750 5500 50  0001 C CNN
F 3 "" H 7750 5500 50  0001 C CNN
	1    7750 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 5050 7750 5500
$Comp
L +12V #PWR?
U 1 1 59EA052B
P 6450 4300
F 0 "#PWR?" H 6450 4150 50  0001 C CNN
F 1 "+12V" H 6465 4473 50  0000 C CNN
F 2 "" H 6450 4300 50  0001 C CNN
F 3 "" H 6450 4300 50  0001 C CNN
	1    6450 4300
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR?
U 1 1 59EA056C
P 7750 4400
F 0 "#PWR?" H 7750 4250 50  0001 C CNN
F 1 "VCC" H 7767 4573 50  0000 C CNN
F 2 "" H 7750 4400 50  0001 C CNN
F 3 "" H 7750 4400 50  0001 C CNN
	1    7750 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 4400 7750 4650
$Comp
L R R?
U 1 1 59EA0648
P 7200 4500
F 0 "R?" H 7270 4546 50  0000 L CNN
F 1 "1k" H 7270 4455 50  0000 L CNN
F 2 "" V 7130 4500 50  0001 C CNN
F 3 "" H 7200 4500 50  0001 C CNN
	1    7200 4500
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J?
U 1 1 59EA07D1
P 6750 4100
F 0 "J?" V 6715 3962 50  0000 R CNN
F 1 "CONN_01X02" V 6624 3962 50  0000 R CNN
F 2 "" H 6750 4100 50  0001 C CNN
F 3 "" H 6750 4100 50  0001 C CNN
	1    6750 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6450 4300 6700 4300
Wire Wire Line
	6800 4300 7200 4300
Wire Wire Line
	7200 4300 7200 4350
Wire Wire Line
	7200 4650 7200 5000
Connection ~ 7200 4850
$Comp
L Q_NPN_BCE Q?
U 1 1 59EA0DDD
P 9750 4850
F 0 "Q?" H 9941 4804 50  0000 L CNN
F 1 "Q_NPN_BCE" H 9941 4895 50  0000 L CNN
F 2 "" H 9950 4950 50  0001 C CNN
F 3 "" H 9750 4850 50  0001 C CNN
	1    9750 4850
	1    0    0    1   
$EndComp
Wire Wire Line
	8500 4850 9550 4850
$Comp
L GND #PWR?
U 1 1 59EA0DE5
P 9850 5450
F 0 "#PWR?" H 9850 5200 50  0001 C CNN
F 1 "GND" H 9855 5277 50  0000 C CNN
F 2 "" H 9850 5450 50  0001 C CNN
F 3 "" H 9850 5450 50  0001 C CNN
	1    9850 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 5050 9850 5450
$Comp
L +12V #PWR?
U 1 1 59EA0DEC
P 8550 4300
F 0 "#PWR?" H 8550 4150 50  0001 C CNN
F 1 "+12V" H 8565 4473 50  0000 C CNN
F 2 "" H 8550 4300 50  0001 C CNN
F 3 "" H 8550 4300 50  0001 C CNN
	1    8550 4300
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR?
U 1 1 59EA0DF2
P 9850 4400
F 0 "#PWR?" H 9850 4250 50  0001 C CNN
F 1 "VCC" H 9867 4573 50  0000 C CNN
F 2 "" H 9850 4400 50  0001 C CNN
F 3 "" H 9850 4400 50  0001 C CNN
	1    9850 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 4400 9850 4650
$Comp
L R R?
U 1 1 59EA0DF9
P 9300 4500
F 0 "R?" H 9370 4546 50  0000 L CNN
F 1 "1k" H 9370 4455 50  0000 L CNN
F 2 "" V 9230 4500 50  0001 C CNN
F 3 "" H 9300 4500 50  0001 C CNN
	1    9300 4500
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 J?
U 1 1 59EA0DFF
P 8850 4100
F 0 "J?" V 8815 3962 50  0000 R CNN
F 1 "CONN_01X02" V 8724 3962 50  0000 R CNN
F 2 "" H 8850 4100 50  0001 C CNN
F 3 "" H 8850 4100 50  0001 C CNN
	1    8850 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8550 4300 8800 4300
Wire Wire Line
	8900 4300 9300 4300
Wire Wire Line
	9300 4300 9300 4350
Wire Wire Line
	9300 4650 9300 5000
Connection ~ 9300 4850
Wire Wire Line
	7750 4600 8350 4600
Connection ~ 7750 4600
Wire Wire Line
	9850 4550 10650 4550
Connection ~ 9850 4550
Text Label 7850 4600 0    60   ~ 0
CPU_DIN1
Text Label 10000 4550 0    60   ~ 0
CPU_DIN2
$Comp
L D_TVS D?
U 1 1 59EA10D6
P 7200 5150
F 0 "D?" V 7154 5229 50  0000 L CNN
F 1 "D_TVS" V 7245 5229 50  0000 L CNN
F 2 "" H 7200 5150 50  0001 C CNN
F 3 "" H 7200 5150 50  0001 C CNN
	1    7200 5150
	0    1    1    0   
$EndComp
$Comp
L D_TVS D?
U 1 1 59EA1312
P 9300 5150
F 0 "D?" V 9254 5229 50  0000 L CNN
F 1 "D_TVS" V 9345 5229 50  0000 L CNN
F 2 "" H 9300 5150 50  0001 C CNN
F 3 "" H 9300 5150 50  0001 C CNN
	1    9300 5150
	0    1    1    0   
$EndComp
Wire Wire Line
	7200 5300 7200 5350
Wire Wire Line
	7200 5350 7750 5350
Connection ~ 7750 5350
Wire Wire Line
	9300 5300 9300 5350
Wire Wire Line
	9300 5350 9850 5350
Connection ~ 9850 5350
$Comp
L D_TVS D?
U 1 1 59EA15E2
P 8200 1850
F 0 "D?" V 8154 1929 50  0000 L CNN
F 1 "D_TVS" V 8245 1929 50  0000 L CNN
F 2 "" H 8200 1850 50  0001 C CNN
F 3 "" H 8200 1850 50  0001 C CNN
	1    8200 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	8200 1700 8200 1500
Connection ~ 8200 1500
Wire Wire Line
	8200 2000 8200 2100
Wire Wire Line
	8200 2100 7600 2100
Connection ~ 7600 2100
$Comp
L D_TVS D?
U 1 1 59EA1E08
P 10600 1800
F 0 "D?" V 10554 1879 50  0000 L CNN
F 1 "D_TVS" V 10645 1879 50  0000 L CNN
F 2 "" H 10600 1800 50  0001 C CNN
F 3 "" H 10600 1800 50  0001 C CNN
	1    10600 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	10600 1650 10600 1500
Connection ~ 10600 1500
Wire Wire Line
	10600 1950 10600 2050
Wire Wire Line
	10600 2050 10000 2050
Connection ~ 10000 2050
Wire Wire Line
	8200 1500 7600 1500
Wire Wire Line
	10600 1500 10000 1500
Text Label 7750 1500 0    60   ~ 0
DOUT1
Text Label 10200 1500 0    60   ~ 0
DOUT2
Text Label 6550 4850 0    60   ~ 0
DIN1
Text Label 8700 4850 0    60   ~ 0
DIN2
$Comp
L CONN_01X06 J?
U 1 1 59EA24F9
P 10550 3200
F 0 "J?" H 10628 3241 50  0000 L CNN
F 1 "CONN_01X06" H 10628 3150 50  0000 L CNN
F 2 "" H 10550 3200 50  0001 C CNN
F 3 "" H 10550 3200 50  0001 C CNN
	1    10550 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 2950 9600 2950
Wire Wire Line
	9350 3050 10350 3050
Wire Wire Line
	10350 3150 9600 3150
Wire Wire Line
	10350 3250 9600 3250
Wire Wire Line
	10350 3350 9600 3350
Wire Wire Line
	10350 3450 9600 3450
Text Label 9800 2950 0    60   ~ 0
12v
Text Label 9800 3050 0    60   ~ 0
GND
Text Label 9800 3150 0    60   ~ 0
DOUT1
Text Label 9800 3250 0    60   ~ 0
DOUT2
Text Label 9800 3350 0    60   ~ 0
DIN1
Text Label 9800 3450 0    60   ~ 0
DIN2
$Comp
L +12V #PWR?
U 1 1 59EA2CE1
P 9600 2950
F 0 "#PWR?" H 9600 2800 50  0001 C CNN
F 1 "+12V" H 9615 3123 50  0000 C CNN
F 2 "" H 9600 2950 50  0001 C CNN
F 3 "" H 9600 2950 50  0001 C CNN
	1    9600 2950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59EA2D18
P 9350 3050
F 0 "#PWR?" H 9350 2800 50  0001 C CNN
F 1 "GND" H 9355 2877 50  0000 C CNN
F 2 "" H 9350 3050 50  0001 C CNN
F 3 "" H 9350 3050 50  0001 C CNN
	1    9350 3050
	1    0    0    -1  
$EndComp
$EndSCHEMATC