import sys,os

if len(sys.argv) < 2:
	exit(12)

fh=open( str(sys.argv[1]), 'rb' )
head=fh.read(2)
if head != 'PK':
	fh.close()
	exit(1)
exit(0)

