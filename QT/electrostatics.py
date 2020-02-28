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
from pylib import eBoundarySolver



class Electrostatics(QTabWidget):
    def __init__(self, parent=None):
        super(Electrostatics, self).__init__(parent)

        self.solver = eBoundarySolver(100,100)

        self.window = QWidget(self)
        self.figure = plt.figure(figsize=(6,6))
        self.resize(1400,900)
        self.canvas = FigureCanvas(self.figure)
        self.filepath = ""

        layout = QGridLayout(self.window)
        layout.addWidget(self.canvas, 0, 0, 15, 15)


        self.ptn_label = QLabel("Point")
        self.ptn_x_label = QLabel("x-coord")
        self.ptn_y_label = QLabel("y-coord")
        self.ptn_V_label = QLabel("Charge")

        self.point_x_input = QLineEdit(self)
        self.point_y_input = QLineEdit(self)
        self.point_V_input = QLineEdit(self)

        self.point_btn = QPushButton("Add")
        self.point_btn.clicked.connect(lambda:self.put_point())

        layout.addWidget(self.ptn_label, 0, 19)
        layout.addWidget(self.ptn_x_label, 1, 17)
        layout.addWidget(self.ptn_y_label, 1, 19)
        layout.addWidget(self.ptn_V_label, 3, 17)
        layout.addWidget(self.point_x_input, 2, 17)
        layout.addWidget(self.point_y_input, 2, 19)
        layout.addWidget(self.point_V_input, 4, 17)
        layout.addWidget(self.point_btn, 4, 19)


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

        layout.addWidget(self.rec_label, 6, 19)
        layout.addWidget(self.rec_x_label, 7, 17)
        layout.addWidget(self.rec_y_label, 7, 19)
        layout.addWidget(self.rec_x_len_label, 9, 17)
        layout.addWidget(self.rec_y_len_label, 9, 19)
        layout.addWidget(self.rec_V_label, 7, 20)
        layout.addWidget(self.rec_x_input, 8, 17)
        layout.addWidget(self.rec_y_input, 8, 19)
        layout.addWidget(self.rec_x_len_input, 10, 17)
        layout.addWidget(self.rec_y_len_input, 10, 19)
        layout.addWidget(self.rec_V_input, 8, 20)
        layout.addWidget(self.rec_btn, 10, 20)


        self.crl_label = QLabel("Circle")
        self.crl_x_label = QLabel("Centre-x")
        self.crl_y_label = QLabel("Centre-y")
        self.crl_r_label = QLabel("Radius")

        self.crl_V_label = QLabel("Potentials")
        self.crl_V_in_label = QLabel("Internal")
        self.crl_V_bound_label = QLabel("Boundary")
        self.crl_V_out_label = QLabel("External")

        self.crl_x_input = QLineEdit(self)
        self.crl_y_input = QLineEdit(self)
        self.crl_r_input = QLineEdit(self)

        self.crl_V_in_input = QLineEdit(self)
        self.crl_V_bound_input = QLineEdit(self)
        self.crl_V_out_input = QLineEdit(self)

        self.crl_fixed_label = QLabel("Fixed?")
        self.crl_in_fixed = QCheckBox(self)
        self.crl_bound_fixed = QCheckBox(self)
        self.crl_out_fixed = QCheckBox(self)

        self.crl_btn_spacer = QLabel("")
        self.crl_btn = QPushButton("Add")
        self.crl_btn.clicked.connect(lambda:self.put_circle())

        layout.addWidget(self.crl_label, 13, 19)

        layout.addWidget(self.crl_x_label, 15, 17)
        layout.addWidget(self.crl_y_label, 17, 17)
        layout.addWidget(self.crl_x_input, 16, 17)
        layout.addWidget(self.crl_y_input, 18, 17)
        layout.addWidget(self.crl_r_label, 19, 17)
        layout.addWidget(self.crl_r_input, 20, 17)

        layout.addWidget(self.crl_V_label, 14, 19)
        layout.addWidget(self.crl_V_in_label, 15, 19)
        layout.addWidget(self.crl_V_in_input, 16, 19)
        layout.addWidget(self.crl_V_bound_label, 17, 19)
        layout.addWidget(self.crl_V_bound_input, 18, 19)
        layout.addWidget(self.crl_V_out_label, 19, 19)
        layout.addWidget(self.crl_V_out_input, 20, 19)

        layout.addWidget(self.crl_fixed_label, 14, 20)
        layout.addWidget(self.crl_in_fixed, 16, 20)
        layout.addWidget(self.crl_bound_fixed, 18, 20)
        layout.addWidget(self.crl_out_fixed, 20, 20)

        layout.addWidget(self.crl_btn_spacer, 21, 19)
        layout.addWidget(self.crl_btn, 22, 19)


        self.clear_btn = QPushButton("Clear")
        self.clear_btn.clicked.connect(lambda:self.clear())
        self.solve_btn = QPushButton("Solve")
        self.solve_btn.clicked.connect(lambda:self.solve())
        self.lbl1 = QLabel("")
        self.lbl2 = QLabel("")

        layout.addWidget(self.clear_btn, 16, 6)
        layout.addWidget(self.lbl1, 18, 5)
        layout.addWidget(self.solve_btn, 16, 8)
        layout.addWidget(self.lbl2, 17, 7)


        self.solver_label = QLabel("Solver")
        self.solver_choice = QComboBox(self)
        self.solver_choice.addItem("Jacobi")
        self.solver_choice.addItem("Gauss-Seidel")
        self.solver_choice.addItem("Successive-over-relaxation")

        layout.addWidget(self.solver_label, 16, 10)
        layout.addWidget(self.solver_choice, 16, 11)


        self.scalar_field_label = QLabel("Scalar Field")
        self.field_lines_label = QLabel("Field Lines")
        self.equi_label = QLabel("Equipotential Lines")

        self.scalar_field_choice = QCheckBox(self)
        self.field_lines_choice = QCheckBox(self)
        self.equi_choice = QCheckBox(self)

        self.scalar_field_choice.setChecked(True)
        self.scalar_field_choice.clicked.connect(self.plot)
        self.field_lines_choice.setChecked(True)
        self.field_lines_choice.clicked.connect(self.plot)
        self.equi_choice.setChecked(True)
        self.equi_choice.clicked.connect(self.plot)

        layout.addWidget(self.scalar_field_label, 19, 4)
        layout.addWidget(self.field_lines_label, 19, 7)
        layout.addWidget(self.equi_label, 19, 9)
        layout.addWidget(self.scalar_field_choice, 20, 4)
        layout.addWidget(self.field_lines_choice, 20, 7)
        layout.addWidget(self.equi_choice, 20, 9)


    def clear(self):
        self.canvas.figure.clf()
        self.canvas.draw()
        self.solver = eBoundarySolver(100, 100)


    def put_circle(self):
        x = int(self.crl_x_input.text())
        y = int(self.crl_y_input.text())
        r = float(self.crl_r_input.text())
        V_in = float(self.crl_V_in_input.text())
        V_bound = float(self.crl_V_bound_input.text())
        V_out = float(self.crl_V_out_input.text())
        fixed_in = self.crl_in_fixed.isChecked()
        fixed_bound = self.crl_bound_fixed.isChecked()
        fixed_out = self.crl_out_fixed.isChecked()
        self.crl_x_input.setText("")
        self.crl_y_input.setText("")
        self.crl_r_input.setText("")
        self.crl_V_in_input.setText("")
        self.crl_V_bound_input.setText("")
        self.crl_V_out_input.setText("")
        self.crl_in_fixed.setChecked(False)
        self.crl_bound_fixed.setChecked(False)
        self.crl_out_fixed.setChecked(False)
        self.solver.circle(x, y, r, V_in, V_bound, V_out, fixed_in, fixed_bound, fixed_out)
        self.plot()


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
        self.plot()


    def put_point(self):
        x = int(self.point_x_input.text())
        y = int(self.point_y_input.text())
        charge = float(self.point_V_input.text())
        self.point_x_input.setText("")
        self.point_y_input.setText("")
        self.point_V_input.setText("")
        self.solver.single_point(x, y, charge, True)
        self.plot()


    def solve(self):
        if self.solver_choice.currentText() == "Jacobi":
            self.solver.relaxPotential_J(1e-4, 10000)
        elif self.solver_choice.currentText() == "Gauss-Seidel":
            self.solver.relaxPotential_G(1e-4, 10000)
        elif self.solver_choice.currentText() == "Successive-over-relaxation":
            self.solver.relaxPotential_SOR(1e-4, 10000)
        self.plot()


    def plot(self):
        self.canvas.figure.clf()
        self.solver.save_to_csv("temp")
        self.filepath = "temp.csv"
        self.get_display()
        self.create_grid()

        if self.scalar_field_choice.isChecked():
            self.show_scalar_field()
        if self.field_lines_choice.isChecked():
            self.show_field_lines()
        if self.equi_choice.isChecked():
            self.show_equipotential()
        self.canvas.draw()

    # Reads from a specified csv file to a matrix
    def get_display(self):
        filename = self.filepath
        data = np.loadtxt(filename, dtype=str, delimiter=';')
        data = np.delete(data, -1, axis=1)
        data = data.astype(np.float)
        self.values = np.array(data)
        self.data = data


    # Establishes the 2D grid to display
    def create_grid(self):
        self.X = np.linspace(0, len(self.data[0,:]), len(self.data[0,:])+1)
        self.Y = np.linspace(0, len(self.data[:,0]), len(self.data[:,0])+1)


    def truncate_colormap(self, cmap, minval=0.0, maxval=1.0, n=100):
        new_cmap = colors.LinearSegmentedColormap.from_list('trunc({n},{a:.2f},{b:.2f})'.format(n=cmap.name, a=minval, b=maxval),
            cmap(np.linspace(minval, maxval, n)))
        return new_cmap


    def show_scalar_field(self):
        if max(map(max, self.values)) == 0:
            cmap = plt.get_cmap("bwr")
            new_cmap = self.truncate_colormap(cmap, 0, 0.5)
            plt.pcolormesh(self.X, self.Y, self.values, cmap=new_cmap)
            zero_patch = mpatches.Patch(color='white', label=str(max(map(max, self.values))))
            neg_patch = mpatches.Patch(color='blue', label=str(min(map(min, self.values))))
            plt.legend(handles=[neg_patch, zero_patch])
            print(0)
        elif min(map(min, self.values)) == 0:
            cmap = plt.get_cmap("bwr")
            new_cmap = self.truncate_colormap(cmap, 0.5, 1)
            plt.pcolormesh(self.X, self.Y, self.values, cmap=new_cmap)
            pos_patch = mpatches.Patch(color='red', label=str(max(map(max, self.values))))
            zero_patch = mpatches.Patch(color='white', label=str(min(map(min, self.values))))
            plt.legend(handles=[zero_patch, pos_patch])
            print(1)
        elif max(map(max, self.values)) < 0:
            cmap = plt.get_cmap("Blues")
            new_cmap = self.truncate_colormap(cmap, 0.3, 1)
            plt.pcolormesh(self.X, self.Y, self.values, cmap=new_cmap)
            print(2)
        elif min(map(min, self.values)) > 0:
            cmap = plt.get_cmap("Reds")
            new_cmap = self.truncate_colormap(cmap, 0.3, 1)
            plt.pcolormesh(self.X, self.Y, self.values, cmap=new_cmap)
            print(3)
        else:
            offset = colors.DivergingNorm(vmin=min(map(min, self.values)), vcenter=0, vmax=max(map(max, self.values)))
            draw_data = offset(self.values)
            plt.pcolormesh(self.X, self.Y, draw_data, cmap=plt.get_cmap("bwr"))
            pos_patch = mpatches.Patch(color='red', label=str(max(map(max, self.values))))
            neg_patch = mpatches.Patch(color='blue', label=str(min(map(min, self.values))))
            plt.legend(handles=[neg_patch, pos_patch])
            print(4)



    def show_field_lines(self):
        dx, dy = np.gradient(self.data)
        dx = np.column_stack((dx[:,0], dx))
        dy = np.column_stack((dy[:,0], dy))
        plt.streamplot(self.X, self.Y[:-1], dy, dx, color='black')


    def show_equipotential(self):
        plt.contour(self.X[:-1], self.Y[:-1], self.values, 15, colors="grey", linestyles="solid")



if __name__ == "__main__":
    app = QApplication(sys.argv)
    main = Electrostatics()
    main.show()
    sys.exit(app.exec_())
