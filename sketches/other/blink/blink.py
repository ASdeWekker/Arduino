import time
from machine import Pin

led = Pin(2, Pin.OUT)

while True:
	led.off()
	time.sleep(0.1)
	led.on()
	time.sleep(0.1)
