import numpy as np
import matplotlib.pyplot as plt
import argparse
import re
from os import listdir
from os import listdir
from os.path import isfile, join


"""The purpose of this file is to graph the input sine and output of a
bandpass filter
"""

def plotAudio(files):
    f, ax = plt.subplots(len(files)/2, 1)
    i = 0
    title = ''
    for i in range(0, len(files)/2):
        m = re.search('sin_(.*).csv', files[i*2])
        if m:
            title = m.group(1)
        x = np.loadtxt(files[i*2])
        y = np.loadtxt(files[(i*2)+1])
        data = np.vstack((x,y))
        ax[i].plot(data.T)
        ax[i].set_title(title)
        i += 1

    plt.legend(['unfiltered', 'filtered'])
    plt.grid()
    plt.show()

def plotFFT(x, y):
    fs = 48000
    nfft = 256
    X=np.fft.fft(x, nfft)
    Y=np.fft.fft(y, nfft)
    W=np.linspace(0, fs/2, len(X)/2+1)
    # Get abs value of half + 1
    X = np.abs(X[0:int(len(X)/2+1)])
    Y = np.abs(Y[0:int(len(Y)/2+1)])
    # Norm
    #X = X / np.max(X)
    #Y = Y / np.max(X) # Norm to X
    # Log plot
    X = 20 * np.log(X)
    Y = 20 * np.log(Y)
    plt.figure()
    plt.plot(W,X,W,Y)
    plt.grid()
    plt.legend(['unfiltered', 'filtered'])
    plt.xlabel("Frequency (Hz)")
    plt.show()

if __name__ == "__main__":
    infoStr = """The purpose of this file is to graph the input sine and output of a
    bandpass filter.
    usage: python plot_filter_test.py <input sine> <filter sine>
    """

    # parser = argparse.ArgumentParser(description=infoStr)
    # parser.add_argument('inputs',
    #                     metavar='I',
    #                     type=str,
    #                     nargs='+',
    #                     help='The raw sine input file, the other file will be automatically detected')

    # args = parser.parse_args()
    mypath = '.'
    onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f))]

    sin_files = []
    for f in onlyfiles:
        m = re.search('sin_.*', f)
        if m:
            sin_files.append(m.group(0))

    sin_files = sorted(sin_files)
    print(sin_files)

    plotAudio(sin_files)

    # print('Loading raw audio file {0}'.format(args.inputs[0]))

    # m = re.search('(.*)\.csv', args.inputs[0])
    # filteredAudio = m.group(1)
    # filteredAudio += 'f.csv'

    # print('Loading raw audio file {0}'.format(filteredAudio))

    # x = np.loadtxt(args.inputs[0]);
    # y = np.loadtxt(filteredAudio);

    # plotAudio(x, y)
    # plotFFT(x, y)