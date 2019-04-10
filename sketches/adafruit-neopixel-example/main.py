import time


def led(r,g,b):
	for i in range(pixels):
		np[i] = (r,b,g)
		np.write()


while True:
	led(122,0,0)
	time.sleep(1)
	led(122,122,0)
	time.sleep(1)
	led(0,122,0)
	time.sleep(1)
	led(0,122,122)
	time.sleep(1)
	led(0,0,122)
	time.sleep(1)
	led(122,0,122)
	time.sleep(1)