import uos
import esp
import gc

esp.osdebug(None)
gc.collect()

import time
from machine import Pin

led = Pin(2, Pin.OUT)