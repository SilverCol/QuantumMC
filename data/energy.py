from matplotlib import pyplot as plt
import numpy as np

points = 200
L = 1024
data = np.fromfile('cooling_' + str(L) + '_' + str(L) + '000_0.900000.bin')
data = np.reshape(data, (2, points), 'F')

plt.rcParams.update({'font.size': 15})
fig = plt.figure()
ax = fig.subplots()

ax.grid()
ax.set_xscale('log')
ax.plot(data[0], data[1])
ax.plot(data[0], [.5 for value in data[0]])
ax.set_title(str(L))
ax.set_ylabel('$\\langle H \\rangle$')
ax.set_xlabel('$\\beta$')

plt.show()
