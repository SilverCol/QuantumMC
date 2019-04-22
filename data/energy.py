from matplotlib import pyplot as plt
import numpy as np
from scipy import optimize as opt

points = 200
L = 128
data = np.fromfile('cooling_' + str(L) + '_1280000_0.500000.bin')
data = np.reshape(data, (2, points), 'F')
print(data)

plt.rcParams.update({'font.size': 20})
fig = plt.figure()
ax = fig.subplots()

plt.show()
