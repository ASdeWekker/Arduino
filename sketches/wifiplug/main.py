s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(("", 80))
s.listen(5)

def led_control(arg):
	global check
	if arg == "on":
		print("led on")
		led.off()
		check = True
	elif arg == "off":
		print("led off")
		led.on()
		check = False
	elif arg == "toggle":
		if not check:
			print("led on")
			led.off()
			check = True
		else:
			print("led off")
			led.on()
			check = False


def parser(get_request):
	params = {}
	arguments = get_request.split(" ")[1].split("&")
	arguments[0] = arguments[0].replace("/","").replace("?","")
	print(arguments)

	for args in arguments:
		arg = args.split("=")
		params[arg[0]] = arg[1]
	print(params)

	if "state" in params:
		led_control(params["state"])


while True:
	conn, addr = s.accept()
	request_raw = conn.recv(1024)
	request = str(request_raw)

	parser(request)

	conn.sendall("Processed.\n")
	conn.close()
