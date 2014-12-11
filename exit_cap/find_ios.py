#!/usr/bin/python
import os, sys

if len(sys.argv) < 2:
	print "please input dir parameter..."
	exit(1)

for subdir, dirs, files in os.walk(sys.argv[1]):
	for f in files:
		fh = open(os.path.join(subdir, f), 'rb')
		head = fh.read(2)		
		if head!='PK':
			print f
		fh.close()
