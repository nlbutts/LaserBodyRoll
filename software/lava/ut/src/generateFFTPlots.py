#!/usr/bin/python
import matplotlib.pyplot as plt
import numpy as np
from scipy import signal

x=np.genfromtxt('fft_out.csv', delimiter=',')
x=x[:,0:2]

y=np.genfromtxt('fftr_out.csv', delimiter=',')
y=x[:,0:2]

X=np.sqrt(x[:,0]**2+x[:,1]**2)
Y=np.sqrt(y[:,0]**2+y[:,1]**2)

fig = plt.figure()
plt.subplot(211)
plt.plot(X)
plt.title('Complex FFT')
plt.subplot(212)
plt.plot(Y)
plt.title('Real FFT')
fig.savefig('Complex vs real FFT.png', bbox_inches='tight', dpi=300)
plt.show()
