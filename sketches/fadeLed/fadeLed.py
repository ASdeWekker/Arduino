import time
import machine

led = machine.PWM(machine.Pin(2))

def led_pulse(val):
	if val % 20 == 0:
		led.duty(val)
		time.sleep(0.1)

while True:
	for i in range(1024):
		led_pulse(i)
	time.sleep(0.5)
	for i in range(1023,-1,-1):
		led_pulse(i)
	time.sleep(0.5)

