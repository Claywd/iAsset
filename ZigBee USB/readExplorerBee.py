import serial, time, String

ser = serial.Serial('/dev/cu.usbserial-DN02SMAF', 9600)
serial_line = ser.readline()
while 1:

    if (ser.readline() != serial_line)
        serial_line = ser.readline()
        print(serial_line) # If using Python 2.x use: print serial_line
    # Do some other work on the data
    time.sleep(2) # sleep 5 minutes

    # Loop restarts once the slseep is finished

ser.close() # Only executes once the loop exits
