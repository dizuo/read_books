#np++

res = 0
x = 1
while x < 9:
	res = (res<<4) | x
	
	str = bin(res)[2:]
	xlen = 4 - len(str) % 4
	prefix = ''
	for i in range(xlen):
		prefix += '0'
	print res, prefix + str
	
	x = x + 1
