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
Sheet 4 4
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
U 1 1 59E9701E
P 6550 1750
F 0 "Q1" H 6741 1796 50  0000 L CNN
F 1 "Q_NPN_BCE" H 6741 1705 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 6750 1850 50  0001 C CNN
F 3 "" H 6550 1750 50  0001 C CNN
F 4 "MMBT3904FSCT-ND" H 6550 1750 60  0001 C CNN "Digikey"
	1    6550 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 59E9E700
P 6650 2300
F 0 "#PWR014" H 6650 2050 50  0001 C CNN
F 1 "GND" H 6655 2127 50  0000 C CNN
F 2 "" H 6650 2300 50  0001 C CNN
F 3 "" H 6650 2300 50  0001 C CNN
	1    6650 2300
	1    0    0    -1  
$EndComp
$Comp
L Q_NPN_BCE Q2
U 1 1 59E9EF10
P 7450 4850
F 0 "Q2" H 7641 4804 50  0000 L CNN
F 1 "Q_NPN_BCE" H 7641 4895 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 7650 4950 50  0001 C CNN
F 3 "" H 7450 4850 50  0001 C CNN
F 4 "MMBT3904FSCT-ND" H 7450 4850 60  0001 C CNN "Digikey"
	1    7450 4850
	1    0    0    1   
$EndComp
$Comp
L GND #PWR015
U 1 1 59EA03EA
P 7550 5650
F 0 "#PWR015" H 7550 5400 50  0001 C CNN
F 1 "GND" H 7555 5477 50  0000 C CNN
F 2 "" H 7550 5650 50  0001 C CNN
F 3 "" H 7550 5650 50  0001 C CNN
	1    7550 5650
	1    0    0    -1  
$EndComp
$Comp
L R R16
U 1 1 59EA0648
P 6350 4500
F 0 "R16" H 6420 4546 50  0000 L CNN
F 1 "24.3k" H 6420 4455 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 6280 4500 50  0001 C CNN
F 3 "" H 6350 4500 50  0001 C CNN
	1    6350 4500
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x02 J5
U 1 1 59EA07D1
P 5850 4100
F 0 "J5" V 5815 3962 50  0000 R CNN
F 1 "CONN_01X02" V 5724 3962 50  0000 R CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 5850 4100 50  0001 C CNN
F 3 "" H 5850 4100 50  0001 C CNN
	1    5850 4100
	0    -1   -1   0   
$EndComp
Text Label 5700 4850 0    60   ~ 0
DIN1
Text Label 9800 3150 0    60   ~ 0
DOUT1
Text Label 9800 3250 0    60   ~ 0
DOUT2
Text Label 9800 3350 0    60   ~ 0
DIN1
Text Label 9800 3450 0    60   ~ 0
DIN2
Text HLabel 6550 550  0    60   Input ~ 0
12V
$Comp
L R R15
U 1 1 59EA8B52
P 6050 1750
F 0 "R15" V 5950 1750 50  0000 L CNN
F 1 "24.3k" V 6150 1750 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 5980 1750 50  0001 C CNN
F 3 "" H 6050 1750 50  0001 C CNN
	1    6050 1750
	0    1    1    0   
$EndComp
Text HLabel 5700 1750 0    60   Input ~ 0
CPU_DOUT1
$Comp
L R R19
U 1 1 59EB3309
P 6950 1500
F 0 "R19" V 6850 1500 50  0000 L CNN
F 1 "24.3k" V 7050 1500 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 6880 1500 50  0001 C CNN
F 3 "" H 6950 1500 50  0001 C CNN
	1    6950 1500
	0    1    1    0   
$EndComp
$Comp
L R R17
U 1 1 59EB340E
P 6650 1300
F 0 "R17" V 6550 1300 50  0000 L CNN
F 1 "24.3k" V 6750 1300 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 6580 1300 50  0001 C CNN
F 3 "" H 6650 1300 50  0001 C CNN
	1    6650 1300
	-1   0    0    1   
$EndComp
Text Label 7400 1500 0    60   ~ 0
DOUT1
$Comp
L Q_NPN_BCE Q3
U 1 1 59EB3A69
P 9550 1750
F 0 "Q3" H 9741 1796 50  0000 L CNN
F 1 "Q_NPN_BCE" H 9741 1705 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 9750 1850 50  0001 C CNN
F 3 "" H 9550 1750 50  0001 C CNN
F 4 "MMBT3904FSCT-ND" H 9550 1750 60  0001 C CNN "Digikey"
	1    9550 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 59EB3A6F
P 9650 2300
F 0 "#PWR017" H 9650 2050 50  0001 C CNN
F 1 "GND" H 9655 2127 50  0000 C CNN
F 2 "" H 9650 2300 50  0001 C CNN
F 3 "" H 9650 2300 50  0001 C CNN
	1    9650 2300
	1    0    0    -1  
$EndComp
Text HLabel 9550 550  0    60   Input ~ 0
12V
$Comp
L R R22
U 1 1 59EB3A7B
P 9050 1750
F 0 "R22" V 8950 1750 50  0000 L CNN
F 1 "24.3k" V 9150 1750 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 8980 1750 50  0001 C CNN
F 3 "" H 9050 1750 50  0001 C CNN
	1    9050 1750
	0    1    1    0   
$EndComp
Text HLabel 8700 1750 0    60   Input ~ 0
CPU_DOUT2
$Comp
L R R26
U 1 1 59EB3A8B
P 9950 1500
F 0 "R26" V 9850 1400 50  0000 L CNN
F 1 "24.3k" V 9850 1600 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 9880 1500 50  0001 C CNN
F 3 "" H 9950 1500 50  0001 C CNN
	1    9950 1500
	0    1    1    0   
$EndComp
$Comp
L R R25
U 1 1 59EB3A97
P 9650 1300
F 0 "R25" V 9550 1300 50  0000 L CNN
F 1 "24.3k" V 9750 1300 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 9580 1300 50  0001 C CNN
F 3 "" H 9650 1300 50  0001 C CNN
	1    9650 1300
	-1   0    0    1   
$EndComp
Text Label 10400 1500 0    60   ~ 0
DOUT2
Text HLabel 5600 4300 0    60   Input ~ 0
12V
$Comp
L R R18
U 1 1 59EB4696
P 6750 4850
F 0 "R18" V 6957 4850 50  0000 C CNN
F 1 "24.3k" V 6866 4850 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 6680 4850 50  0001 C CNN
F 3 "" H 6750 4850 50  0001 C CNN
	1    6750 4850
	0    -1   -1   0   
$EndComp
$Comp
L R R20
U 1 1 59EB4799
P 7100 5000
F 0 "R20" H 7031 5046 50  0000 R CNN
F 1 "24.3k" H 7031 4955 50  0000 R CNN
F 2 "Resistors_SMD:R_0603" V 7030 5000 50  0001 C CNN
F 3 "" H 7100 5000 50  0001 C CNN
	1    7100 5000
	1    0    0    -1  
$EndComp
$Comp
L R R21
U 1 1 59EB53D7
P 7550 4350
F 0 "R21" H 7620 4396 50  0000 L CNN
F 1 "75k" H 7620 4305 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 7480 4350 50  0001 C CNN
F 3 "" H 7550 4350 50  0001 C CNN
	1    7550 4350
	1    0    0    -1  
$EndComp
$Comp
L Q_NPN_BCE Q4
U 1 1 59EB5910
P 10300 4850
F 0 "Q4" H 10491 4804 50  0000 L CNN
F 1 "Q_NPN_BCE" H 10491 4895 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 10500 4950 50  0001 C CNN
F 3 "" H 10300 4850 50  0001 C CNN
F 4 "MMBT3904FSCT-ND" H 10300 4850 60  0001 C CNN "Digikey"
	1    10300 4850
	1    0    0    1   
$EndComp
$Comp
L GND #PWR018
U 1 1 59EB5917
P 10400 5650
F 0 "#PWR018" H 10400 5400 50  0001 C CNN
F 1 "GND" H 10405 5477 50  0000 C CNN
F 2 "" H 10400 5650 50  0001 C CNN
F 3 "" H 10400 5650 50  0001 C CNN
	1    10400 5650
	1    0    0    -1  
$EndComp
$Comp
L R R23
U 1 1 59EB5925
P 9200 4500
F 0 "R23" H 9270 4546 50  0000 L CNN
F 1 "24.3k" H 9270 4455 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 9130 4500 50  0001 C CNN
F 3 "" H 9200 4500 50  0001 C CNN
	1    9200 4500
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x02 J6
U 1 1 59EB592B
P 8700 4100
F 0 "J6" V 8665 3962 50  0000 R CNN
F 1 "CONN_01X02" V 8574 3962 50  0000 R CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 8700 4100 50  0001 C CNN
F 3 "" H 8700 4100 50  0001 C CNN
	1    8700 4100
	0    -1   -1   0   
$EndComp
Text Label 8550 4850 0    60   ~ 0
DIN2
Text HLabel 8450 4300 0    60   Input ~ 0
12V
$Comp
L R R24
U 1 1 59EB5943
P 9600 4850
F 0 "R24" V 9807 4850 50  0000 C CNN
F 1 "24.3k" V 9716 4850 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 9530 4850 50  0001 C CNN
F 3 "" H 9600 4850 50  0001 C CNN
	1    9600 4850
	0    -1   -1   0   
$EndComp
$Comp
L R R27
U 1 1 59EB5949
P 9950 5000
F 0 "R27" H 9881 5046 50  0000 R CNN
F 1 "24.3k" H 9881 4955 50  0000 R CNN
F 2 "Resistors_SMD:R_0603" V 9880 5000 50  0001 C CNN
F 3 "" H 9950 5000 50  0001 C CNN
	1    9950 5000
	1    0    0    -1  
$EndComp
$Comp
L R R28
U 1 1 59EB5953
P 10400 4350
F 0 "R28" H 10470 4396 50  0000 L CNN
F 1 "75k" H 10470 4305 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 10330 4350 50  0001 C CNN
F 3 "" H 10400 4350 50  0001 C CNN
	1    10400 4350
	1    0    0    -1  
$EndComp
Text HLabel 7650 4600 2    60   Input ~ 0
CPU_DIN1
Text HLabel 10500 4600 2    60   Input ~ 0
CPU_DIN2
$Comp
L LMC6032 U3
U 1 1 59EBA988
P 1950 2450
F 0 "U3" H 1950 2947 60  0000 C CNN
F 1 "LMC6032" H 1950 2841 60  0000 C CNN
F 2 "SMD_Packages:SOIC-8-N" H 1950 2450 60  0001 C CNN
F 3 "" H 1950 2450 60  0001 C CNN
	1    1950 2450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 59EBF2A0
P 1550 800
F 0 "#PWR019" H 1550 550 50  0001 C CNN
F 1 "GND" H 1555 627 50  0000 C CNN
F 2 "" H 1550 800 50  0001 C CNN
F 3 "" H 1550 800 50  0001 C CNN
	1    1550 800 
	1    0    0    -1  
$EndComp
Text HLabel 1400 650  0    60   Input ~ 0
GND
Text Label 2250 7050 0    60   ~ 0
ANA_OUT1
Text Label 2250 7150 0    60   ~ 0
ANA_OUT2
Text Label 2250 7250 0    60   ~ 0
ANA_IN1
Text Label 2250 7350 0    60   ~ 0
ANA_IN2
$Comp
L GND #PWR021
U 1 1 59EC6B5F
P 2600 3600
F 0 "#PWR021" H 2600 3350 50  0001 C CNN
F 1 "GND" H 2605 3427 50  0000 C CNN
F 2 "" H 2600 3600 50  0001 C CNN
F 3 "" H 2600 3600 50  0001 C CNN
	1    2600 3600
	1    0    0    -1  
$EndComp
Text HLabel 2700 2200 2    60   Input ~ 0
12V
Text HLabel 7550 4100 1    60   Input ~ 0
+3V3
Text HLabel 10400 4100 1    60   Input ~ 0
+3V3
Text HLabel 1300 2350 0    60   Input ~ 0
CPU_ANA_OUT1
Text HLabel 1300 2550 0    60   Input ~ 0
CPU_ANA_OUT2
$Comp
L R R13
U 1 1 59ED1E9D
P 4300 2350
F 0 "R13" V 4200 2200 50  0000 L CNN
F 1 "24.3k" V 4200 2350 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 4230 2350 50  0001 C CNN
F 3 "" H 4300 2350 50  0001 C CNN
F 4 "311-24.3KHRCT-ND" V 4300 2350 60  0001 C CNN "Digikey"
	1    4300 2350
	0    1    1    0   
$EndComp
$Comp
L R R14
U 1 1 59ED1EFF
P 4300 2550
F 0 "R14" V 4200 2400 50  0000 L CNN
F 1 "24.3k" V 4200 2550 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 4230 2550 50  0001 C CNN
F 3 "" H 4300 2550 50  0001 C CNN
	1    4300 2550
	0    1    1    0   
$EndComp
$Comp
L C C13
U 1 1 59ED235D
P 2750 3200
F 0 "C13" H 2865 3246 50  0000 L CNN
F 1 "10n" H 2865 3155 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2788 3050 50  0001 C CNN
F 3 "" H 2750 3200 50  0001 C CNN
	1    2750 3200
	1    0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 59ED24B1
P 3150 3200
F 0 "C14" H 3265 3246 50  0000 L CNN
F 1 "10n" H 3265 3155 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 3188 3050 50  0001 C CNN
F 3 "" H 3150 3200 50  0001 C CNN
	1    3150 3200
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 59ED86A3
P 1300 4250
F 0 "R5" V 1093 4250 50  0000 C CNN
F 1 "24.3k" V 1184 4250 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1230 4250 50  0001 C CNN
F 3 "" H 1300 4250 50  0001 C CNN
	1    1300 4250
	0    1    1    0   
$EndComp
Text Label 700  4250 0    60   ~ 0
ANA_IN1
$Comp
L D_Zener D2
U 1 1 59ED9EBE
P 1750 4050
F 0 "D2" V 1704 4129 50  0000 L CNN
F 1 "D_Zener" V 1795 4129 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 1750 4050 50  0001 C CNN
F 3 "" H 1750 4050 50  0001 C CNN
F 4 "MMSZ5232B-FDICT-ND" V 1750 4050 60  0001 C CNN "Digikey"
	1    1750 4050
	0    1    1    0   
$EndComp
$Comp
L R R9
U 1 1 59ED9FE3
P 2900 4250
F 0 "R9" V 2693 4250 50  0000 C CNN
F 1 "24.3k" V 2784 4250 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2830 4250 50  0001 C CNN
F 3 "" H 2900 4250 50  0001 C CNN
	1    2900 4250
	0    1    1    0   
$EndComp
$Comp
L C C11
U 1 1 59EDA05B
P 2250 4500
F 0 "C11" H 2365 4546 50  0000 L CNN
F 1 "10n" H 2365 4455 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2288 4350 50  0001 C CNN
F 3 "" H 2250 4500 50  0001 C CNN
	1    2250 4500
	1    0    0    -1  
$EndComp
Text HLabel 1750 3800 1    60   Input ~ 0
+3V3
$Comp
L GND #PWR022
U 1 1 59EDC73D
P 1750 4750
F 0 "#PWR022" H 1750 4500 50  0001 C CNN
F 1 "GND" H 1755 4577 50  0000 C CNN
F 2 "" H 1750 4750 50  0001 C CNN
F 3 "" H 1750 4750 50  0001 C CNN
	1    1750 4750
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 59EDCBAC
P 1300 5800
F 0 "R6" V 1093 5800 50  0000 C CNN
F 1 "24.3k" V 1184 5800 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 1230 5800 50  0001 C CNN
F 3 "" H 1300 5800 50  0001 C CNN
	1    1300 5800
	0    1    1    0   
$EndComp
Text Label 700  5800 0    60   ~ 0
ANA_IN2
$Comp
L R R10
U 1 1 59EDCBC0
P 2950 5800
F 0 "R10" V 2743 5800 50  0000 C CNN
F 1 "24.3k" V 2834 5800 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2880 5800 50  0001 C CNN
F 3 "" H 2950 5800 50  0001 C CNN
	1    2950 5800
	0    1    1    0   
$EndComp
$Comp
L C C12
U 1 1 59EDCBC6
P 2250 6050
F 0 "C12" H 2365 6096 50  0000 L CNN
F 1 "10n" H 2365 6005 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 2288 5900 50  0001 C CNN
F 3 "" H 2250 6050 50  0001 C CNN
	1    2250 6050
	1    0    0    -1  
$EndComp
Text HLabel 1750 5350 1    60   Input ~ 0
+3V3
$Comp
L GND #PWR023
U 1 1 59EDCBD3
P 1750 6300
F 0 "#PWR023" H 1750 6050 50  0001 C CNN
F 1 "GND" H 1755 6127 50  0000 C CNN
F 2 "" H 1750 6300 50  0001 C CNN
F 3 "" H 1750 6300 50  0001 C CNN
	1    1750 6300
	1    0    0    -1  
$EndComp
$Comp
L D_Zener D3
U 1 1 59EDD4A5
P 1750 4500
F 0 "D3" V 1704 4579 50  0000 L CNN
F 1 "D_Zener" V 1795 4579 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 1750 4500 50  0001 C CNN
F 3 "" H 1750 4500 50  0001 C CNN
F 4 "MMSZ5232B-FDICT-ND" V 1750 4500 60  0001 C CNN "Digikey"
	1    1750 4500
	0    1    1    0   
$EndComp
$Comp
L D_Zener D4
U 1 1 59EDD51B
P 1750 5600
F 0 "D4" V 1704 5679 50  0000 L CNN
F 1 "D_Zener" V 1795 5679 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 1750 5600 50  0001 C CNN
F 3 "" H 1750 5600 50  0001 C CNN
F 4 "MMSZ5232B-FDICT-ND" V 1750 5600 60  0001 C CNN "Digikey"
	1    1750 5600
	0    1    1    0   
$EndComp
$Comp
L D_Zener D5
U 1 1 59EDD599
P 1750 6050
F 0 "D5" V 1704 6129 50  0000 L CNN
F 1 "D_Zener" V 1795 6129 50  0000 L CNN
F 2 "Diodes_SMD:D_SOD-123" H 1750 6050 50  0001 C CNN
F 3 "" H 1750 6050 50  0001 C CNN
F 4 "MMSZ5232B-FDICT-ND" V 1750 6050 60  0001 C CNN "Digikey"
	1    1750 6050
	0    1    1    0   
$EndComp
$Comp
L D_Zener D7
U 1 1 59EE2D57
P 3550 3200
F 0 "D7" V 3504 3279 50  0000 L CNN
F 1 "D_Zener" V 3595 3279 50  0000 L CNN
F 2 "Diodes_SMD:D_SMB" H 3550 3200 50  0001 C CNN
F 3 "" H 3550 3200 50  0001 C CNN
F 4 "MMSZ5232B-FDICT-ND" V 3550 3200 60  0001 C CNN "Digikey"
	1    3550 3200
	0    1    1    0   
$EndComp
$Comp
L D_Zener D8
U 1 1 59EE2DE3
P 4000 3200
F 0 "D8" V 3954 3279 50  0000 L CNN
F 1 "D_Zener" V 4045 3279 50  0000 L CNN
F 2 "Diodes_SMD:D_SMB" H 4000 3200 50  0001 C CNN
F 3 "" H 4000 3200 50  0001 C CNN
F 4 "MMSZ5232B-FDICT-ND" V 4000 3200 60  0001 C CNN "Digikey"
	1    4000 3200
	0    1    1    0   
$EndComp
Text Label 4550 2350 0    60   ~ 0
ANA_OUT1
Text Label 4550 2550 0    60   ~ 0
ANA_OUT2
$Comp
L R R7
U 1 1 59EE48F3
P 2600 4500
F 0 "R7" H 2530 4454 50  0000 R CNN
F 1 "DNI" H 2530 4545 50  0000 R CNN
F 2 "Resistors_SMD:R_0603" V 2530 4500 50  0001 C CNN
F 3 "" H 2600 4500 50  0001 C CNN
	1    2600 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	6650 1450 6650 1550
Wire Wire Line
	6650 1950 6650 2300
Connection ~ 6650 1500
Wire Wire Line
	5600 4850 6600 4850
Wire Wire Line
	7550 5050 7550 5650
Wire Wire Line
	7550 4500 7550 4650
Wire Wire Line
	5600 4300 5850 4300
Wire Wire Line
	5950 4300 6350 4300
Wire Wire Line
	6350 4300 6350 4350
Wire Wire Line
	6350 4650 6350 5050
Connection ~ 6350 4850
Wire Wire Line
	7550 4600 7650 4600
Connection ~ 7550 4600
Wire Wire Line
	7100 1500 7800 1500
Connection ~ 7250 1500
Wire Wire Line
	10350 3150 9600 3150
Wire Wire Line
	10350 3250 9600 3250
Wire Wire Line
	10350 3350 9600 3350
Wire Wire Line
	10350 3450 9600 3450
Wire Wire Line
	6800 1500 6650 1500
Wire Wire Line
	6200 1750 6350 1750
Wire Wire Line
	5700 1750 5900 1750
Wire Wire Line
	6550 550  6650 550 
Wire Wire Line
	6650 550  6650 1150
Wire Wire Line
	7250 2200 6650 2200
Connection ~ 6650 2200
Wire Wire Line
	9650 1450 9650 1550
Wire Wire Line
	9650 1950 9650 2300
Connection ~ 9650 1500
Wire Wire Line
	10100 1500 10800 1500
Connection ~ 10250 1500
Wire Wire Line
	9800 1500 9650 1500
Wire Wire Line
	9200 1750 9350 1750
Wire Wire Line
	8700 1750 8900 1750
Wire Wire Line
	9550 550  9650 550 
Wire Wire Line
	9650 550  9650 1150
Wire Wire Line
	10250 2200 9650 2200
Connection ~ 9650 2200
Wire Wire Line
	6350 5550 7550 5550
Connection ~ 7550 5550
Wire Wire Line
	6900 4850 7250 4850
Connection ~ 7100 4850
Wire Wire Line
	7100 5150 7100 5550
Connection ~ 7100 5550
Wire Wire Line
	7550 4100 7550 4200
Wire Wire Line
	8450 4850 9450 4850
Wire Wire Line
	10400 5050 10400 5650
Wire Wire Line
	10400 4500 10400 4650
Wire Wire Line
	8450 4300 8700 4300
Wire Wire Line
	8800 4300 9200 4300
Wire Wire Line
	9200 4300 9200 4350
Wire Wire Line
	9200 4650 9200 5050
Connection ~ 9200 4850
Wire Wire Line
	10400 4600 10500 4600
Connection ~ 10400 4600
Wire Wire Line
	9200 5550 10400 5550
Connection ~ 10400 5550
Wire Wire Line
	9750 4850 10100 4850
Connection ~ 9950 4850
Wire Wire Line
	9950 5150 9950 5550
Connection ~ 9950 5550
Wire Wire Line
	10400 4100 10400 4200
Wire Wire Line
	10250 1500 10250 1650
Wire Wire Line
	10250 1950 10250 2200
Wire Wire Line
	7250 1500 7250 1700
Wire Wire Line
	7250 2000 7250 2200
Wire Wire Line
	6350 5350 6350 5550
Wire Wire Line
	9200 5350 9200 5550
Wire Wire Line
	1400 650  1550 650 
Wire Wire Line
	1550 650  1550 800 
Wire Wire Line
	2750 7050 2200 7050
Wire Wire Line
	2750 7150 2200 7150
Wire Wire Line
	2750 7250 2200 7250
Wire Wire Line
	2750 7350 2200 7350
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
	1150 4250 650  4250
Wire Wire Line
	1450 4250 2750 4250
Wire Wire Line
	1750 4200 1750 4350
Connection ~ 1750 4250
Wire Wire Line
	2250 4350 2250 4250
Connection ~ 2250 4250
Wire Wire Line
	1750 3800 1750 3900
Wire Wire Line
	1750 4650 1750 4750
Wire Wire Line
	2250 4650 2250 4700
Wire Wire Line
	1750 4700 2600 4700
Connection ~ 1750 4700
Wire Wire Line
	3050 4250 3200 4250
Wire Wire Line
	1150 5800 650  5800
Wire Wire Line
	1450 5800 2800 5800
Wire Wire Line
	1750 5750 1750 5900
Connection ~ 1750 5800
Wire Wire Line
	2250 5900 2250 5800
Connection ~ 2250 5800
Wire Wire Line
	1750 5350 1750 5450
Wire Wire Line
	1750 6200 1750 6300
Wire Wire Line
	2250 6200 2250 6250
Wire Wire Line
	1750 6250 2600 6250
Connection ~ 1750 6250
Wire Wire Line
	3550 3350 3550 3500
Connection ~ 3550 3500
Wire Wire Line
	3550 2150 3550 3050
Connection ~ 3550 2550
Wire Wire Line
	4000 2150 4000 3050
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
Wire Wire Line
	2600 4350 2600 4250
Connection ~ 2600 4250
Wire Wire Line
	2600 4700 2600 4650
Connection ~ 2250 4700
$Comp
L R R8
U 1 1 59EE4C83
P 2600 6050
F 0 "R8" H 2530 6004 50  0000 R CNN
F 1 "DNI" H 2530 6095 50  0000 R CNN
F 2 "Resistors_SMD:R_0603" V 2530 6050 50  0001 C CNN
F 3 "" H 2600 6050 50  0001 C CNN
	1    2600 6050
	-1   0    0    1   
$EndComp
Wire Wire Line
	2600 5900 2600 5800
Connection ~ 2600 5800
Wire Wire Line
	2600 6250 2600 6200
Connection ~ 2250 6250
$Comp
L R R12
U 1 1 59EE6F2D
P 4000 2000
F 0 "R12" H 3930 1954 50  0000 R CNN
F 1 "DNI" H 3930 2045 50  0000 R CNN
F 2 "Resistors_SMD:R_0603" V 3930 2000 50  0001 C CNN
F 3 "" H 4000 2000 50  0001 C CNN
	1    4000 2000
	-1   0    0    1   
$EndComp
$Comp
L R R11
U 1 1 59EE6FE7
P 3550 2000
F 0 "R11" H 3480 1954 50  0000 R CNN
F 1 "DNI" H 3480 2045 50  0000 R CNN
F 2 "Resistors_SMD:R_0603" V 3480 2000 50  0001 C CNN
F 3 "" H 3550 2000 50  0001 C CNN
	1    3550 2000
	-1   0    0    1   
$EndComp
Text HLabel 4000 1700 1    60   Input ~ 0
CPU_ANA_OUT1
Text HLabel 3550 1700 1    60   Input ~ 0
CPU_ANA_OUT2
Wire Wire Line
	3550 1850 3550 1700
Wire Wire Line
	4000 1850 4000 1700
Text HLabel 3200 4250 2    60   Input ~ 0
CPU_ANA_IN1
Text HLabel 3250 5800 2    60   Input ~ 0
CPU_ANA_IN2
Wire Wire Line
	3250 5800 3100 5800
$Comp
L D_TVS D9
U 1 1 59F6C379
P 6350 5200
F 0 "D9" V 6304 5279 50  0000 L CNN
F 1 "D_TVS" V 6395 5279 50  0000 L CNN
F 2 "Diodes_SMD:D_SMB" H 6350 5200 50  0001 C CNN
F 3 "" H 6350 5200 50  0001 C CNN
F 4 "824520201" V 6350 5200 60  0001 C CNN "Partnum"
F 5 "732-9779-1-ND" V 6350 5200 60  0001 C CNN "Digikey"
	1    6350 5200
	0    1    1    0   
$EndComp
$Comp
L D_TVS D11
U 1 1 59F6D334
P 9200 5200
F 0 "D11" V 9154 5279 50  0000 L CNN
F 1 "D_TVS" V 9245 5279 50  0000 L CNN
F 2 "Diodes_SMD:D_SMB" H 9200 5200 50  0001 C CNN
F 3 "" H 9200 5200 50  0001 C CNN
F 4 "824520201" V 9200 5200 60  0001 C CNN "Partnum"
F 5 "732-9779-1-ND" V 9200 5200 60  0001 C CNN "Digikey"
	1    9200 5200
	0    1    1    0   
$EndComp
$Comp
L D_TVS D10
U 1 1 59F73D8D
P 7250 1850
F 0 "D10" V 7204 1929 50  0000 L CNN
F 1 "D_TVS" V 7295 1929 50  0000 L CNN
F 2 "Diodes_SMD:D_SMB" H 7250 1850 50  0001 C CNN
F 3 "" H 7250 1850 50  0001 C CNN
F 4 "824520201" V 7250 1850 60  0001 C CNN "Partnum"
F 5 "732-9779-1-ND" V 7250 1850 60  0001 C CNN "Digikey"
	1    7250 1850
	0    1    1    0   
$EndComp
$Comp
L D_TVS D12
U 1 1 59F74924
P 10250 1800
F 0 "D12" V 10204 1879 50  0000 L CNN
F 1 "D_TVS" V 10295 1879 50  0000 L CNN
F 2 "Diodes_SMD:D_SMB" H 10250 1800 50  0001 C CNN
F 3 "" H 10250 1800 50  0001 C CNN
F 4 "824520201" V 10250 1800 60  0001 C CNN "Partnum"
F 5 "732-9779-1-ND" V 10250 1800 60  0001 C CNN "Digikey"
	1    10250 1800
	0    1    1    0   
$EndComp
$Comp
L R R30
U 1 1 5A04301A
P 1950 1700
F 0 "R30" V 2157 1700 50  0000 C CNN
F 1 "30k" V 2066 1700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1880 1700 50  0001 C CNN
F 3 "" H 1950 1700 50  0001 C CNN
F 4 "311-30KGRCT-ND" V 1950 1700 60  0001 C CNN "Digikey"
	1    1950 1700
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 5A043102
P 1000 1700
F 0 "R1" V 793 1700 50  0000 C CNN
F 1 "10k" V 884 1700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 930 1700 50  0001 C CNN
F 3 "" H 1000 1700 50  0001 C CNN
F 4 "P10KGCT-ND" V 1000 1700 60  0001 C CNN "Digikey"
	1    1000 1700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR01
U 1 1 5A0433D9
P 750 1800
F 0 "#PWR01" H 750 1550 50  0001 C CNN
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
L R R29
U 1 1 5A043797
P 1850 3100
F 0 "R29" V 2057 3100 50  0000 C CNN
F 1 "30k" V 1966 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1780 3100 50  0001 C CNN
F 3 "" H 1850 3100 50  0001 C CNN
	1    1850 3100
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 5A043833
P 1000 3100
F 0 "R2" V 793 3100 50  0000 C CNN
F 1 "10k" V 884 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 930 3100 50  0001 C CNN
F 3 "" H 1000 3100 50  0001 C CNN
	1    1000 3100
	0    1    1    0   
$EndComp
$Comp
L GND #PWR02
U 1 1 5A0438C1
P 750 3150
F 0 "#PWR02" H 750 2900 50  0001 C CNN
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
L Conn_01x04 J3
U 1 1 5A120BAB
P 2950 7150
F 0 "J3" H 3030 7142 50  0000 L CNN
F 1 "Conn_01x04" H 3030 7051 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 2950 7150 50  0001 C CNN
F 3 "" H 2950 7150 50  0001 C CNN
	1    2950 7150
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J4
U 1 1 5A120E4D
P 10550 3250
F 0 "J4" H 10630 3242 50  0000 L CNN
F 1 "Conn_01x04" H 10630 3151 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 10550 3250 50  0001 C CNN
F 3 "" H 10550 3250 50  0001 C CNN
	1    10550 3250
	1    0    0    -1  
$EndComp
$EndSCHEMATC
