'''
from machine import Pin
Pin(2, Pin.OUT).off()

import pyb
pyb.LED(2).off()'''

import time

count = 0
while True:
	print("ding", count)
	count += 1
	time.sleep(1)
