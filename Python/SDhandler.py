import serial # install with hombrew: sudo pip install pyserial
from sys import argv

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

firstline = SERIAL.readline()

if filename=='defaultFilename.txt':
    print firstline
    filename = firstline[:-2]

with open(filename, 'a') as f:
    while True:
        line = SERIAL.readline()
        print line.strip("\n")
        if "*END OF FILE*" in line:
            break
        f.write(line)
        f.flush()
