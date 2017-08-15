
# Dingsen
Arduino code of the device explained.

## Code Structure

* **Dingsen.ino** The heart of the program. Here initializations are performed and where the loop is.
* **Display.ino** Contains functions governing the display of the device.
* **FileHandling.ino**
* **ReadingData.ino**
* **SerialCommunication.ino**
* **TemperatureSensor.ino**
* **keyPad.ino**
* **pushSD.ino**

## Manual Mode
In manual mode, the experiments are controlled and performed and solely by the device. If the device is not explicitly informed otherwise via a serial connection (see Slave Mode) it will automatically enter `manual mode`.

## Data Transfer

## Slave Mode

## Dependencies

#### Import needed
* [LiquidCrystal_I2C](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library/)
* [OneWire](https://github.com/PaulStoffregen/OneWire)
* [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library)

These libraries can be found at [libraries](https://github.com/sloydsalen/Dingsen/tree/master/Arduino/libraries).

#### Native
* [Wire](https://www.arduino.cc/en/Reference/Wire)
* [SD](https://www.arduino.cc/en/Reference/SD)


<!--
`dingsen.py` is a python class intended to retrieve data from an Arduino running the code [Arduino/Dingsen](../Arduino/Dingsen) using a serial port. Depending on the usage, the data can be written directly to a `.txt` file, live-plotted, analyzed after the experiment without writing to file, ... the possibilities are (almost) limitless!

## Direct usage

When running the code directly, you need to provide the port address, i.e
```bash
>>> python dingsen.py /dev/cu.usbmodem1421
```
When opening a file (choosing a group) on the device, there should appear a window for live-plotting the data recieved by the computer. If numerous attempts results in failure, then one might always turn off the computer and store data directly to the mini-SD card mounted on the device. If needed, see [Arduino/Dingsen](../Arduino/Dingsen).

The code can also be invoked with an additional argument, namely the name of the `.txt` file to which the data is written. If this spot is left blank, then the filename is the one chosen from the device. If, for some reason, you find yourself in need of repeating the same experiment multiple times without wanting to dispose of already produced data, then do something like this:
```bash
>>> python dingsen.py PORT whatsTheTemperatureOfMyCoffee137.txt
```
for some desired serial port address `PORT`.

### What's my serial port address? (MAC)
A list of available port addresses can be found by typing
```bash
>>> ls /dev/{tty,cu}.*
```
in the `terminal`. If connected via USB, pick one of the serial port addresses whose name contains *usb*. If many alternatives appear on the screen, and you do not know which you are looking for, I recommend using *trial and error*.



## On import
Importing the `dingsen.py` file is done just like any other import in Python, namely writing
```python
import dingsen.py
```
in the top of your script. The device is then initialized by,
```
thing  = Dingsen()
```
If connected to a device that passes more (or less) than two numbers per timestep via the serial, then one would have to provide this number as an argument, i.e. `Dingsen(3)`.

Once constructed, the program needs to know where to reach out for the device. This is the part where the serial port address is needed. Let us say you find your address to be */dev/cu.usbmodem1421*. You would then need to inform the program about this discovery by writing `dings.openPort("/dev/cu.usbmodem1421")`. If the computer is able to successfully open the provided port, it will respond with the boolean `True`, if not the value `False` will be returned. Hence it might be a good idea to include an `assert` in front of the `openPort()` call to stop a malfunctioning port from influencing the rest of the program.

Here is an example of a minimal program:
```python
import dingsen.py
dings = Dingsen()
assert dings.openPort("/dev/cu.usbmodem1421")
dings.writeAndLiveplot("myTempFile.txt")
```
that initializes the device for a session with two output values, demands success of the opening of the port */dev/cu.usbmodem1421*, and writes the data to a file *myTempFile.txt* while plotting the recieved data live.




## Dependencies

- [PySerial](https://pythonhosted.org/pyserial/)
- [Pylab](http://matplotlib.org/faq/usage_faq.html?highlight=pylab)
- [Subprocess](https://docs.python.org/2/library/subprocess.html) (native)
- [Sys](https://docs.python.org/2/library/sys.html) (native)
-->

### Drivers for Arduino Nano
Some operating systems are unable to detect the Arduino Nano due to driver issues. 
Solution: Download the driver for your OS from [this link](http://www.wch.cn/download/CH341SER_ZIP.html), install and restart the computer.
