# This Python file uses the following encoding: utf-8
import sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap, LinearSegmentedColormap
from colour import Color
import matplotlib.colors as colors
import matplotlib.cm as cm
import matplotlib.patches as mpatches
from matplotlib.figure import Figure
from PySide2.QtWidgets import *
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
import random
#from PySide2.QtCore import Slots


class Electrostatics(QTabWidget):
    def __init__(self, parent=None):
        #QMainWindow.__init__(self)
        super(Electrostatics, self).__init__(parent)

        self.tab1 = QWidget()
        self.addTab(self.tab1, "Tab 1")
        self.figure = plt.figure(figsize=(10,5))
        self.resize(400,400)
        self.canvas = FigureCanvas(self.figure)

        layout = QVBoxLayout()
        layout.addWidget(self.canvas)
        self.tab1.setLayout(layout)
        self.plot()

    def initUI(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width,self.height)
        button = QPushButton("Click me", self)
        button.setToolTip("Cheers")
        button.move(100, 70)
        self.show()

    def plot(self):
        self.get_display()
        #ax = self.figure.add_subplot(111)
        #ax.plot(self.data, 'r-')
        self.create_grid()
        self.show_scalar_field()
        self.show_field_lines()
        self.show_equipotential()
        self.canvas.draw()

    # Reads from a specified csv file to a matrix
    def get_display(self):
        #filename = input("Enter a csv file name or path:\n")
        filename = "../CSV_files/Q1.csv"
        data = np.loadtxt(filename, dtype=str, delimiter=';')
        data = np.delete(data, -1, axis=1)
        data = data.astype(np.float)
        self.values = np.array(data)
        self.data = data


    # Establishes the 2D grid to display
    def create_grid(self):
        self.X = np.linspace(0, len(self.data[0,:]), len(self.data[0,:]))
        self.Y = np.linspace(0, len(self.data[:,0]), len(self.data[:,0]))


    def show_scalar_field(self):
        plt.pcolormesh(self.X, self.Y, self.values, cmap=plt.get_cmap("bwr"))
        neg_patch = mpatches.Patch(color='red', label='+ve')
        pos_patch = mpatches.Patch(color='blue', label='-ve')
        plt.legend(handles=[neg_patch, pos_patch])


    def show_field_lines(self):
        graddata_x = []
        graddata_y = []
        for row in self.values:
            gradrow = []
            for x in range(1,len(row)-1):
                gradrow.append(row[x+1] - row[x])
            graddata_x.append(gradrow)

        graddata_x = np.array(graddata_x)
        graddata_x = np.column_stack((graddata_x.transpose()[0] , np.column_stack((graddata_x, graddata_x.transpose()[-1]))))

        for column in self.values.T:
            gradrow = []
            for y in range(1,len(column)-1):
                gradrow.append(column[y + 1] - column[y])
            graddata_y.append(gradrow)

        graddata_y = np.array(graddata_y)
        graddata_y = np.column_stack((graddata_y.transpose()[0], np.column_stack((graddata_y, graddata_y.transpose()[-1]))))

        plt.streamplot(self.X, self.Y, graddata_x, graddata_y.transpose(), color="black", density=0.5)


    def show_equipotential(self):
        plt.contour(self.X, self.Y, self.values, 15, colors="grey", linestyles="solid")


def main():
    print("hi")
    app = QApplication(sys.argv)
    main = Electrostatics()
    main.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    print("hi")
    main()
