import serial, time

ser = serial.Serial('/dev/cu.usbserial-DN02SMAF', 9600)
serialLine = ser.readline()
while 1:
    serialNextLine = ser.readline()
    if serialNextLine != serialLine:
        serialLine = serialNextLine
        print(serialLine) # If using Python 2.x use: print serial_line
    # Do some other work on the data
    time.sleep(2) # sleep 5 minutes

    # Loop restarts once the slseep is finished

ser.close() # Only executes once the loop exits
