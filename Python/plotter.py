import numpy as np
import matplotlib.pyplot as plt


class Plotter():
    def __init__(self, filename):
        self.filename = filename
        self.time_data = []
        self.temperature_data = []

    def get_data(self):
        self.time_data, self.temperature_data = np.loadtxt(self.filename, unpack=True)

    def plot(self):
        plt.plot(self.time_data, self.temperature_data)
        plt.title(self.filename, size=20)
        plt.xlabel(r"Time, [$s$]", size=15)
        plt.ylabel(r"Temperature, [$^{\circ}C$]", size=15)
        plt.show()


if __name__ == '__main__':
    print "Choose a filename"
    filename = raw_input(">>> ")
    plotter = Plotter(filename)
    plotter.get_data()
    plotter.plot()
