import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap, LinearSegmentedColormap
from colour import Color
import matplotlib.colors as colors
import matplotlib.cm as cm


filename = input("Enter a csv file name or path:\n")

data = np.loadtxt(filename, dtype=str, delimiter=';')
data = np.delete(data, -1, axis=1)
data = data.astype(np.float)
print(data)

#min = min(list(map(min, data)))
#data = data - min

print(data)
X = np.linspace(0, len(data[0,:]), len(data[0,:]))
Y = np.linspace(0, len(data[:,0]), len(data[:,0]))
values = np.array(data)
print(values)
print(X)
print(Y)

def scalar_field(X, Y, values):
    plt.pcolormesh(X, Y, values, cmap=plt.get_cmap("bwr"))
    plt.show()

scalar_field(X, Y, values)
