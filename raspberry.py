import serial
import time
from datetime import datetime
import requests

#teste
porta_serial = '/dev/ttyACM0' 
baud_rate = 9600
timeout = 1

ser = serial.Serial(porta_serial, baudrate=baud_rate, timeout=timeout)

try:
    while True:
        #if datetime.now().minute == 30
        if datetime.now().hour == 20:
            ser.write("1".encode())
            while ser.in_waiting == 0:
                pass
            resposta = ser.readline().decode('utf-8').strip()
            print(f'Resposta do Arduino: {resposta}')
            time.sleep(1)
finally:
    ser.close()