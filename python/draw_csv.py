#import numpy as np
#import matplotlib.pyplot as plt
#from mpl_toolkits.toolkits.mplot3d import Axes3D

fname = input("csv file name or path:\n")

Data = np.loadtxt(fname, dtype=<class 'double'>, delimiter=';')

X = [[i for i in range(len(Data[0,:]))] for j in range(len(Data[:,0]))]

Y = [[j for i in range(len(Data[0,:]))] for j in range(len(Data[:,0]))]

fig = plt.figure()
ax = fig.add_subplot(111, projectoin='3d')
ax.plot_wireframe(X, Y , Data)
fig.savefig("a_name.jpg")
