import time
import machine

led = machine.PWM(machine.Pin(2))

while True:
	for i in range(0,1024,20):
		led.duty(i)
		time.sleep_ms(50)
	time.sleep(0.5)
	for i in range(1023,-1,-20):
		led.duty(i)
		time.sleep_ms(50)
	time.sleep(0.5)
	