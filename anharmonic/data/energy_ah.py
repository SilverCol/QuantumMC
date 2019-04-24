from matplotlib import pyplot as plt
import numpy as np

evalues = np.fromfile('evalues.bin')


def analitic(beta):
    return np.sum(evalues * np.exp(-beta * evalues))/np.sum(np.exp(-beta * evalues))


points = 200
L = 2048
data = np.fromfile('cooling_' + str(L) + '_200_100.bin')
data = np.reshape(data, (3, points), 'F')

plt.rcParams.update({'font.size': 15})
fig = plt.figure()
ax = fig.subplots()

ax.grid()
ax.set_yscale('log')
ax.set_ylim(.2, 2)
kinetic, = ax.plot(data[0], data[1])
potential, = ax.plot(data[0], data[2])
energy, = ax.plot(data[0], data[1] + data[2])
analitic, = ax.plot(data[0], [analitic(beta) for beta in data[0]])
limit, = ax.plot(data[0], [evalues[0] for val in data[0]], '-.')
half, = ax.plot(data[0], [evalues[0]/2 for val in data[0]], '-.')
ax.set_title('$M = ' + str(L) + ', \\lambda = 1$')
ax.set_ylabel('energy')
ax.set_xlabel('$\\beta$')
ax.legend((kinetic, potential, energy, analitic, limit, half),
          ('$\\langle T \\rangle$', '$\\langle V \\rangle$', '$\\langle H \\rangle$',
           '$\\langle H_a \\rangle$', '$E_0 = %.2f$' % evalues[0], '$\\frac{E_0}{2}$'),
          ncol=3)

plt.show()
