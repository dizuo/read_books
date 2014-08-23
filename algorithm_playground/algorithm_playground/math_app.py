import math

def get_prime(value):
    v = 2
    while v <= math.sqrt(value):
        if value % v == 0:
            # print('==', v, value)
            break
        v += 1
    
    if v > math.sqrt(value):
        print(value)

'''
v = 40000
while v < 42000:
    get_prime(v)
    v += 1

'''

def gcd(a, b):
    if a > b:
        tmp = a
        a = b
        b = tmp
    print(a, b)
    
    while a != 0:
        tmp = b % a
        b = a
        a = tmp
        print(a, b)
    
    return b

def isUglyNumber(value):
    while value % 2 == 0:
        value = value / 2
    while value % 3 == 0:
        value = value / 3
    while value % 5 == 0:
        value = value / 5

    return value == 1

def findUglyNumber():
    value = 1
    findNum = 0

    while (findNum <= 100):
        if ( isUglyNumber(value) ):
            print(value)
            findNum += 1

        value += 1

def mod_impl(a, b):
    if (b == 0):
        print('%d\tmod\t%d\t#ERROR' % (a, b))
        return
    print( '%d\tmod\t%d\t=\t%d' % (a, b, (a%b)) )

# http://blog.csdn.net/huasion/article/details/6855900
def python_mod_test():
    print("===PYTHON_MOD_TEST===")
    # a, b 同号 #

    # a > 0 , b > 0
    mod_impl(5, 3)	# a > b
    mod_impl(5, 8)	# a < b
    mod_impl(0, 3)	# a == 0
    mod_impl(5, 0)	# b == 0

    # a < 0 , b < 0
    mod_impl(-5, -3)	# a < b
    mod_impl(-5, -8)	# a > b
    mod_impl(0, -3)	# a == 0
    mod_impl(-5, 0)	# b == 0

    # a, b 异号
    # a < 0 , b > 0
    mod_impl(-5, 3)
    mod_impl(-5, 8)
    
    # a > 0 , b < 0
    mod_impl(5, -3)
    mod_impl(5, -8)

    print("===PYTHON_MOD_TEST===")

        

    
