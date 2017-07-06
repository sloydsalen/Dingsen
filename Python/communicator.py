import serial # install with hombrew: sudo pip install pyserial
from sys import argv
from time import sleep

filename    = 'defaultFilename.txt'
port        = '/dev/cu.usbmodem1421' # default port
SERIAL      = False

def openPort(port,baud=9600):
    return serial.Serial(port, baud)

if len(argv)>1:
    port = argv[1]
elif len(argv)>2:
    filename = argv[2]

print "PORT: ", port

SERIAL = openPort(port)
SERIAL.flush();

initiate                = "INITIATE"+"\n"
recordTrue              = "RECORD TRUE"+"\n"
recordFalse             = "RECORD FALSE"+"\n"
resetTime               = "RESET TIME"+"\n"
deleteAll               = "DELETE ALL"+"\n"
printStoredFiles        = "PRINT STORED"+"\n"
transferAllFiles        = "TRANSFER ALL"+"\n"
increaseBitResolution   = "INCREASE RES"+"\n"
decreaseBitResolution   = "DECREASE RES"+"\n"


def do(msg,sl=2):
    sleep(sl)
    print msg.strip("\n")
    SERIAL.write(msg)

do(initiate)
do(recordTrue)
for i in xrange(20):
    line = SERIAL.readline()
    print line.strip("\n")
do(recordFalse,0)
do(printStoredFiles)
do(transferAllFiles)
while True:
    line = SERIAL.readline()
    print line.strip("\n")
    if "*END OF FILE*" in line: break
