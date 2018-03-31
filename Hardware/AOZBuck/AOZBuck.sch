EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
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
LIBS:dk_Fixed-Inductors
LIBS:dk_PMIC-Voltage-Regulators-DC-DC-Switching-Regulators
LIBS:AOZBuck-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L AOZ1280CI U1
U 1 1 5ABE73B3
P 5750 3350
F 0 "U1" H 5650 3500 60  0000 C CNN
F 1 "AOZ1280CI" H 6150 3600 60  0000 C CNN
F 2 "digikey-footprints:SOT-23-6" H 5950 3550 60  0001 L CNN
F 3 "http://aosmd.com/res/data_sheets/AOZ1280CI.pdf" H 5950 3650 60  0001 L CNN
F 4 "785-1277-1-ND" H 5950 3750 60  0001 L CNN "Digi-Key_PN"
F 5 "AOZ1280CI" H 5950 3850 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 5950 3950 60  0001 L CNN "Category"
F 7 "PMIC - Voltage Regulators - DC DC Switching Regulators" H 5950 4050 60  0001 L CNN "Family"
F 8 "http://aosmd.com/res/data_sheets/AOZ1280CI.pdf" H 5950 4150 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/alpha-omega-semiconductor-inc/AOZ1280CI/785-1277-1-ND/2769845" H 5950 4250 60  0001 L CNN "DK_Detail_Page"
F 10 "IC REG BUCK ADJ 1.2A SOT23-6" H 5950 4350 60  0001 L CNN "Description"
F 11 "Alpha & Omega Semiconductor Inc." H 5950 4450 60  0001 L CNN "Manufacturer"
F 12 "Active" H 5950 4550 60  0001 L CNN "Status"
	1    5750 3350
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5ABE745E
P 4700 3050
F 0 "C1" H 4725 3150 50  0000 L CNN
F 1 "10u" H 4725 2950 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210_HandSoldering" H 4738 2900 50  0001 C CNN
F 3 "" H 4700 3050 50  0001 C CNN
	1    4700 3050
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5ABE74CD
P 7100 3750
F 0 "C3" H 7125 3850 50  0000 L CNN
F 1 "10u" H 7125 3650 50  0000 L CNN
F 2 "Capacitors_SMD:C_1210_HandSoldering" H 7138 3600 50  0001 C CNN
F 3 "" H 7100 3750 50  0001 C CNN
	1    7100 3750
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5ABE7501
P 6850 3650
F 0 "R1" V 6930 3650 50  0000 C CNN
F 1 "49.9k" V 6850 3650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6780 3650 50  0001 C CNN
F 3 "" H 6850 3650 50  0001 C CNN
	1    6850 3650
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5ABE75B4
P 6850 4050
F 0 "R2" V 6930 4050 50  0000 C CNN
F 1 "9.53k" V 6850 4050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6780 4050 50  0001 C CNN
F 3 "" H 6850 4050 50  0001 C CNN
	1    6850 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5ABE75E0
P 5850 4300
F 0 "#PWR01" H 5850 4050 50  0001 C CNN
F 1 "GND" H 5850 4150 50  0000 C CNN
F 2 "" H 5850 4300 50  0001 C CNN
F 3 "" H 5850 4300 50  0001 C CNN
	1    5850 4300
	1    0    0    -1  
$EndComp
$Comp
L L L1
U 1 1 5ABE75FE
P 6550 3450
F 0 "L1" V 6500 3450 50  0000 C CNN
F 1 "4.7u" V 6625 3450 50  0000 C CNN
F 2 "Inductors_SMD:L_1210_HandSoldering" H 6550 3450 50  0001 C CNN
F 3 "" H 6550 3450 50  0001 C CNN
	1    6550 3450
	0    -1   -1   0   
$EndComp
$Comp
L C C2
U 1 1 5ABE766D
P 5500 3000
F 0 "C2" H 5525 3100 50  0000 L CNN
F 1 "10n" H 5525 2900 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5538 2850 50  0001 C CNN
F 3 "" H 5500 3000 50  0001 C CNN
	1    5500 3000
	0    1    1    0   
$EndComp
$Comp
L D_Schottky D1
U 1 1 5ABE76FA
P 6400 3650
F 0 "D1" H 6400 3750 50  0000 C CNN
F 1 "D_Schottky" H 6400 3550 50  0000 C CNN
F 2 "Diodes_SMD:D_SOD-123" H 6400 3650 50  0001 C CNN
F 3 "" H 6400 3650 50  0001 C CNN
	1    6400 3650
	0    1    1    0   
$EndComp
$Comp
L Conn_01x02 J1
U 1 1 5ABE7756
P 4100 2850
F 0 "J1" H 4100 2950 50  0000 C CNN
F 1 "Conn_01x02" H 4100 2650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 4100 2850 50  0001 C CNN
F 3 "" H 4100 2850 50  0001 C CNN
	1    4100 2850
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x02 J2
U 1 1 5ABE780E
P 7650 3450
F 0 "J2" H 7650 3550 50  0000 C CNN
F 1 "Conn_01x02" H 7650 3250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 7650 3450 50  0001 C CNN
F 3 "" H 7650 3450 50  0001 C CNN
	1    7650 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3450 5250 3450
Wire Wire Line
	5250 3450 5250 3850
Wire Wire Line
	5850 4250 7450 4250
Wire Wire Line
	5850 3850 5850 4300
Connection ~ 5850 4250
$Comp
L GND #PWR02
U 1 1 5ABE7979
P 4500 3250
F 0 "#PWR02" H 4500 3000 50  0001 C CNN
F 1 "GND" H 4500 3100 50  0000 C CNN
F 2 "" H 4500 3250 50  0001 C CNN
F 3 "" H 4500 3250 50  0001 C CNN
	1    4500 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 2950 4500 2950
Wire Wire Line
	4300 2850 5850 2850
Wire Wire Line
	5850 2850 5850 3050
Wire Wire Line
	4500 2950 4500 3250
Wire Wire Line
	4700 3200 4500 3200
Connection ~ 4500 3200
Wire Wire Line
	6400 4250 6400 3800
Wire Wire Line
	6400 3000 6400 3500
Wire Wire Line
	6250 3450 6400 3450
Connection ~ 6400 3450
Wire Wire Line
	7100 4250 7100 3900
Connection ~ 6400 4250
Wire Wire Line
	6700 3450 7450 3450
Wire Wire Line
	7100 3450 7100 3600
Connection ~ 7100 3450
Wire Wire Line
	7450 4250 7450 3550
Connection ~ 7100 4250
Wire Wire Line
	5650 3000 6400 3000
Wire Wire Line
	5350 3350 5050 3350
Wire Wire Line
	5050 3350 5050 3000
Wire Wire Line
	5050 3000 5350 3000
Wire Wire Line
	6850 3500 6850 3500
Wire Wire Line
	6850 3500 6850 3450
Connection ~ 6850 3450
Wire Wire Line
	6850 3800 6850 3900
Wire Wire Line
	6850 4200 6850 4250
Connection ~ 6850 4250
Wire Wire Line
	5250 3850 6850 3850
Connection ~ 6850 3850
Wire Wire Line
	5350 3550 4950 3550
Wire Wire Line
	4950 3550 4950 2850
Connection ~ 4950 2850
Wire Wire Line
	4700 2900 4700 2850
Connection ~ 4700 2850
$EndSCHEMATC
