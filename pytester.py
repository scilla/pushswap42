from random import shuffle, randrange
import os
import subprocess

c_arr = []

def gen_num():
	res = set()
	while len(res) < 98:
		x = randrange(-2147483647, 2147483646)
		# x = randrange(0, 10)
		res.add(str(x))
	res.add(str(-2147483648))
	res.add(str(2147483647))
	return list(res)

for i in range(100):
	arr = gen_num()
	# args = ' '.join(map(str, arr))
	# cmd = f'./push_swap {args} | ./checker {args}'
	# cmd = f'./push_swap {args} | wc -l'
	# print(i, end=' ')
	# os.system(cmd)
	cmds = ['./push_swap'] + arr
	res = subprocess.run(cmds, stdout=subprocess.PIPE)
	count = len(res.stdout.decode().split('\n'))
	#if count > 12:
	# 	print(arr)
	print(count, end= ' -> ')
	c_arr.append(count)
	cmds = ['./checker'] + arr
	res_check = subprocess.run(cmds, input=res.stdout, stdout=subprocess.PIPE)
	print(res_check.stdout.decode())
	if 'OK' not in res_check.stdout.decode():
		print(arr)
		print('AAAA	AAAAAAAAAAAAAAHHHHHH')
		exit()


print('Max:', max(c_arr))
print('Min:', min(c_arr))
print('Avg:', round(sum(c_arr)/len(c_arr)))
c_arr = sorted(c_arr)
print('Med:', c_arr[round(len(c_arr)/2)])