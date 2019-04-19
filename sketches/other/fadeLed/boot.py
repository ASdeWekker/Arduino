import esp
import uos
import gc

esp.osdebug(None)
gc.collect()

import time
import machine

led = machine.PWM(machine.Pin(2, machine.Pin.OUT))