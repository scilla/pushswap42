from math import ceil, floor
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

def how_sorted(stack_A: list, stack_B):
	res = 0
	# if len(stack_A) and len(stack_B):
	# 	res += abs(stack_A[0] + stack_B[0])
	if len(stack_A) > 1:
		stack_A = stack_A.copy()
		while max(stack_A) != stack_A[-1]:
			stack_A, _ = rotateA(stack_A, None)
		for i in range(1, len(stack_A)):
			if stack_A[i] < stack_A[i-1]:
				res += 1
	if len(stack_B) > 1:
		stack_B = stack_B.copy()
		while max(stack_B) != stack_B[-1]:
			stack_B, _ = rotateA(stack_B, None)
		for i in range(1, len(stack_B)):
			if stack_B[i] < stack_B[i-1]:
				res += 1
	return res

def do_nothing(stack_A, stack_B):
	return stack_A, stack_B

def find_spot_back(stack: list, n: int, rev=False):
	if len(stack) < 2:
		return 0, 0
	effort = 0
	if not rev:
		while stack[effort - 1] > n or stack[effort] < n:
			effort += 1
	else:
		while not (stack[effort - 1] > n and stack[effort] < n):
			effort += 1
	return effort, len(stack) - effort

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

def LIS(ST):
	res = []
	A = ST + []
	# make a list of lists
	while min(A) != A[0]:
		A, _ = rotateA(A, None)
	
	L = list()
	for i in range(0, len(A)):
		L.append(list())

	# the first increasing subsequence is the first element in A
	L[0].append(A[0])

	for i in range(1, len(A)):
		for j in range(0, i):

			# a new larger increasing subsequence found
			if (A[j] < A[i]) and (len(L[i]) < len(L[j])):
				'throw the previous list'
				L[i] = []
				'add all elements of L[j] to L[i]'
				L[i].extend(L[j])
		L[i].append(A[i])

	for i in range(len(A)):
	# print an increasing subsequence
		# res.append(L[i])
		if len(L[i]) > len(res):
			res = L[i]
	return res
# A = [3, 5, 10, 0, 1, 100, 2, 4, 7]
# LIS(A)

if __name__ == '__main__':
	globa_count = []
	seed(1)
	items_count = 500
	or_stack_A = [i for i in range(items_count, 0, -1)]
	for i in range(100):
		stack_A = or_stack_A + []
		shuffle(stack_A)
		stack_A, _ = rotateA(stack_A, None)
		or_stack_A = stack_A + []
		stack_B = []
		move_count = 0
		sel = []
		new_stackA = stack_A + []
		ll = LIS(new_stackA)
		if len(ll) > len(sel):
			sel = ll
		print(len(sel), sel)
		
		sel = []
		
		# while len(stack_A) > len(sel):
		divs = 4
		itp = items_count / divs
		for b in range(divs):
			item_put = 0
			low_bound = (items_count / divs) * b
			high_bound = (items_count / divs) * (b + 1)
			print(low_bound, high_bound)
			while len(stack_B) < itp - 1:
				move_count += 1
				enne = stack_A[0]
				if low_bound <= enne < high_bound:
					stack_A, stack_B = pushA(stack_A, stack_B)
					if enne > (low_bound + high_bound) / 2:
						_, stack_B = rotateB(None, stack_B)
						move_count += 1
					continue
				stack_A, _ = inv_rotateA(stack_A, None)
			# print(stack_A)
			# print(stack_B)
			# input('k')
			while len(stack_B):
				# break
				fc, bc = find_spot(stack_A, stack_B[0], rev=False)
				if fc < bc:
					for _ in range(fc):
						stack_A, _ = rotateA(stack_A, None)
						move_count += 1
				else:
					for _ in range(bc):
						stack_A, _ = inv_rotateA(stack_A, None)
						move_count += 1
				stack_A, stack_B = pushB(stack_A, stack_B)
				move_count += 1
		move_count += int(items_count/2 - abs(stack_A[0] - items_count/2))
		print(move_count)
		globa_count.append(move_count)
		print("aA", stack_A)
		print("aB", stack_B)
	print("Avg", round(sum(globa_count) / len(globa_count)))
	print("Min", min(globa_count))
	print("Max", max(globa_count))
	print(globa_count)
	print(sorted(globa_count))
	LIMIT = 5500
	YES = 0
	NO = 0
	if items_count == 100:
		LIMIT = 700
	for x in globa_count:
		if x <= LIMIT:
			YES += 1
		else:
			NO += 1
	print(round(100*YES/(YES+NO), 2))

		
