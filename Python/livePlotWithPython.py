import serial # install with hombrew: sudo pip install pyserial
from pylab import ion,plot,grid,minorticks_on,ylim,xlim,show,pause,figure,title
import subprocess

class Liveplot:
    def __init__(self,N):
        self.Nmax   = N;
        self.values = [];
        self.values = {};
        self.nameOfInput = False

    def getPorts(self,printIt=False):
        ports = subprocess.check_output(['bash','-c', "ls /dev/cu.*"])
        if printIt:
            print ports
        return ports.split("\n")[:-1]

    def setNameOfInputs(self,names):
        self.nameOfInput = {}
        for i,n in enumerate(names):
            self.nameOfInput[i] = n

    def openPort(self,port='/dev/cu.usbmodem1421',baud=9600):
        try:
            self.serial = serial.Serial(port, baud)
            return True
        except:
            return False;

    def readLine(self,separator="\t"):
         # assuming line ends with the separator
        strings = self.serial.readline().split(separator)[:-1]
        for i,string in enumerate(strings):
            if(self.nameOfInput!=False):
                j = self.nameOfInput[i]
            else:
                j = i
            if j in self.values:
                self.values[j].append(float(string))
                if len(self.values[j])>self.Nmax: # pop if overpopulated
                    del self.values[j][0]
            else:
                self.values[j] = [float(string)];
        print " ".join(strings)

    def initiatePlotting(self):
        liveplot.readLine() # one read to initiate
        self.LINES = []
        for j,dataName in enumerate(self.values.keys()):
            figure(j)
            title(self.nameOfInput[j])
            line, = plot(liveplot.values[dataName][0],0,marker=".")
            self.LINES.append(line)
            grid(b=True, which='major', color='0', linestyle='-',alpha=0.3)
            grid(b=True, which='minor', color='0', linestyle='-',alpha=0.05)
            minorticks_on()
            ion()

    def updatePlot(self):
        for j,dataName in enumerate(self.values.keys()):
            figure(j)
            ydata = liveplot.values[dataName]
            xdata = range(len(ydata))
            self.LINES[j].set_xdata(xdata)
            self.LINES[j].set_ydata(ydata)  # update the data
            ylim([min(ydata),max(ydata)])
            xlim([min(xdata),max(xdata)])



liveplot = Liveplot(500)
ports = liveplot.getPorts(True)
liveplot.openPort(ports[-1])
liveplot.setNameOfInputs(["light","temp"])

# initiate after first read
liveplot.initiatePlotting()

for i in range(400):
    liveplot.readLine()   # retrieve
    liveplot.updatePlot() # update
    show()                # show
    pause(1e-9);          #
