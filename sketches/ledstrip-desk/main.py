s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(("", 80))
s.listen(5)

while True:
	conn, addr = s.accept()
	request_raw = conn.recv(512)
	request = str(request_raw)
	led_on = request.find("/?led=on")
	led_off = request.find("/?led=off")

	if led_on == 6:
		print("Led on")
		print(led_on)
		print(led_off)
		led.value(1)
		print(request)

	if led_off == 6:
		print("Led off")
		print(led_on)
		print(led_off)
		led.value(0)
		print(request)

	conn.sendall("Processed.\n")
	conn.close()