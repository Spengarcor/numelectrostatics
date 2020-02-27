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
import matplotlib.path as path
#import eBoundarySolver
from pylib import eBoundarySolver
#from PySide2.QtCore import Slots



class Electrostatics(QTabWidget):
    def __init__(self, parent=None):
        #QMainWindow.__init__(self)
        super(Electrostatics, self).__init__(parent)

        self.tab1 = QWidget(self)
        self.addTab(self.tab1, "Tab 1")
        self.figure = plt.figure(figsize=(10,5))
        self.resize(400,400)
        self.canvas = FigureCanvas(self.figure)
        self.filepath = ""

        layout = QVBoxLayout()
        layout.addWidget(self.canvas)
        self.tab1.setLayout(layout)

        self.inputline = QLineEdit(self)


        self.btn = QPushButton("Enter")
        self.btn.clicked.connect(lambda:self.plot())
        layout.addWidget(self.btn)


    def initUI(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width,self.height)
        button = QPushButton("Click me", self)
        button.setToolTip("Cheers")
        button.move(100, 70)
        self.show()

    def plot(self):
        self.filepath = self.inputline.text()
        self.canvas.figure.clf()
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
        filename = self.filepath
        #filename = "../Q2_SOR.csv"
        #filename = "../CSV_files/Q1.csv"
        data = np.loadtxt(filename, dtype=str, delimiter=';')
        data = np.delete(data, -1, axis=1)
        data = data.astype(np.float)
        self.values = np.array(data)
        self.data = data


    # Establishes the 2D grid to display
    def create_grid(self):
        self.X = np.linspace(0, len(self.data[0,:]), len(self.data[0,:])+1)
        self.Y = np.linspace(0, len(self.data[:,0]), len(self.data[:,0])+1)


    def show_scalar_field(self):
        plt.pcolormesh(self.X, self.Y, self.values, cmap=plt.get_cmap("bwr"))
        neg_patch = mpatches.Patch(color='red', label='-ve')
        pos_patch = mpatches.Patch(color='blue', label='+ve')
        plt.legend(handles=[neg_patch, pos_patch])


    def show_field_lines(self):
        dx, dy = np.gradient(self.data)
        dx = np.column_stack((dx[:,0], dx))
        dy = np.column_stack((dy[:,0], dy))
        #print(len(self.X))
        #print(len(self.Y[:-1]))
        #print(len(dx[0]))
        #print(len(dx))
        plt.streamplot(self.X, self.Y[:-1], dy, dx, color='black')



    def show_equipotential(self):
        #print("\n")
        #print(len(self.X))
        #print(len(self.Y))
        #eBoundaryPlotter.single_point(1,1,1)
        #print(len(self.values[0]))
        #print(len(self.values))
        plt.contour(self.X[:-1], self.Y[:-1], self.values, 15, colors="grey", linestyles="solid")



if __name__ == "__main__":
    app = QApplication(sys.argv)
    main = Electrostatics()
    main.show()
    sys.exit(app.exec_())
