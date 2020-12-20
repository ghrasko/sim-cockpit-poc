import time
import serial                   # USB serial communication
from fsuipc import FSUIPC       # FSUIPC communication

# USB (COM) port configuration
serial_port = 'COM7'
baud_rate = 57600
frequency = 10
arduino = serial.Serial(serial_port, baud_rate, timeout=1/frequency)

with FSUIPC() as fsuipc:
    # Prepare data structure for sending to FSUIPC
    act = [ 0, 0 ]
    toSim = fsuipc.prepare_data([
        (0X3103, "b"),  # Avionics master
        (0X07C8, "u")   # AP Heading hold status
    ], False)

    # Prepare data structure for receiving from FSUIPC
    fromSim = fsuipc.prepare_data([
        (0X07C8, "u")   # AP Heading hold status
    ], True)

    while True:
        # Reading data via FSUIPC and sending received data to USB port
        apStatus, = fromSim.read()
        arduino.write( repr(apStatus).encode("ascii") )
        act[1] = apStatus
        
        # Monitoring COM port and sending received data to FSUIPC
        if arduino.inWaiting() > 0 :
            data = arduino.readline().decode("ascii")[:-2] # Dropping new-line chars
            if data == 'AVIONICS-ON': act[0] = 1
            elif data == 'AVIONICS-OFF': act[0] = 0
            elif data == 'APPHDG-ON': pass
            elif data == 'APPHDG-OFF': act[1] = (1 - apStatus)
            else:
                pass

            print( data )
            toSim.write( act )  # Sending all current values

        time.sleep(0.1)

arduino.close()