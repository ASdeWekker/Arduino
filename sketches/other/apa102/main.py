## For led stuff.

import machine
import apa102

strip = apa102.APA102(machine.Pin(5), machine.Pin(4), 10)

strip.ORDER = (0,1,2,3)

for i in range(10):
	strip[i] = (0,255,255,100)

strip.write()
