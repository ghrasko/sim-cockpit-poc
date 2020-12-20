import serial                   # USB serial communication
from fsuipc import FSUIPC       # FSUIPC communication
from utils import Progress      # Just some progress indicator in the terminal

progress = Progress()

# USB (COM) port configuration
serial_port = 'COM7'
baud_rate = 9600
arduino = serial.Serial(serial_port, baud_rate, timeout=0.1)

with FSUIPC() as fsuipc:
    # Prepare data structure for sending through FSUIPC
    prepared = fsuipc.prepare_data([
        (0X3103, "b")
    ], False)

    # Monitoring COM port and sending received data to FSUIPC. Also logging to terminal
    while True:
        data = arduino.readline().decode("ascii")[:-2] # Dropping new-line chars
        if data == 'ON':
            print('->ON')
            prepared.write( [1] )
        elif data == 'OFF':
            print('->OFF')
            prepared.write( [0] )
        else:
            progress()


