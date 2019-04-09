s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(("", 80))
s.listen(5)

while True:
	conn, addr = s.accept()
	request_raw = conn.recv(1024)
	request = str(request_raw)
	request_enc = request_raw.decode("utf8")
	led_on = request.find("/?led=on")
	led_off = request.find("/?led=off")

	if led_on == 6:
		print("Led on")
		print(led_on)
		print(led_off)
		led.value(1)
		print("\nRaw\n", request_raw)
		print("\nNormal\n", request)
		print("\nEnc\n", request_enc)

	if led_off == 6:
		print("Led off")
		print(led_on)
		print(led_off)
		led.value(0)
		print(request)

	conn.sendall("Processed.\n")
	conn.close()