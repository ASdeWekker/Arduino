import uos
import esp
import gc

esp.osdebug(None)
gc.collect()

try:
	import usocket as socket
except:
	import socket
try:
	import utime as time
except:
	import time
try:
	import urequest as request
except:
	import request
from machine import Pin
import network
import wifi

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(wifi.ssid,wifi.password)

while wlan.isconnected() == False:
	pass

print("\nConnection succesful")
print(str(wlan.ifconfig()[0]))

led = Pin(2, Pin.OUT)