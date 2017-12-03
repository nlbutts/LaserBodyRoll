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
Sheet 2 4
Title "POV Base Controller"
Date "2016-09-25"
Rev "R00"
Comp "Nick Butts"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L PWR_FLAG #FLG01
U 1 1 57E830AD
P 9450 1350
F 0 "#FLG01" H 9450 1445 50  0001 C CNN
F 1 "PWR_FLAG" H 9450 1530 50  0000 C CNN
F 2 "" H 9450 1350 50  0000 C CNN
F 3 "" H 9450 1350 50  0000 C CNN
	1    9450 1350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 57E83120
P 9450 1550
F 0 "#PWR04" H 9450 1300 50  0001 C CNN
F 1 "GND" H 9450 1400 50  0000 C CNN
F 2 "" H 9450 1550 50  0000 C CNN
F 3 "" H 9450 1550 50  0000 C CNN
	1    9450 1550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 57E8605E
P 6500 3400
F 0 "#PWR06" H 6500 3150 50  0001 C CNN
F 1 "GND" H 6500 3250 50  0000 C CNN
F 2 "" H 6500 3400 50  0000 C CNN
F 3 "" H 6500 3400 50  0000 C CNN
	1    6500 3400
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 57E8A33E
P 6750 2300
F 0 "R4" V 6830 2300 50  0000 C CNN
F 1 "525k" V 6750 2300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 6680 2300 50  0001 C CNN
F 3 "" H 6750 2300 50  0000 C CNN
F 4 "311-523KHRCT-ND" V 6750 2300 60  0001 C CNN "Digikey"
	1    6750 2300
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 57E8AB6F
P 6750 2850
F 0 "R3" V 6830 2850 50  0000 C CNN
F 1 "100k" V 6750 2850 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 6680 2850 50  0001 C CNN
F 3 "" H 6750 2850 50  0000 C CNN
F 4 "P100KGCT-ND" V 6750 2850 60  0001 C CNN "Digikey"
	1    6750 2850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 57E8C888
P 2150 6300
F 0 "#PWR08" H 2150 6050 50  0001 C CNN
F 1 "GND" H 2150 6150 50  0000 C CNN
F 2 "" H 2150 6300 50  0000 C CNN
F 3 "" H 2150 6300 50  0000 C CNN
	1    2150 6300
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG09
U 1 1 57E8D032
P 10300 1350
F 0 "#FLG09" H 10300 1445 50  0001 C CNN
F 1 "PWR_FLAG" H 10300 1530 50  0000 C CNN
F 2 "" H 10300 1350 50  0000 C CNN
F 3 "" H 10300 1350 50  0000 C CNN
	1    10300 1350
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR010
U 1 1 57E8D088
P 10300 1600
F 0 "#PWR010" H 10300 1450 50  0001 C CNN
F 1 "+12V" H 10300 1740 50  0000 C CNN
F 2 "" H 10300 1600 50  0000 C CNN
F 3 "" H 10300 1600 50  0000 C CNN
	1    10300 1600
	-1   0    0    1   
$EndComp
$Comp
L C C4
U 1 1 57EC6C01
P 4650 2300
F 0 "C4" H 4675 2400 50  0000 L CNN
F 1 "10u" H 4675 2200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4688 2150 50  0001 C CNN
F 3 "" H 4650 2300 50  0000 C CNN
F 4 "490-12737-1-ND" H 4650 2300 60  0001 C CNN "DIGIKEY"
	1    4650 2300
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 57EC6EE3
P 4900 2600
F 0 "C5" H 4925 2700 50  0000 L CNN
F 1 "3.3n" H 4925 2500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 4938 2450 50  0001 C CNN
F 3 "" H 4900 2600 50  0000 C CNN
F 4 "1276-1790-1-ND" H 4900 2600 60  0001 C CNN "Digikey"
F 5 "CL10C3R3CB8NNNC" H 4900 2600 60  0001 C CNN "Partnum"
	1    4900 2600
	1    0    0    -1  
$EndComp
$Comp
L CP C7
U 1 1 57EC9160
P 7850 2150
F 0 "C7" H 7875 2250 50  0000 L CNN
F 1 "22u" H 7875 2050 50  0000 L CNN
F 2 "SMD_Packages:SMD-1210_Pol" H 7888 2000 50  0001 C CNN
F 3 "" H 7850 2150 50  0000 C CNN
F 4 "478-9063-1-ND" H 7850 2150 60  0001 C CNN "DIGIKEY"
F 5 "TPSB226K006R0375" H 7850 2150 60  0001 C CNN "PartNum"
	1    7850 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 1350 9450 1550
Wire Wire Line
	3750 1900 5300 1900
Wire Wire Line
	4650 1900 4650 2150
Connection ~ 4650 1900
Wire Wire Line
	4650 3300 4650 2450
Connection ~ 4650 3300
Wire Wire Line
	10300 1600 10300 1350
Wire Wire Line
	4900 3300 4900 2750
Connection ~ 4900 3300
Wire Wire Line
	7850 3300 7850 2300
Connection ~ 7850 3300
$Comp
L TEST_1P W14
U 1 1 584868C9
P 2150 6200
F 0 "W14" H 2150 6470 50  0000 C CNN
F 1 "TEST_1P" H 2150 6400 50  0000 C CNN
F 2 "Connectors_TestPoints:Test_Point_Pad_d2.0mm" H 2350 6200 50  0001 C CNN
F 3 "" H 2350 6200 50  0000 C CNN
	1    2150 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 6200 2150 6300
$Comp
L Conn_01x02 J1
U 1 1 59E71894
P 3000 2450
F 0 "J1" H 3078 2491 50  0000 L CNN
F 1 "CONN_01X02" H 3078 2400 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 3000 2450 50  0001 C CNN
F 3 "" H 3000 2450 50  0001 C CNN
F 4 "277-1667-ND" H 3000 2450 60  0001 C CNN "Digikey"
	1    3000 2450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3950 3300 3950 2550
Wire Wire Line
	3950 2550 3200 2550
Connection ~ 4350 3300
Connection ~ 3950 1900
Text HLabel 8000 1900 2    60   Input ~ 0
+5V
Text HLabel 8050 3300 2    60   Input ~ 0
GND
Text HLabel 3750 1900 0    60   Input ~ 0
12V
Wire Wire Line
	4350 1900 4350 2650
Wire Wire Line
	4350 2950 4350 3300
Wire Wire Line
	3950 1900 3950 2450
Wire Wire Line
	3350 2450 3200 2450
Wire Wire Line
	3950 2450 3650 2450
$Comp
L D_TVS D15
U 1 1 59F6AB56
P 4350 2800
F 0 "D15" V 4304 2879 50  0000 L CNN
F 1 "D_TVS" V 4395 2879 50  0000 L CNN
F 2 "Diodes_SMD:D_SMB" H 4350 2800 50  0001 C CNN
F 3 "" H 4350 2800 50  0001 C CNN
F 4 "824520201" V 4350 2800 60  0001 C CNN "Partnum"
F 5 "732-9779-1-ND" V 4350 2800 60  0001 C CNN "Digikey"
	1    4350 2800
	0    1    1    0   
$EndComp
$Comp
L D D1
U 1 1 59F6AF4B
P 3500 2450
F 0 "D1" H 3500 2550 50  0000 C CNN
F 1 "STPS2L40" H 3500 2350 50  0000 C CNN
F 2 "Diodes_SMD:D_SMB" H 3500 2450 50  0001 C CNN
F 3 "" H 3500 2450 50  0000 C CNN
F 4 "497-5574-1-ND" H 3500 2450 60  0001 C CNN "DIGIKEY"
F 5 "STPS2L40U" H 3500 2450 60  0001 C CNN "PartNum"
	1    3500 2450
	-1   0    0    1   
$EndComp
$Comp
L TPS821XX U1
U 1 1 5A04433C
P 5850 2150
F 0 "U1" H 5850 2737 60  0000 C CNN
F 1 "TPS821XX" H 5850 2631 60  0000 C CNN
F 2 "KicadFootprint:TPS821XX" H 5850 2150 60  0001 C CNN
F 3 "" H 5850 2150 60  0001 C CNN
	1    5850 2150
	1    0    0    -1  
$EndComp
Connection ~ 4350 1900
Wire Wire Line
	5300 2050 5200 2050
Wire Wire Line
	5200 2050 5200 1900
Connection ~ 5200 1900
Wire Wire Line
	5300 2250 4900 2250
Wire Wire Line
	4900 2250 4900 2450
Wire Wire Line
	6500 2550 6500 3400
Connection ~ 6500 3300
Wire Wire Line
	6500 2550 6400 2550
Wire Wire Line
	6400 2400 6600 2400
Wire Wire Line
	6600 2400 6600 2600
Wire Wire Line
	6600 2600 6750 2600
Wire Wire Line
	6750 2450 6750 2700
Connection ~ 6750 2600
Wire Wire Line
	6750 3000 6750 3300
Connection ~ 6750 3300
Wire Wire Line
	6400 2050 6750 2050
Wire Wire Line
	6750 1900 6750 2150
Wire Wire Line
	6400 1900 8000 1900
Connection ~ 6750 2050
Wire Wire Line
	7850 1900 7850 2000
Connection ~ 6750 1900
Connection ~ 7850 1900
Wire Wire Line
	3950 3300 8050 3300
NoConn ~ 6400 2250
$EndSCHEMATC
