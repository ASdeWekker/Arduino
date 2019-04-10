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