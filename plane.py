# Brian Lesko 
# Run this file on the mobile robot, it will relay the UDP signal to the arduino over the serial USB connection

import arduino as ard
import socket
from get_ip import get_IP

def main():

    # Set up the serial connection 
    port = '/dev/ttyACM0'
    IP = get_IP('wlan0')
    # on mac in terminal: 'ls /dev/tty.*' to find the port manually
    # on linux in terminal: 'ls /dev/tty*' to find the port manually or 'dmesg | grep tty' to find the port manually
    try: 
        ser = serial.Serial(port, 115200) # usually '/dev/ttyACM0' on linux
        print(f"Connection to {port} successful")
    except Exception as e:
        print("Could not connect to arduino")

    # Set up the UDP connection
    my_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    my_socket.bind((IP, 12345))

    print("Waiting for commands...")
    while True:
        # Receive UDP Signal
        data, addr = my_socket.recvfrom(1024) # buffer size is 1024 bytes
        if data:
            new_data = data.decode("utf-8")
            print("received: %s" % new_data)
        #except Exception as e:
        #    print("Error occurred while receiving the UDP signal.")

        # Send Serial Signal 
        try:
            ser.write(new_data)
        except Exception as e:
            print("Error occurred while sending the serial signal.")

main()
