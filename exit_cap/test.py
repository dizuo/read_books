import sys, os

print(sys.argv)
#print( len(sys.argv) )

if len(sys.argv) == 2:
	res=int(sys.argv[1])
	print(res)
	exit(res )
else:
	exit(0)


