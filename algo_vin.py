from random import Random, shuffle, random, choice, seed

def pushA(stack_A, stack_B):
	if len(stack_A):
		stack_B.insert(0, stack_A[0])
		stack_A = stack_A[1:]
	return stack_A, stack_B

def pushB(stack_A, stack_B):
	if len(stack_B):
		stack_A.insert(0, stack_B[0])
		stack_B = stack_B[1:]
	return stack_A, stack_B

def swapA(stack_A, stack_B):
	if len(stack_A) > 1:
		tmp = stack_A[0] + 0
		stack_A[0] = stack_A[1]
		stack_A[1] = tmp
	return stack_A, stack_B

def swapB(stack_A, stack_B):
	if len(stack_B) > 2:
		tmp = stack_B[0] + 0
		stack_B[0] = stack_B[1]
		stack_B[1] = tmp
	return stack_A, stack_B

def swapA_swapB(stack_A, stack_B):
	stack_A, stack_B = swapA(stack_A, stack_B)
	stack_A, stack_B = swapB(stack_A, stack_B)
	return stack_A, stack_B

def rotateA(stack_A, stack_B):
	if len(stack_A) > 1:
		tmp = stack_A[0] + 0
		stack_A.append(tmp)
		stack_A = stack_A[1:]
	return stack_A, stack_B

def rotateB(stack_A, stack_B):
	if len(stack_B) > 1:
		tmp = stack_B[0] + 0
		stack_B.append(tmp)
		stack_B = stack_B[1:]
	return stack_A, stack_B

def rr(stack_A, stack_B):
	stack_A, stack_B = rotateA(stack_A, stack_B)
	stack_A, stack_B = rotateB(stack_A, stack_B)
	return stack_A, stack_B

def inv_rotateA(stack_A, stack_B):
	if len(stack_A) > 1:
		tmp = stack_A[-1] + 0
		stack_A.insert(0, tmp)
		stack_A = stack_A[:-1]
	return stack_A, stack_B

def inv_rotateB(stack_A, stack_B):
	if len(stack_B) > 1:
		tmp = stack_B[-1] + 0
		stack_B.insert(0, tmp)
		stack_B = stack_B[:-1]
	return stack_A, stack_B

def rrr(stack_A, stack_B):
	stack_A, stack_B = inv_rotateA(stack_A, stack_B)
	stack_A, stack_B = inv_rotateB(stack_A, stack_B)
	return stack_A, stack_B

def count_over(stack, n):
	res = 0
	for x in stack:
		if x > n:
			res += 1
	return res

def find_spot(stack: list, n: int, rev=False):
	if len(stack) < 2:
		return 0, 0
	if n > max(stack) or n < min(stack):
		if not rev:
			effort = stack.index(max(stack))
		else:
			effort = stack.index(min(stack))
		return effort + 1, len(stack) - effort - 1
	effort = 0
	if not rev:
		while stack[effort - 1] > n or stack[effort] < n:
			effort += 1
	else:
		while not (stack[effort - 1] > n and stack[effort] < n):
			effort += 1
	return effort, len(stack) - effort

if __name__=='__main__':
	seed(2)
	move_count = 0
	stack_A = [x for x in range(500)]
	shuffle(stack_A)
	stack_B = []
	while len(stack_A):
		index_list = []
		for i, n in enumerate(stack_A):
			res = count_over(stack_A[i:], n)
			index_list.append(res)
		# print('s',stack_A)
		# print('i', index_list)
		moves = []
		while len(index_list):
			ind_min = index_list.index(min(index_list))
			moves.append(ind_min)
			index_list = index_list[:ind_min]
		moves.reverse()
		# print('m', moves)
		moved = 0
		for x in moves:
			moves_A = 0
			for _ in range(x - moved):
				stack_A, stack_B = rotateA(stack_A, stack_B)
				moved += 1
		move_count += moved
	print('A', stack_A)
	print('B', stack_B)
	while len(stack_B):
		fw, bw = find_spot(stack_A, stack_B[0])
		# print('A', stack_A)
		# print('B', stack_B)
		# input(f'fw {fw} bw {bw}')
		if fw <= bw:
			for _ in range(fw):
				stack_A, _ = rotateA(stack_A, stack_B)
				move_count += 1
		else:
			for _ in range(bw):
				stack_A, _ = inv_rotateA(stack_A, stack_B)
				move_count += 1
		stack_A, stack_B = pushB(stack_A, stack_B)
		move_count += 1
	print('A', stack_A)
	print('B', stack_B)
	print('move_count', move_count)
