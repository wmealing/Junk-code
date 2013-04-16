#!/bin/env python

import sys

filename=1
extension=".mail"
prevline = ""

f = open(str(filename) + str(extension),'w+')

with open(sys.argv[-1]) as file:
	    for line in file:
		if line.startswith("From") and prevline == "\n": 
			print "."
			f.close()
			filename += 1
			f = open(str(filename) + str(extension),'w+')
			f.write(line)
			
		else:
			prevline = line
			f.write(line)



		
print "done" 
