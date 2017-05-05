import time
import Adafruit_BBIO.GPIO as GPIO
import Adafruit_BBIO.ADC as ADC
import socket

HOST = '10.7.120.5'  # Endereco IP do Servidor
PORT = 5000            # Porta que o Servidor esta
udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
dest = (HOST, PORT)

GPIO.setup("P9_14", GPIO.IN)

ADC.setup();

def controleDirecao():
	value = ADC.read("P9_40")
	if (value * 4096) > 2500:
		return "D"

	elif (value * 4096) < 2048:
		return "E"

	return ""

def controleArmadura():
	value = ADC.read("P9_38")
	if( value < 300):
		return "A"
	return ""

def controleTiro():
	if GPIO.input("P9_14"):
		return "T"
	else:
		return ""


print 'Para sair use CTRL+X\n'

msg = controleDirecao + ":" + controleArmadura + ":" + controleTiro + ":"

while msg <> '\x18':
    udp.sendto (msg, dest)
    msg = controleDirecao + ":" + controleArmadura + ":" + controleTiro + ":"
    time.sleep(0.1)

udp.close()
