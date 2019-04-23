from matplotlib import pyplot as plt
import numpy as np

evalues = np.fromfile('evalues.bin')


def analitic(beta):
    return np.sum(evalues * np.exp(-beta * evalues))/np.sum(np.exp(-beta * evalues))


points = 200
L = 1024
data = np.fromfile('cooling_' + str(L) + '_200_100.bin')
data = np.reshape(data, (2, points), 'F')

plt.rcParams.update({'font.size': 15})
fig = plt.figure()
ax = fig.subplots()

ax.grid()
ax.set_xscale('log')
ax.plot(data[0], data[1])
ax.plot(data[0], [analitic(beta) for beta in data[0]])
ax.set_title(str(L))
ax.set_ylabel('$\\langle H \\rangle$')
ax.set_xlabel('$\\beta$')

plt.show()
