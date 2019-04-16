import uos
import esp
import gc

esp.osdebug(None)
gc.collect()

import socket
import time
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

led = Pin(0, Pin.OUT)