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
import ipaddr

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(wifi.ssid,wifi.password)

while wlan.isconnected() == False:
	pass

wlan.ifconfig(ipaddr.ip)
print("\nConnection succesful")
print(str(wlan.ifconfig()[0]))

led = Pin(2, Pin.OUT)