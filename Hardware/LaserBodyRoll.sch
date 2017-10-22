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
Sheet 1 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 1050 1050 2500 2000
U 59E70A39
F0 "Power" 60
F1 "Power.sch" 60
F2 "VCC" I R 3550 1500 60 
F3 "GND" I R 3550 1750 60 
F4 "12V" I R 3550 1250 60 
$EndSheet
$Sheet
S 4250 3400 2950 2000
U 59E951CD
F0 "Processor" 60
F1 "Processor.sch" 60
$EndSheet
$Sheet
S 7100 1050 2950 2050
U 59EA7C91
F0 "IO" 60
F1 "IO.sch" 60
F2 "12V" I L 7100 1250 60 
F3 "GND" I L 7100 1700 60 
F4 "VCC" I L 7100 1500 60 
F5 "CPU_ANA_OUT1" I L 7100 2850 60 
F6 "CPU_ANA_OUT2" I L 7100 3000 60 
F7 "CPU_DOUT1" I L 7100 1900 60 
F8 "CPU_DOUT2" I L 7100 2050 60 
F9 "CPU_DIN1" I L 7100 2250 60 
F10 "CPU_DIN2" I L 7100 2400 60 
F11 "CPU_ANA_IN1" I L 7100 2550 60 
F12 "CPU_ANA_IN2" I L 7100 2700 60 
$EndSheet
Wire Wire Line
	3550 1250 7100 1250
$EndSCHEMATC
