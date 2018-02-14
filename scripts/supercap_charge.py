# -*- coding: utf-8 -*-
"""
Created on Wed Feb 14 05:47:58 2018

@author: Nick Butts

Super cap charging times
"""

import matplotlib.pyplot as plt
import numpy as np

'''
Constants
'''
Cs = 1.5
Ilim = 0.1

Vi = 3.3
Vfm = 0.3

Ts = 1e-3
simTime = 120

'''
Calculations
'''

Vsc = Vi - Vfm

joules = 0.5 * Cs * Vsc**2
coloumbs = Cs * Vsc

rlimit = Vsc / Ilim
rlimit = 5

charge = 0
data = []
voltage = []
current = []
t = np.arange(simTime/Ts)
t *= Ts

coloumbLimit = np.ones(len(t)) * coloumbs 

for i in t:
    scVoltage = 0.5 * (charge**2 / Cs)
    currentFlow = (Vi - scVoltage) / rlimit    
    data.append(charge)
    voltage.append(scVoltage)
    current.append(scVoltage/rlimit)
    charge += currentFlow * Ts
       
plt.plot(t, data, label='Charge')    
plt.plot(t, coloumbLimit, label='Limit')
plt.plot(t, voltage, label='Voltage')
plt.plot(t, current, label='Current')
plt.title('Charge on Supercap vs time')
plt.xlabel('Time [seconds]')
plt.ylabel('Charge [Coloumbs]')
plt.grid()
plt.legend()