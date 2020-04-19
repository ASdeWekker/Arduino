# The usual imports.
import machine
import time
import network
try:
	import usocket as socket
except:
	import socket

# Importing the wifi credentials.
import wifi

# Enable the network and connecting to it.
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(wifi.ssid,wifi.password)

addr = socket.getaddrinfo("0.0.0.0", 80)[0][-1]

s = socket.socket()
s.bind(addr)
s.listen(1)

print("Listening on ", addr)
print("My ip is ", wlan.ifconfig()[0])

while True:
	cl, addr = s.accept()
	cl.send("<h1>Alex</h1>")
	cl.close()
