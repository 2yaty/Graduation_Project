import serial
import struct
import json

# Configure serial port
ser = serial.Serial(
    port='/dev/ttyS0',  # replace with your port name
    baudrate=19200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

def read_packet(ser):
    while True:
        # Read header
        header = ser.read(2)
        if header == b'\xAA\x55':
            # Read payload length
            length = ser.read(1)
            
            if length:
                length = struct.unpack('B', length)[0]
                print("payload length", length)
                # Read payload
                payload = ser.read(length)
                # print("payload", struct.unpack(f'{length}s', payload)[0].decode('utf-8'))
                # print("payload", payload)

                # Convert payload to JSON
                try:
                    payload_json = json.loads(struct.unpack(f'{length}s', payload)[0])
                    print("Payload in JSON format:", payload_json)
                except json.JSONDecodeError:
                    print("Error decoding payload as JSON")
                
                # Read checksum
                checksum = ser.read(1)
                if checksum:
                    checksum = struct.unpack('B', checksum)[0]
                    # print("checksum", checksum)
                    # print("sum(payload)", sum(payload) & 0xFF)
                    # Validate checksum (simple sum of payload bytes)
                    if checksum == sum(payload) & 0xFF:
                        return payload
                    else:
                        print("Checksum error")
            else:
                print("Error reading length")
        else:
            # print("Invalid header")
            pass

# Example usage
while True:
    data = read_packet(ser)
    if data:
        # print("Received data:", data)
        pass
