import uos
import esp
import gc

esp.osdebug(None)
gc.collect()

import socket
import time
from machine import Pin
from neopixel import NeoPixel
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

global pixels
pixels = 30
np = NeoPixel(Pin(2, Pin.OUT), pixels)
