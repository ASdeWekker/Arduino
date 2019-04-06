
import machine
import time
import network
import socket

import wifi

sta_if = network.WLAN(network.STA_IF)
sta_if.active(True)
sta_if.connect(wifi.ssid,wifi.password)

addr = socket.getaddrinfo("0.0.0.0", 80)[0][-1]

s = socket.socket()
s.bind(addr)
s.listen(1)
'''
while True:
	cl, addr = s.accept()
	print("client connected from", addr)
	cl.send("<h1>Alex de Wekker</h1>")
	cl.close()
'''