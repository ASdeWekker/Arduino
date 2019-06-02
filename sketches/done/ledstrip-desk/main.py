''' Ik wil dat de strip via led wordt aangeroepen.
	En dat je dan zelf extra argumenten mee kan geven
	zoals aan/uit, kleur en fade aan/uit of fade
	naar een andere kleur.

	Het lijkt mij daarnaast handiger om de technische
	en opstartcode in die bestand te houden en om dan
	voor de ledstrip controle functie een extra
	ledstrip-desk.h bestand aan te maken en die te
	includen.

	Daarnaast wil ik de volgende functies/argumenten
	implementeren.
	$stripColor: gebruikt het color argument:
	- gooi er drie kleurcodes in die door de strip
	toegepast worden, hier moet nog een integratie
	met fade bij zitten.
	$ledControl: gebruikt het aan/uit argument:
	- zet de strip uit met het command on, off
	of toggle. Integreer dit met fade om het uit
	te laten faden. Moet even nagedacht worden
	of er altijd een fade functie in moet zitten,
	ik ga het gewoon testen en kijken wat ik het
	meest gebruik.
	$fade: laat de strip aan/uit of naar een andere
	kleur faden:
	- Integreer dit met stripColor en ledControl,
	wanneer er een andere vooringestelde kleur wordt
	geselecteerd zoals blauw kan dit met een fade
	veranderen. Ook kan er voor het aan en uitgaan
	een fade worden toegepast.
	$pulse: laat de strip van de ene kleur naar de
	andere kleur pulsen:
	- Geef twee kleuren (dit kan dus ook zwart zijn)
	en een tijd mee hoe lang er tussen de pulse moet
	zitten, het moet ook mogelijk zijn om later de
	kleur en de tijd los van elkaar aan te passen.
	Bij de kleur wordt dan eerst de oude kleur
	gespecificeerd.

	Alle functienamen kunnen nog veranderd worden.
'''

## Some nerdy connection stuff.
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(("", 80))
s.listen(5)

## RGB values, also for old and new values.
crgb = {
	"r": 0,
	"g": 255,
	"b": 255
}
orgb = {}
nrgb = {}


## A function which takes rgb values as arguments
#  and update the strip with this color.
def led(r,g,b):
	for i in range(pixels):
		np[i] = (r,b,g)
		np.write()


## Function to check if the strip should be
#  powered on or off, also works with toggle.
def control(arg):
	global check
	if arg == "on":
		led(crgb["r"],crgb["g"],crgb["b"])
		check = True
	elif arg == "off":
		led(0,0,0)
		check = False
	elif arg == "toggle":
		try:
			if not check:
				led(crgb["r"],crgb["g"],crgb["b"])
				check = True
			else:
				led(0,0,0)
				check = False
		except NameError:
			led(crgb["r"],crgb["g"],crgb["b"])
			check = True


## A function to fade to another color or fade to power off.
#def fade():


#def pulse():


## A function to take a color value like 'yellow'
#  and change the color to this. Can also power on the strip.
def color(color):
	if color == "red":
		led(200,0,0)
	elif color == "green":
		led(0,200,0)
	elif color == "blue":
		led(0,0,200)
	elif color == "yellow":
		led(200,200,0)
	elif color == "purple":
		led(200,0,200)
	elif color == "lightblue":
		led(0,200,200)


## A function to take an RGB value and change the color to this.
#  Can also power on the strip.
def rgb(color):
	args = color.split(",")
	for i in range(3):
		args[i] = int(float(args[i]))
	led(args[0],args[1],args[2])


## Function which takes the GET request and extracts the parameters from it.
def parser(get_request):
	arguments = get_request.replace("/","").replace("?","").split(" ")[1].split("&")

	params = {}
	for args in arguments:
		arg = args.split("=")
		params[arg[0]] = arg[1]

	if "power" in params:
		control(params["power"])

	if "color" in params:
		color(params["color"])

	if "rgb" in params:
		rgb(params["rgb"])


## The while loop to execute everything.
while True:
	conn, addr = s.accept()
	request = str(conn.recv(1024))

	parser(request)

	conn.sendall("Processed.\n")
	conn.close()
