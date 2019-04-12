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
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
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
L Q_NPN_BCE Q1
U 1 1 59E9EF10
P 9900 4950
F 0 "Q1" H 10091 4904 50  0000 L CNN
F 1 "Q_NPN_BCE" H 10091 4995 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 10100 5050 50  0001 C CNN
F 3 "" H 9900 4950 50  0001 C CNN
F 4 "MMBT3904FSCT-ND" H 9900 4950 60  0001 C CNN "Digikey"
	1    9900 4950
	1    0    0    1   
$EndComp
$Comp
L GND #PWR026
U 1 1 59EA03EA
P 10000 5750
F 0 "#PWR026" H 10000 5500 50  0001 C CNN
F 1 "GND" H 10005 5577 50  0000 C CNN
F 2 "" H 10000 5750 50  0001 C CNN
F 3 "" H 10000 5750 50  0001 C CNN
	1    10000 5750
	1    0    0    -1  
$EndComp
$Comp
L R R17
U 1 1 59EA0648
P 8800 4600
F 0 "R17" H 8870 4646 50  0000 L CNN
F 1 "24.3k" H 8870 4555 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 8730 4600 50  0001 C CNN
F 3 "" H 8800 4600 50  0001 C CNN
	1    8800 4600
	-1   0    0    1   
$EndComp
$Comp
L R R18
U 1 1 59EB4696
P 9200 4950
F 0 "R18" V 9407 4950 50  0000 C CNN
F 1 "24.3k" V 9316 4950 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 9130 4950 50  0001 C CNN
F 3 "" H 9200 4950 50  0001 C CNN
	1    9200 4950
	0    -1   -1   0   
$EndComp
$Comp
L R R19
U 1 1 59EB4799
P 9550 5100
F 0 "R19" H 9481 5146 50  0000 R CNN
F 1 "24.3k" H 9481 5055 50  0000 R CNN
F 2 "Resistors_SMD:R_0603" V 9480 5100 50  0001 C CNN
F 3 "" H 9550 5100 50  0001 C CNN
	1    9550 5100
	1    0    0    -1  
$EndComp
$Comp
L LMC6032 U4
U 1 1 59EBA988
P 1950 2450
F 0 "U4" H 1950 2947 60  0000 C CNN
F 1 "LMC6032" H 1950 2841 60  0000 C CNN
F 2 "SMD_Packages:SOIC-8-N" H 1950 2450 60  0001 C CNN
F 3 "" H 1950 2450 60  0001 C CNN
F 4 "LMC6032IMX/NOPBDKR-ND" H 0   0   60  0001 C CNN "Digikey"
F 5 "LMC6032IMX/NOPB" H 0   0   60  0001 C CNN "Partnum"
	1    1950 2450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR024
U 1 1 59EBF2A0
P 1550 800
F 0 "#PWR024" H 1550 550 50  0001 C CNN
F 1 "GND" H 1555 627 50  0000 C CNN
F 2 "" H 1550 800 50  0001 C CNN
F 3 "" H 1550 800 50  0001 C CNN
	1    1550 800 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 59EC6B5F
P 2600 3600
F 0 "#PWR025" H 2600 3350 50  0001 C CNN
F 1 "GND" H 2605 3427 50  0000 C CNN
F 2 "" H 2600 3600 50  0001 C CNN
F 3 "" H 2600 3600 50  0001 C CNN
	1    2600 3600
	1    0    0    -1  
$EndComp
$Comp
L R R15
U 1 1 59ED1E9D
P 4300 2350
F 0 "R15" V 4300 2300 50  0000 L CNN
F 1 "24.3k" V 4200 2300 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 4230 2350 50  0001 C CNN
F 3 "" H 4300 2350 50  0001 C CNN
F 4 "311-24.3KHRCT-ND" V 4300 2350 60  0001 C CNN "Digikey"
	1    4300 2350
	0    1    1    0   
$EndComp
$Comp
L R R16
U 1 1 59ED1EFF
P 4300 2550
F 0 "R16" V 4300 2500 50  0000 L CNN
F 1 "24.3k" V 4400 2500 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 4230 2550 50  0001 C CNN
F 3 "" H 4300 2550 50  0001 C CNN
	1    4300 2550
	0    1    1    0   
$EndComp
$Comp
L C C18
U 1 1 59ED235D
P 2750 3200
F 0 "C18" H 2865 3246 50  0000 L CNN
F 1 "10n" H 2865 3155 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2788 3050 50  0001 C CNN
F 3 "" H 2750 3200 50  0001 C CNN
	1    2750 3200
	1    0    0    -1  
$EndComp
$Comp
L C C19
U 1 1 59ED24B1
P 3150 3200
F 0 "C19" H 3265 3246 50  0000 L CNN
F 1 "10n" H 3265 3155 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3188 3050 50  0001 C CNN
F 3 "" H 3150 3200 50  0001 C CNN
	1    3150 3200
	1    0    0    -1  
$EndComp
$Comp
L D_Zener D4
U 1 1 59EE2D57
P 3550 3200
F 0 "D4" V 3504 3279 50  0000 L CNN
F 1 "D_Zener" V 3595 3279 50  0000 L CNN
F 2 "Diodes_SMD:D_SMB" H 3550 3200 50  0001 C CNN
F 3 "" H 3550 3200 50  0001 C CNN
F 4 "MMSZ5232B-FDICT-ND" V 3550 3200 60  0001 C CNN "Digikey"
F 5 "MMSZ5232B" H 0   0   60  0001 C CNN "Partnum"
	1    3550 3200
	0    1    1    0   
$EndComp
$Comp
L D_Zener D5
U 1 1 59EE2DE3
P 4000 3200
F 0 "D5" V 3954 3279 50  0000 L CNN
F 1 "D_Zener" V 4045 3279 50  0000 L CNN
F 2 "Diodes_SMD:D_SMB" H 4000 3200 50  0001 C CNN
F 3 "" H 4000 3200 50  0001 C CNN
F 4 "MMSZ5232B-FDICT-ND" V 4000 3200 60  0001 C CNN "Digikey"
F 5 "MMSZ5232B" H 0   0   60  0001 C CNN "Partnum"
	1    4000 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	8050 4950 9050 4950
Wire Wire Line
	10000 5150 10000 5750
Wire Wire Line
	8800 4350 8800 4450
Wire Wire Line
	8800 4750 8800 5150
Connection ~ 8800 4950
Wire Wire Line
	10000 4700 10100 4700
Wire Wire Line
	8800 5650 10000 5650
Connection ~ 10000 5650
Wire Wire Line
	9350 4950 9700 4950
Connection ~ 9550 4950
Wire Wire Line
	9550 5250 9550 5650
Connection ~ 9550 5650
Wire Wire Line
	8800 5450 8800 5650
Wire Wire Line
	1400 650  1550 650 
Wire Wire Line
	1550 650  1550 800 
Wire Wire Line
	2550 2750 2600 2750
Wire Wire Line
	2550 2350 4150 2350
Wire Wire Line
	1350 2350 1300 2350
Wire Wire Line
	1350 2550 1300 2550
Wire Wire Line
	2750 2550 2750 3050
Connection ~ 2750 2550
Wire Wire Line
	3150 1700 3150 3050
Connection ~ 3150 2350
Wire Wire Line
	2750 3350 2750 3500
Wire Wire Line
	2600 3500 4000 3500
Wire Wire Line
	3150 3500 3150 3350
Connection ~ 2750 3500
Connection ~ 3150 3500
Wire Wire Line
	3550 3350 3550 3500
Connection ~ 3550 3500
Connection ~ 3550 2550
Connection ~ 4000 2350
Wire Wire Line
	4000 3500 4000 3350
Wire Wire Line
	2550 2550 4150 2550
Wire Wire Line
	4450 2350 4900 2350
Wire Wire Line
	4450 2550 4900 2550
Wire Wire Line
	1350 1700 1350 2250
Wire Wire Line
	2600 2750 2600 3600
Connection ~ 2600 3500
Wire Wire Line
	1350 2650 1350 3100
Connection ~ 2750 2900
$Comp
L D_TVS D6
U 1 1 59F6C379
P 8800 5300
F 0 "D6" V 8754 5379 50  0000 L CNN
F 1 "D_TVS" V 8845 5379 50  0000 L CNN
F 2 "Diodes_SMD:D_SMB" H 8800 5300 50  0001 C CNN
F 3 "" H 8800 5300 50  0001 C CNN
F 4 "824520201" V 8800 5300 60  0001 C CNN "Partnum"
F 5 "732-9779-1-ND" V 8800 5300 60  0001 C CNN "Digikey"
	1    8800 5300
	0    1    1    0   
$EndComp
$Comp
L R R14
U 1 1 5A04301A
P 1950 1700
F 0 "R14" V 2157 1700 50  0000 C CNN
F 1 "24.3k" V 2066 1700 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1880 1700 50  0001 C CNN
F 3 "" H 1950 1700 50  0001 C CNN
F 4 "311-30KGRCT-ND" V 1950 1700 60  0001 C CNN "Digikey"
	1    1950 1700
	0    -1   -1   0   
$EndComp
$Comp
L R R11
U 1 1 5A043102
P 1000 1700
F 0 "R11" V 793 1700 50  0000 C CNN
F 1 "44.2k" V 884 1700 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 930 1700 50  0001 C CNN
F 3 "" H 1000 1700 50  0001 C CNN
F 4 "P10KGCT-ND" V 1000 1700 60  0001 C CNN "Digikey"
	1    1000 1700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR022
U 1 1 5A0433D9
P 750 1800
F 0 "#PWR022" H 750 1550 50  0001 C CNN
F 1 "GND" H 755 1627 50  0000 C CNN
F 2 "" H 750 1800 50  0001 C CNN
F 3 "" H 750 1800 50  0001 C CNN
	1    750  1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  1800 750  1700
Wire Wire Line
	750  1700 850  1700
Wire Wire Line
	1150 1700 1800 1700
Connection ~ 1350 1700
Wire Wire Line
	2100 1700 3150 1700
$Comp
L R R13
U 1 1 5A043797
P 1850 3100
F 0 "R13" V 2057 3100 50  0000 C CNN
F 1 "24.3k" V 1966 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1780 3100 50  0001 C CNN
F 3 "" H 1850 3100 50  0001 C CNN
	1    1850 3100
	0    -1   -1   0   
$EndComp
$Comp
L R R12
U 1 1 5A043833
P 1000 3100
F 0 "R12" V 793 3100 50  0000 C CNN
F 1 "44.2k" V 884 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 930 3100 50  0001 C CNN
F 3 "" H 1000 3100 50  0001 C CNN
	1    1000 3100
	0    1    1    0   
$EndComp
$Comp
L GND #PWR023
U 1 1 5A0438C1
P 750 3150
F 0 "#PWR023" H 750 2900 50  0001 C CNN
F 1 "GND" H 755 2977 50  0000 C CNN
F 2 "" H 750 3150 50  0001 C CNN
F 3 "" H 750 3150 50  0001 C CNN
	1    750  3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  3150 750  3100
Wire Wire Line
	750  3100 850  3100
Wire Wire Line
	1150 3100 1700 3100
Connection ~ 1350 3100
Wire Wire Line
	2000 3100 2300 3100
Wire Wire Line
	2300 3100 2300 2900
Wire Wire Line
	2300 2900 2750 2900
Wire Wire Line
	2700 2200 2550 2200
$Comp
L ITS42K5D U5
U 1 1 5A809B8E
P 9550 1600
F 0 "U5" H 9550 2137 60  0000 C CNN
F 1 "ITS42K5D" H 9550 2031 60  0000 C CNN
F 2 "KicadFootprint:PG-TSON-10" H 9450 900 60  0001 C CNN
F 3 "" H 9550 1000 60  0001 C CNN
F 4 "ITS42K5DLDFXUMA1CT-ND" H 0   0   60  0001 C CNN "Digikey"
F 5 "ITS42K5DLDFXUMA1" H 0   0   60  0001 C CNN "Partnum"
	1    9550 1600
	1    0    0    -1  
$EndComp
Text GLabel 1300 2350 0    60   Input ~ 0
DAC1
Text GLabel 1300 2550 0    60   Input ~ 0
DAC2
Text GLabel 2700 2200 2    60   Input ~ 0
5V
Text GLabel 1400 650  0    60   Input ~ 0
GND
Wire Wire Line
	3550 3050 3550 2550
Wire Wire Line
	4000 3050 4000 2350
Text GLabel 8650 1350 0    60   Input ~ 0
CPU_DOUT1
Text GLabel 8650 1750 0    60   Input ~ 0
CPU_DOUT2
Wire Wire Line
	8650 1350 8950 1350
Wire Wire Line
	8650 1750 8950 1750
Text GLabel 8650 1450 0    60   Input ~ 0
CPU_DOUT1_ST
Text GLabel 8650 1850 0    60   Input ~ 0
CPU_DOUT2_ST
Wire Wire Line
	8650 1450 8950 1450
Wire Wire Line
	8650 1850 8950 1850
Text GLabel 10400 1350 2    60   Input ~ 0
12V
Wire Wire Line
	10400 1350 10150 1350
Wire Wire Line
	10150 1500 10600 1500
Wire Wire Line
	10150 1700 10600 1700
$Comp
L GND #PWR027
U 1 1 5A80B5E2
P 10250 2200
F 0 "#PWR027" H 10250 1950 50  0001 C CNN
F 1 "GND" H 10255 2027 50  0000 C CNN
F 2 "" H 10250 2200 50  0001 C CNN
F 3 "" H 10250 2200 50  0001 C CNN
	1    10250 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 1850 10250 1850
Wire Wire Line
	10250 1850 10250 2200
Wire Wire Line
	10150 1950 10250 1950
Connection ~ 10250 1950
Wire Wire Line
	10150 2050 10250 2050
Connection ~ 10250 2050
Text GLabel 10100 4700 2    60   Input ~ 0
CPU_DIN1
Wire Wire Line
	10000 4700 10000 4750
Wire Wire Line
	8800 4350 8300 4350
Text Label 8300 4350 0    60   ~ 0
12V_PULLUP
Text Label 10200 1700 0    60   ~ 0
12V_PULLUP
$Comp
L Conn_01x08 J4
U 1 1 5A818E28
P 5800 5150
F 0 "J4" H 5880 5142 50  0000 L CNN
F 1 "Conn_01x08" H 5880 5051 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 5800 5150 50  0001 C CNN
F 3 "" H 5800 5150 50  0001 C CNN
	1    5800 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 4850 5550 4850
Text GLabel 5550 4850 0    60   Input ~ 0
PWR_IN
Text GLabel 5550 4950 0    60   Input ~ 0
GND
Wire Wire Line
	5550 4950 5600 4950
Text Label 10250 1500 0    60   ~ 0
DOUT
Text Label 8050 4950 0    60   ~ 0
DIN
Text Label 4550 2350 0    60   ~ 0
ANA_OUT1
Text Label 4550 2550 0    60   ~ 0
ANA_OUT2
Wire Wire Line
	5600 5050 4600 5050
Wire Wire Line
	5600 5150 4600 5150
Wire Wire Line
	5600 5250 4600 5250
Wire Wire Line
	5600 5350 4600 5350
Wire Wire Line
	5600 5450 5550 5450
Wire Wire Line
	5550 5550 5600 5550
Text Label 4600 5050 0    60   ~ 0
ANA_OUT1
Text Label 4600 5150 0    60   ~ 0
ANA_OUT2
Text GLabel 5550 5450 0    60   Input ~ 0
CANH
Text GLabel 5550 5550 0    60   Input ~ 0
CANL
Text Label 4600 5250 0    60   ~ 0
DIN
Text Label 4600 5350 0    60   ~ 0
DOUT
$EndSCHEMATC