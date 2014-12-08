#!/usr/bin/python
# Example using a character LCD plate.
import math
import time
import os
import requests
from ctypes import *


import Adafruit_CharLCD as LCD


lib = cdll.LoadLibrary('./example.so')

# Initialize the LCD using the pins 
lcd = LCD.Adafruit_CharLCDPlate()

# create some custom characters
lcd.create_char(1, [2, 3, 2, 2, 14, 30, 12, 0])
lcd.create_char(2, [0, 1, 3, 22, 28, 8, 0, 0])
lcd.create_char(3, [0, 14, 21, 23, 17, 14, 0, 0])
lcd.create_char(4, [31, 17, 10, 4, 10, 17, 31, 0])
lcd.create_char(5, [8, 12, 10, 9, 10, 12, 8, 0])
lcd.create_char(6, [2, 6, 10, 18, 10, 6, 2, 0])
lcd.create_char(7, [31, 17, 21, 21, 21, 21, 17, 31])

# Show some basic colors.
lcd.set_color(1.0, 0.0, 0.0)
lcd.clear()
lcd.message('RED \x01')
#time.sleep(3.0)

lcd.set_color(0.0, 1.0, 0.0)
lcd.clear()
lcd.message('GREEN \x02')
#time.sleep(3.0)

lcd.set_color(0.0, 0.0, 1.0)
lcd.clear()
lcd.message('BLUE \x03')
#time.sleep(3.0)

lcd.set_color(1.0, 1.0, 0.0)
lcd.clear()
lcd.message('YELLOW \x04')
#time.sleep(3.0)

lcd.set_color(0.0, 1.0, 1.0)
lcd.clear()
lcd.message('CYAN \x05')
#time.sleep(3.0)

lcd.set_color(1.0, 0.0, 1.0)
lcd.clear()
lcd.message('MAGENTA \x06')
#time.sleep(3.0)

lcd.set_color(1.0, 1.0, 1.0)
lcd.clear()
lcd.message('WHITE \x07')
#time.sleep(3.0)

# Show button state.
lcd.clear()
lcd.message('Press buttons...')

# Make list of button value, text, and backlight color.
colors = (  ('RED',     (1,0,0)),
            ('GREEN',   (0,1,0)),
            ('BLUE',    (0,0,1)),
            ('YELLOW',  (1,1,0)),
            ('CYAN',    (0,1,1)), 
            ('MAGENTA', (1,0,1)),
            ('WHITE',   (1,1,1)) )

print 'Press Ctrl-C to quit.'
curr  = 0
while True:
	# Loop through possible color options
	#lcd.set_color(colors[curr][1][0], colors[curr][1][1], colors[curr][1][2])
	#lcd.clear()
	#lcd.message(colors[curr][0])	
	#this is the line to change for talking to the mongoose server
	curr = requests.get("http://localhost:8282/lights/get")
	temp = curr.json()
	num = temp[u"redLED"]
	print num
	if(0 <= num <= 6 ):
		print "good number"
		lcd.set_color(colors[num][1][0], colors[num][1][1], colors[num][1][2])
		lcd.clear()
		lcd.message(colors[num][0])	
	else:
		print "bad number"
	time.sleep(3.0)
