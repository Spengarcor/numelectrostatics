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

        self.solver = eBoundarySolver(100,100)

        self.window = QWidget(self)
        #self.addTab(self.tab1, "Tab 1")
        self.figure = plt.figure(figsize=(6,6))
        self.resize(1400,900)
        self.canvas = FigureCanvas(self.figure)
        self.filepath = ""

        #layout = QVBoxLayout()
        layout = QGridLayout(self.window)
        layout.addWidget(self.canvas, 0, 0, 10, 10)
        #self.window.setLayout(layout)


        self.ptn_label = QLabel("Point")
        self.ptn_x_label = QLabel("x-coord")
        self.ptn_y_label = QLabel("y-coord")
        self.ptn_V_label = QLabel("Charge")

        self.point_x_input = QLineEdit(self)
        self.point_y_input = QLineEdit(self)
        self.point_V_input = QLineEdit(self)

        self.point_btn = QPushButton("Add")
        self.point_btn.clicked.connect(lambda:self.put_point())

        layout.addWidget(self.ptn_label, 0, 14)
        layout.addWidget(self.ptn_x_label, 1, 12)
        layout.addWidget(self.ptn_y_label, 1, 14)
        layout.addWidget(self.ptn_V_label, 3, 12)
        layout.addWidget(self.point_x_input, 2, 12)
        layout.addWidget(self.point_y_input, 2, 14)
        layout.addWidget(self.point_V_input, 4, 12)
        layout.addWidget(self.point_btn, 4, 14)


        self.rec_label = QLabel("Rectangle")
        self.rec_x_label = QLabel("Corner-x")
        self.rec_y_label = QLabel("Corner-y")
        self.rec_x_len_label = QLabel("x-Length")
        self.rec_y_len_label = QLabel("y-Length")
        self.rec_V_label = QLabel("Charge")

        self.rec_x_input = QLineEdit(self)
        self.rec_y_input = QLineEdit(self)
        self.rec_x_len_input = QLineEdit(self)
        self.rec_y_len_input = QLineEdit(self)
        self.rec_V_input = QLineEdit(self)

        self.rec_btn = QPushButton("Add")
        self.rec_btn.clicked.connect(lambda:self.put_rectangle())

        layout.addWidget(self.rec_label, 5, 14)
        layout.addWidget(self.rec_x_label, 6, 12)
        layout.addWidget(self.rec_y_label, 6, 14)
        layout.addWidget(self.rec_x_len_label, 8, 12)
        layout.addWidget(self.rec_y_len_label, 8, 14)
        layout.addWidget(self.rec_V_label, 6, 16)
        layout.addWidget(self.rec_x_input, 7, 12)
        layout.addWidget(self.rec_y_input, 7, 14)
        layout.addWidget(self.rec_x_len_input, 9, 12)
        layout.addWidget(self.rec_y_len_input, 9, 14)
        layout.addWidget(self.rec_V_input, 7, 16)
        layout.addWidget(self.rec_btn, 9, 16)


        self.crl_label = QLabel("Circle")
        self.crl_x_label = QLabel("Centre-x")
        self.crl_y_label = QLabel("Centre-y")
        self.crl_r_label = QLabel("Radius")
        self.crl_V_label = QLabel("Charge")

        self.crl_x_input = QLineEdit(self)
        self.crl_y_input = QLineEdit(self)
        self.crl_r_input = QLineEdit(self)
        self.crl_V_input = QLineEdit(self)

        self.crl_btn = QPushButton("Add")
        self.crl_btn.clicked.connect(lambda:self.put_circle())

        layout.addWidget(self.crl_label, 13, 14)
        layout.addWidget(self.crl_x_label, 15, 12)
        layout.addWidget(self.crl_y_label, 15, 14)
        layout.addWidget(self.crl_x_input, 16, 12)
        layout.addWidget(self.crl_y_input, 16, 14)
        layout.addWidget(self.crl_btn, 16, 16)
        layout.addWidget(self.crl_r_label, 17, 12)
        layout.addWidget(self.crl_V_label, 17, 14)
        layout.addWidget(self.crl_r_input, 18, 12)
        layout.addWidget(self.crl_V_input, 18, 14)


        self.clear_btn = QPushButton("Clear")
        self.solve_btn = QPushButton("Solve")
        self.solve_btn.clicked.connect(lambda:self.plot())
        self.lbl1 = QLabel("")
        self.lbl2 = QLabel("")

        layout.addWidget(self.clear_btn, 11, 5)
        layout.addWidget(self.lbl1, 12, 5)
        layout.addWidget(self.solve_btn, 13, 5)
        layout.addWidget(self.lbl2, 14, 5)


    def put_circle(self):
        x = int(self.crl_x_input.text())
        y = int(self.crl_y_input.text())
        r = int(self.crl_r_input.text())
        charge = float(self.crl_V_input.text())
        self.crl_x_input.setText("")
        self.crl_y_input.setText("")
        self.crl_r_input.setText("")
        self.crl_V_input.setText("")
        self.solver.circle(x, y, r, charge, charge, 0, True, True, False)

    def put_rectangle(self):
        x = int(self.rec_x_input.text())
        y = int(self.rec_y_input.text())
        x_len = int(self.rec_x_len_input.text())
        y_len = int(self.rec_y_len_input.text())
        charge = float(self.rec_V_input.text())
        self.rec_x_input.setText("")
        self.rec_y_input.setText("")
        self.rec_x_len_input.setText("")
        self.rec_y_len_input.setText("")
        self.rec_V_input.setText("")
        self.solver.rectangle(x, y, x_len, y_len, charge)


    def put_point(self):
        x = int(self.point_x_input.text())
        y = int(self.point_y_input.text())
        charge = float(self.point_V_input.text())
        self.point_x_input.setText("")
        self.point_y_input.setText("")
        self.point_V_input.setText("")
        self.solver.single_point(x, y, charge, True)


    def plot(self):
        self.canvas.figure.clf()
        self.solver.save_to_csv("temp")
        self.filepath = "temp.csv"
        self.get_display()
        #ax = self.figure.add_subplot(111)
        #ax.plot(self.data, 'r-')
        self.create_grid()
        self.solver.relaxPotential_SOR(1e-4, 100)
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
