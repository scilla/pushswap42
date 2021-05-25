from random import shuffle, randrange
import sys

def gen_num(cc):
	res = [x for x in range(cc)]
	shuffle(res)
	return list(res)

res = gen_num(int(sys.argv[1]))
print(' '.join(map(str, res)))