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
import eBoundarySolver
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
        print(len(self.X))
        print(len(self.Y[:-1]))
        print(len(dx[0]))
        print(len(dx))
        plt.streamplot(self.X, self.Y[:-1], dy, dx, color='black')

    def show_field_line(self):
        graddata_x = []
        graddata_y = []
        for row in self.values:
            gradrow = []
            for x in range(1,len(row)-1):
                gradrow.append(row[x+1] - row[x])
            graddata_x.append(gradrow)

        graddata_x = np.array(graddata_x)
        graddata_x = np.column_stack((graddata_x.transpose()[0] , np.column_stack((graddata_x, graddata_x.transpose()[0]))))

        for column in self.values.transpose():
            gradrow = []
            for y in range(1,len(column)-1):
                gradrow.append(column[y+1] - column[y])
            graddata_y.append(gradrow)

        graddata_y = np.array(graddata_y)
        graddata_y = np.column_stack((graddata_y.transpose()[0], np.column_stack((graddata_y, graddata_y.transpose()[0]))))
        #plt.quiver(self.X[::10], self.Y[::10], graddata_x[::,10], graddata_y.transpose()[::,10])
        #stream_points = np.array(zip(self.X, -self.Y))
        #stream_points = np.array([self.X, -self.Y])
        stream_points = []
        for x in self.X[:-1]:
            for y in self.Y[:-1]:
                stream_points.append([x,y])
        stream_points = np.array(stream_points)
        #stream_points = np.dstack((self.X, self.Y[:-1]))[0][:-1]
        print(stream_points)
        #stream_points = np.array(zip(np.arange(0, len(self.X), .5), -np.arange(0, len(self.Y), .5)))

        #print(len(self.X[:len(graddata_y.transpose())-1]))
        #print(len(self.Y[:len(graddata_x)]))
        #print(len(graddata_x[0]))
        #print(len(graddata_x))

        #plt.streamplot(self.X[:len(graddata_y.transpose())-1], self.Y[:len(graddata_x)], graddata_x, graddata_y.transpose(), start_points=stream_points, color="black", density=1)

        #Y,X = np.mgrid[-10:10:.01, -10:10:.01]
        #y,x = Y[:,0], X[0,:]
        #U, V = Y**2, X**2
        #stream_points = []
        #for x in np.arange(-9,9,.5):
        #    for y in -np.arange(-9,9,.5):
        #        stream_points.append([x,y])
        #stream_points = np.array(stream_points)
        #print(stream_points)
        #stream_points = np.dstack((np.arange(-9,9,.5), -np.arange(-9,9,.5)))
        #plt.streamplot(x,y, U,V, start_points=stream_points, density=35)

        #print(len(self.X))
        #print(len(self.Y[:-2]))
        #print(len(graddata_x))
        #print(len(graddata_y))
        #U, V = np.meshgrid(self.X, self.Y[:-1])
        #plt.quiver(self.X[:-1], self.Y[:-2], graddata_x[:-1], graddata_y)
        #skip = (slice(None,None,3))
        #skip2 = (slice(None,None,3),slice(None,None,3))
        #plt.quiver(self.X[skip], self.Y[:-1:10], graddata_x[skip2], graddata_y[skip2], scale=10, minshaft=10, color='black')


    def show_equipotential(self):
        print("\n")
        print(len(self.X))
        print(len(self.Y))
        print(len(self.values[0]))
        print(len(self.values))
        plt.contour(self.X[:-1], self.Y[:-1], self.values, 15, colors="grey", linestyles="solid")



if __name__ == "__main__":
    app = QApplication(sys.argv)
    main = Electrostatics()
    main.show()
    sys.exit(app.exec_())
