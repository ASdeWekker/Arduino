import uos
import esp
import gc

esp.osdebug(None)
gc.collect()

try:
	import usocket as socket
except:
	import socket
from machine import Pin
import network
import wifi

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(wifi.ssid,wifi.password)

while wlan.isconnected() == False:
	pass

print("Connection succesful")
print(wlan.ifconfig())

led = Pin(2, Pin.OUT)