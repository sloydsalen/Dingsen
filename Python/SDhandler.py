import serial # install with hombrew: sudo pip install pyserial
import serial.tools.list_ports as sertools
from time import sleep

initiate                = "INITIATE"+"\n"
recordTrue              = "RECORD TRUE"+"\n"
recordFalse             = "RECORD FALSE"+"\n"
resetTime               = "RESET TIME"+"\n"
deleteAll               = "DELETE ALL"+"\n"
printStoredFiles        = "PRINT STORED"+"\n"
transferAllFiles        = "TRANSFER ALL"+"\n"
increaseBitResolution   = "INCREASE RES"+"\n"
decreaseBitResolution   = "DECREASE RES"+"\n"
ORDERS = [initiate,recordTrue,recordFalse,
          resetTime,deleteAll,printStoredFiles,
          transferAllFiles,increaseBitResolution,
          decreaseBitResolution]

class DataRetriever:
    def __init__(self):
        self.SERIAL = False
        self.initializePort()
        self.SERIAL.flush()
        print "Serial Connection established: %s"%self.port.device

    def initializePort(self):
        ports = self.getPorts()
        for port in ports:
            if "Arduino" in str(port.manufacturer):
                self.port = port
                self.SERIAL = self.openPort(port)
        if self.SERIAL == False:
            print "\n\nERROR: Did not find any connected arduino devices"
            print "       these ports were found:\n"
            print "%3s %35s -  %30s  %30s  "%("NUM","ADDRESS","MANUFACTURER","DESCRIPTION")
            for n,port in enumerate(ports):
                print "%3g %35s -   %30s  %30s  "%(n,port.device,port.manufacturer,port.description)
            num = input("\nPick the desired port: ")
            chosenport = ports[num]
            print "You picked: %s"%chosenport.device
            self.port = port
            self.SERIAL = self.openPort(port)

    def getPorts(self):
        return sertools.comports()

    def openPort(self,port,baud=9600):
        return serial.Serial(port.device, baud)

    def do(self,msg,sl=2):
        sleep(sl)
        print "To device >> " + msg.strip("\n")
        self.SERIAL.write(msg)

    def manualPush(self):
        print "\n MANUAL DATA TRANSFER"
        print " Choose the desired file from the device"
        print " and press print to transfer the data.\n"
        line = self.SERIAL.readline().strip("\n")
        while "*PUSHING FILE*" not in line:
            line = self.SERIAL.readline().strip("\n")
        firstline = self.SERIAL.readline()
        print firstline
        filename = firstline[:-2]
        with open(filename, 'a') as f:
            while True:
                line = self.SERIAL.readline()
                print line.strip("\n")
                if "*END OF FILE*" in line:
                    break
                f.write(line)
                f.flush()

    def slavePush(self):
        self.do(initiate)
        self.do(transferAllFiles)
        self.handleTransferAll()

    def handleTransferAll(self):
        while True:
            line = self.SERIAL.readline().strip("\n")
            if "*PUSHING FILE*" in line: # Data from new file starts transfer
                nameOfFile = self.SERIAL.readline().strip("\n").strip("\r") # get filename from first line
                if "*END OF FILE*" not in nameOfFile: # If file available
                    with open(nameOfFile, 'a') as f:  # make new file
                        print "===== RETRIEVING FILE:", nameOfFile
                        while True: # read file
                            line = self.SERIAL.readline().strip("\n")
                            if "*END OF FILE*" in line: break # if end of file: break from while only
                            print line
                            f.write(line) # write to file
                            f.flush() # ensure written
                        else: # executed when while ended on break
                            continue
            if "*END OF TRANSFER*" in line:
                print "ALL FILES (hopefully) TRANSFERRED"
                break

    def totalSlave(self):
        self.do(initiate)
        print "\n TOTAL SLAVE MODE INTITATED"
        print " (Written orders are sent directly to the device)"
        print " allowed orders are:"
        print "\n BREAK, LISTEN [num], ", ", ".join([ordr.strip("\n") for ordr in ORDERS])+"\n"
        order = None
        while True:
            order = raw_input("Order: ")
            if order == "BREAK": break
            elif "LISTEN" in order:
                self.SERIAL.reset_output_buffer()
                numLines = int(order.split("LISTEN")[-1])
                for i in range(numLines):
                    line = self.SERIAL.readline().strip("\n").strip("\r")
                    print line
            elif order=="TRANSFER ALL":
                self.do(transferAllFiles)
                self.handleTransferAll()
            else:
                self.do(order+"\n")


if __name__=="__main__":
    from sys import argv

    obj = DataRetriever()
    try:
        if argv[1]=="manual":
            obj.manualPush()
        elif argv[1]=="totalslave":
            obj.totalSlave()
        else:
            obj.slavePush()
    except:
        obj.slavePush()
