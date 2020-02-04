import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap, LinearSegmentedColormap
from colour import Color
import matplotlib.colors as colors
import matplotlib.cm as cm
import matplotlib.patches as mpatches

# Reads from a specified csv file to a matrix
filename = input("Enter a csv file name or path:\n")
data = np.loadtxt(filename, dtype=str, delimiter=';')
data = np.delete(data, -1, axis=1)
data = data.astype(np.float)
values = np.array(data)


# Establishes the 2D grid to display
X = np.linspace(0, len(data[0,:]), len(data[0,:]))
Y = np.linspace(0, len(data[:,0]), len(data[:,0]))


def show_scalar_field(X, Y, values):
    plt.pcolormesh(X, Y, values, cmap=plt.get_cmap("bwr"))
    neg_patch = mpatches.Patch(color='red', label='+ve')
    pos_patch = mpatches.Patch(color='blue', label='-ve')
    plt.legend(handles=[neg_patch, pos_patch])


def show_field_lines(X, Y, values):
    graddata_x = []
    graddata_y = []
    for row in values:
        gradrow = []
        for x in range(1,len(row)-1):
            gradrow.append(row[x+1] - row[x])
        graddata_x.append(gradrow)

    graddata_x = np.array(graddata_x)
    graddata_x = np.column_stack((graddata_x.transpose()[0] , np.column_stack((graddata_x, graddata_x.transpose()[-1]))))

    for column in values.T:
        gradrow = []
        for y in range(1,len(column)-1):
            gradrow.append(column[y + 1] - column[y])
        graddata_y.append(gradrow)

    graddata_y = np.array(graddata_y)
    graddata_y = np.column_stack((graddata_y.transpose()[0], np.column_stack((graddata_y, graddata_y.transpose()[-1]))))

    plt.streamplot(X, Y, graddata_x, graddata_y.transpose(), color="black", density=0.5)


def show_equipotential(X, Y, values):
    plt.contour(X, Y, values, 15, colors="grey", linestyles="solid")


show_scalar_field(X, Y, values)
show_equipotential(X, Y, values)
show_field_lines(X, Y, values)
plt.show()
