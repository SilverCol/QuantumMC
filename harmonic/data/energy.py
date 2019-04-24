from matplotlib import pyplot as plt
import numpy as np

points = 200
L = 1024
data = np.fromfile('cooling_' + str(L) + '_200_100.bin')
data = np.reshape(data, (3, points), 'F')

plt.rcParams.update({'font.size': 15})
fig = plt.figure()
ax = fig.subplots()

ax.grid()
ax.set_xscale('log')
kinetic, = ax.plot(data[0], data[1])
potential, = ax.plot(data[0], data[2])
energy, = ax.plot(data[0], data[1] + data[2])
analitic, = ax.plot(data[0], .5/np.tanh(data[0]/2))
ax.set_title(str(L))
ax.set_ylabel('$\\langle H \\rangle$')
ax.set_xlabel('$\\beta$')
ax.legend((kinetic, potential, energy, analitic),
          ('$\\langle T \\rangle$', '$\\langle V \\rangle$', '$\\langle H \\rangle$', '$\\langle H_a \\rangle$'))

plt.show()
