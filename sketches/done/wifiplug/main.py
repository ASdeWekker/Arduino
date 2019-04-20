s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(("", 80))
s.listen(5)


def control(arg):
	global check
	if arg == "on":
		relay.off()
		check = True
	elif arg == "off":
		relay.on()
		check = False
	elif arg == "toggle":
		try:
			if not check:
				relay.off()
				check = True
			else:
				relay.on()
				check = False
		except NameError:
			relay.on()
			check = True


def parser(get_request):
	params = {}
	arguments = get_request.replace("/","").replace("?","").split(" ")[1].split("&")

	for args in arguments:
		arg = args.split("=")
		params[arg[0]] = arg[1]

	if "power" in params:
		control(params["power"])


while True:
	conn, addr = s.accept()
	parser(str(conn.recv(1024)))
	conn.sendall("Processed.\n")
	conn.close()