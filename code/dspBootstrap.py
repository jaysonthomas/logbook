import matplotlib.pyplot as plt
import numpy as np

def simpleRemoveNoise(freq, fpass):
  filteredFreq = np.empty(len(freq))

  for i, f in enumerate(freq):
    if (fpass-50 < i < fpass+50):
      if (f < 1):
        filteredFreq[i] = 0
    else:
      filteredFreq[i] = 0

    # filteredFreq = np.array([f if (fpass-50<i)])
  return filteredFreq

f = 1000
fnoise = 50
fs = 48000 # sampling frequency
nSamples = fs

t = np.array([x/fs for x in range(nSamples)])
signal = np.sin(2*np.pi*f*t)
noise = np.sin(2*np.pi*fnoise*t)
y = signal + noise

fftOutput = np.fft.fft(y)
fftFreq = np.abs(fftOutput)

filteredFreq = simpleRemoveNoise(fftFreq, f)

# 1- FFT
plt.subplot(2,1,1) # subplot(nrows, ncols, plotIndex)
# If we are sampling at fs, at most, we can only recreate
# 0 to fs/2 frequencies. I think the remainder of the plot,
# fs/2 onwards, is related to the complex conjugate.
plt.xlim(0, f+20)
plt.xlabel('Time (s)')
plt.ylabel('Amplitude')
# plt.plot(t[:5000], y[:5000])
plt.plot(filteredFreq)

# 2 - signal
plt.subplot(2,1,2)
plt.xlabel('Time (s)')
plt.ylabel('Amplitude')
plt.plot(t[:5000], y[:5000])

plt.show()