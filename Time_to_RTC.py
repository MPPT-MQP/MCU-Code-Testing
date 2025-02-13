# Example PC-side code (Python, using serial)
import serial #need to make sure pyserial is installed
import datetime
import time

# Replace '/dev/tty.usbmodem14302' with the actual serial port of your Pico
ser = serial.Serial('/dev/tty.usbmodem14302', 115200)  

while True:
    now = datetime.datetime.now()
    time_str = now.strftime("%Y-%m-%d %H:%M:%S")
    ser.write(time_str.encode())
    print(f"Sent time: {time_str}")
    time.sleep(1)