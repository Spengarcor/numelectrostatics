# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %%
from IPython import get_ipython

# %%
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

get_ipython().run_line_magic('matplotlib', 'inline')
get_ipython().run_line_magic('matplotlib', 'notebook')
plt.ion()


# %%
fname = "Q1.csv"

Data = np.loadtxt(fname, delimiter=';')


X = [[i for i in range(len(Data[0,:]))] for j in range(len(Data[:,0]))]

Y = [[j for i in range(len(Data[0,:]))] for j in range(len(Data[:,0]))]

get_ipython().run_line_magic('matplotlib', 'notebook')
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(X, Y , Data)



# %%
fname = "Q2.csv"

Data = np.loadtxt(fname, delimiter=';')


X = np.array([[i for i in range(len(Data[0,:]))] for j in range(len(Data[:,0]))])

Y = np.array([[j for i in range(len(Data[0,:]))] for j in range(len(Data[:,0]))])

get_ipython().run_line_magic('matplotlib', 'notebook')
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(X, Y , Data)

def analq1(V,a,b,centre_x,centre_y,x,y):
    """
    V - potential at the further boundary
    a - radius of inner circle
    b - radius of outer circle
    x, y - coordinates
"""
    return V*(np.log(np.sqrt((centre_x-x)**2+(centre_y-y)**2)/a)/np.log(b/a)

Analsol =  analq1(1.5,25,45,50,50,X,Y)

get_ipython().run_line_magic('matplotlib', 'notebook')
fig = plt.figure()
ax1 = fig.add_subplot(111, projection='3d')
ax1.plot_wireframe(X, Y , Analsol)
ax1.plot_wireframe(X, Y, Data-Analsol)
