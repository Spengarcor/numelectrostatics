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


X = [[i for i in range(len(Data[0,:]))] for j in range(len(Data[:,0]))]

Y = [[j for i in range(len(Data[0,:]))] for j in range(len(Data[:,0]))]

get_ipython().run_line_magic('matplotlib', 'notebook')
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(X, Y , Data)

