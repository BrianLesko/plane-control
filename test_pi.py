import streamlit as st
import arduino as ard

st.title("Control Input")
power = st.slider("Power", min_value=0, max_value=100, value=0)
angle = st.slider("Angle", min_value=0, max_value=180, value=95)

if "my_arduino" not in st.session_state:
    port = '/dev/ttyACM0'
    try: 
        BAUD = 9600
        my_arduino = ard.arduino(port,BAUD,.1)
        st.write(f"Connection to {port} successful")
    except Exception as e:
        st.write("Could not connect to arduino")
else:
    my_arduino = st.session_state.my_arduino
    st.write(f"Connection to arduino successful")

throttle = 'throttle:'+str(power)
steering = 'servo:'+str(angle)

# Send Serial Signal 
try:
    my_arduino.send(throttle)
    my_arduino.send(steering)
except Exception as e:
    st.write("Error occurred while sending the serial signal.")
    st.write(e)