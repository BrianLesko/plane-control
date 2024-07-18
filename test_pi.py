import streamlit as st
import arduino as ard

st.title("Control Input")

if "my_arduino" not in st.session_state:
    port = '/dev/ttyACM0'
    try: 
        BAUD = 9600
        my_arduino = ard.arduino(port,BAUD,.1)
        st.write(f"Connection to {port} successful")
        st.session_state.my_arduino = my_arduino
        st.rerun()
    except Exception as e:
        st.write("Could not connect to arduino")

if "my_arduino" in st.session_state:
    power = st.slider("Power", min_value=1000, max_value=2000, value=1000)
    left = st.slider("Left Servo", min_value=40, max_value=140, value=95)
    right = st.slider("Right Servo", min_value=40, max_value=140, value=95)

    throttle = 'throttle:'+str(power)
    Left = 'left:'+str(left)
    Right = 'right:'+str(right)

    # Send Serial Signal 
    try:
        st.session_state.my_arduino.send(throttle)
        st.session_state.my_arduino.send(Left)
        st.session_state.my_arduino.send(Right)
    except Exception as e:
        st.write("Error occurred while sending the serial signal.")
        st.write(e)