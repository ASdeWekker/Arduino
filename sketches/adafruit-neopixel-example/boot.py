import uos
import esp
import gc

esp.osdebug(None)
gc.collect()

from machine import Pin
from neopixel import NeoPixel

global pixels
pixels = 5
np = NeoPixel(Pin(2, Pin.OUT), pixels)