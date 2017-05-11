import serial # install with hombrew: sudo pip install pyserial
import subprocess

class Dingsen:
    def __init__(self,inputs=2): #if, for some reason, other numer of inputs desired
        self.inputs = inputs
        self.active = True
        self.values = [[] for i in range(inputs)] # make [[],[],..,[]]
        self.nameOfInput = False

    def getPorts(self,printIt=False):
        # works only on mac
        ports = subprocess.check_output(['bash','-c', "ls /dev/cu.*"])
        if printIt:
            print ports
        return ports.split("\n")[:-1]

    def openPort(self,port='/dev/cu.usbmodem1421',baud=9600):
        try:
            self.serial = serial.Serial(port, baud)
            self.serial.flush();
            return True
        except:
            return False

    def getData(self):
        while True:
            self.readLine(True)
            if not dings.active: break
        dings.active = True
        return self.values

    def returnWaitingData(self):
        return self.serial.inWaiting()


    def writeLineToFile(self,line,openFile,printIt=False):
        if "CLOSING" in line: # if file closing
            self.active = False;
            self.serial.flush();
            print "*FILE CLOSED*"
        else: # if file not closing
            openFile.write(line)
            openFile.flush()
            if printIt: print line
            # val = float(line.strip("\t"))
            # print int((100)/(50-10)*val)*"#"

    def getFilename(self):
        firstLine = self.serial.readline()
        if "FILE:" in firstLine:
            string = firstLine.strip("FILE:")
            string = string.split(".txt")
            string = string[0]+".txt"
            self.filename = string
            return self.filename
        else:
            return False

    def writeToFile(self,filename=False):
        if not filename:
            filename = self.getFilename();
            print "Writing to file: %s"%filename
        with open(filename, 'a') as f:
            while True:
                line = self.serial.readline().strip("\n")
                self.writeLineToFile(line,f,True) # print data: true
                if not dings.active: break

    # FOR DATA STORAGE
    def writeAndCollectData(self,filename=False):
        if not filename:
            filename = self.getFilename();
            print "Writing to file: %s"%filename
        with open(filename, 'a') as f:
            while True:
                line = self.serial.readline().strip("\n")
                self.writeLineToFile(line,f,True)
                self.handleLine(line,False) # print data: false
                if not dings.active: break

    def handleLine(self,line,printIt=False,separator="\t"):
        line = line.strip("\n")
        if printIt: print "IN:",line
        if "CLOSING" in line:
            self.active = False;
            self.serial.flush();
        else:
            lines = line.split(separator)[:-1]
            for j,string in enumerate(lines):
                self.values[j].append(float(string))
                if len(self.values[j])>self.Nmax: # pop if overpopulated
                    del self.values[j][0]

    # LIVEPLOT
    def writeAndLiveplot(self,filename=False, N=200):
        self.Nmax = N
        self.initiatePlotting();
        fName = self.getFilename(); # get name suggested by device
        if not filename:
            filename = fName
        print "Writing to file: %s"%filename
        with open(filename, 'a') as f:
            while True:
                line = self.serial.readline().strip("\n")
                self.writeLineToFile(line,f,False) # print: True
                self.handleLine(line,False)
                self.updatePlot()
                show()
                pause(1e-6)
                if not dings.active: break
        ioff()
        show()

    def initiatePlotting(self):
        self.LINES = []
        self.line, = plot([0],[0],marker=".")
        grid(b=True, which='major', color='0', linestyle='-',alpha=0.3)
        grid(b=True, which='minor', color='0', linestyle='-',alpha=0.05)
        minorticks_on()
        ion()

    def updatePlot(self):
        # assuming dataset X Y to be plotted as [x,y]
        ydata = self.values[1] # temp
        xdata = self.values[0] # time
        self.line.set_xdata(xdata)
        self.line.set_ydata(ydata)  # update the data
        if min(ydata)<max(ydata):
            ylim([min(ydata),max(ydata)])
        if min(xdata)<max(xdata):
            xlim([min(xdata),max(xdata)])

if __name__=="__main__":
    from pylab import ion,plot,grid,minorticks_on,ylim,xlim,show,pause,figure,title,ioff,xlabel,ylabel
    from sys import argv
    # if run directly, then dump to file

    dings    = Dingsen(2) # time and temp

    if len(argv)>1:
        port = argv[1]
    else:
        print """
        SHOULD RUN AS: python dingsen.py [PORT] [FILENAME]
            PORT:       Mandatory,          i.e  /dev/cu.usbmodem1421
            FILENAME:   Can be left blank,  i.e  testOfFilename.txt
        """
        port = dings.getPorts(True)[-1]

    while not dings.openPort(port): # assert openPort successful
        port = raw_input("""
        The provided port did not seem to work.
        MAC: >> ls /dev/{tty,cu}.*

        Please specify a port:
        """)

    title("DINGSEN")
    xlabel("Tid [sek]")
    ylabel("Temp [Celsius]")

    if len(argv)>2:
        filename = argv[2]
        print 30*"-"+"\n"+"PORT:    %s \nFILENAME: %s\n"%(port,filename)+30*"-"+"\n"
        dings.writeAndLiveplot(filename)
    else:
        print 30*"-"+"\n"+"PORT:    %s \nFILENAME: Default\n"%port+30*"-"+"\n"
        dings.writeAndLiveplot()
