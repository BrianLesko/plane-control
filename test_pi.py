import streamlit as st
import arduino as ard

st.title("Control Input")
power = st.slider("Power", min_value=0, max_value=100, value=0)
angle = st.slider("Angle", min_value=0, max_value=180, value=95)

port = '/dev/ttyACM0'
try: 
    BAUD = 9600
    my_arduino = ard.arduino(port,BAUD,.1)
    print(f"Connection to {port} successful")
except Exception as e:
    print("Could not connect to arduino")

    throttle = 'throttle:'+str(power)
    steering = 'servo:'+str(angle)

while True:
    # Send Serial Signal 
    try:
        my_arduino.send(throttle)
        my_arduino.send(steering)
    except Exception as e:
        print("Error occurred while sending the serial signal.")