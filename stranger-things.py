import serial
from playsound import playsound

arduino = serial.Serial( '/dev/cu.usbmodem144201', 115200, timeout=.1 )
while True:
	data = arduino.readline()[:-2] #the last bit gets rid of the new-line chars
	if data:
		decoded_data = data.decode()
		if ( decoded_data.endswith( '.mp3' ) ) :
			playsound( "audio/" + data.decode() )
		else:
			print( decoded_data )