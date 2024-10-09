import serial
import time

porta_serial = 'COM3' 
baud_rate = 9600
timeout = 1

ser = serial.Serial(porta_serial, baudrate=baud_rate, timeout=timeout)

comando = input()[0]

while comando != '9':	
	ser.write(comando.encode())

	resposta = ser.readline().decode('utf-8').strip()

	print(f'Resposta do Arduino: {resposta}')

	comando = input()[0]

ser.close()


