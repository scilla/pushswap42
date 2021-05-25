from random import shuffle, randrange
from itertools import permutations
import os
import subprocess

c_arr = []

def all_comb():
	arr = [str(x) for x in range(10)]
	ff = [list(r) for r in permutations(arr)]
	return list(ff)

allc = all_comb()
print('all_comb', len(allc))
for arr in allc:
	cmds = ['./push_swap'] + arr
	res = subprocess.run(cmds, stdout=subprocess.PIPE)
	count = len(res.stdout.decode().split('\n'))
	#if count > 12:
	# 	print(arr)
	print(count, end= ' -> ')
	c_arr.append(count)
	cmds = ['./checker'] + arr
	#res_check = subprocess.run(cmds, input=res.stdout, stdout=subprocess.PIPE)
	#print(res_check.stdout.decode())


print('Max:', max(c_arr))
print('Min:', min(c_arr))
print('Avg:', round(sum(c_arr)/len(c_arr)))
c_arr = sorted(c_arr)
print('Med:', c_arr[round(len(c_arr)/2)])
print('test len:', len(c_arr))