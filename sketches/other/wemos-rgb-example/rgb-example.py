
crgb = {
	"r": 0,
	"g": 255,
	"b": 255
}
orgb = {}
nrgb = {}

import time

def led(r,g,b):
	for i in range(pixels):
		np[i] = (r,b,g)
		np.write()


# for i in range(0,255):
# 	led(i,0,i)
# 	time.sleep_ms(25)

led(200,0,200)
time.sleep(1)
led(0,200,200)
time.sleep(1)
led(200,200,0)
time.sleep(1)
led(200,0,0)
time.sleep(1)
led(0,200,0)
time.sleep(1)
led(0,0,200)
