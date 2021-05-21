from math import floor
from random import Random, shuffle, random, choice, seed
from functools import lru_cache, cache

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

def LIS(ST, rev=False) -> list:
	res = []
	A = ST + []
	if not rev:
		while min(A) != A[0]:
			A, _ = rotateA(A, None)
	else:
		while max(A) != A[0]:
			A, _ = rotateA(A, None)
	L = list()
	for i in range(0, len(A)):
		L.append(list())
	L[0].append(A[0])
	for i in range(1, len(A)):
		for j in range(0, i):
			if not rev:
				check = (A[j] < A[i])
			else:
				check = (A[j] > A[i])
			if check and (len(L[i]) < len(L[j])):
				'throw the previous list'
				L[i] = []
				'add all elements of L[j] to L[i]'
				L[i].extend(L[j])
		L[i].append(A[i])
	for i in range(len(A)):
		if len(L[i]) > len(res):
			res = L[i]
	return res

def find_spot_lis(stack: list, n: int, rev=False):
	if len(stack) < 2:
		return 0, 0
	best_lis = LIS(stack, rev)
	for i in range(len(stack)):
		new_stack = stack + []
		inverted = False
		if i < len(stack)/ 2:
			for _ in range(i):
					new_stack, _ = rotateA(new_stack, None)
		else:
			i = len(stack) - i
			inverted = True
			for _ in range(i):
				new_stack, _ = inv_rotateA(new_stack, None)
		new_stack, _ = pushB(new_stack, [n])
		if len(LIS(new_stack, rev)) > len(best_lis):
			if not inverted:
				return i, len(stack) - i
			else:
				return len(stack) - i, i
			break

def rotate_and_check(stack_A, stack_B, range_count, funct, lis):
	move_count = 0
	break_it = False
	for _ in range(range_count):
		# 1/10 41
		# 1/20 45
		# 1/25 47
		# 1/30 56 57 49
		# 1/40 51
		# if len(stack_B) and len(stack_B) >= items_count * (1 - 1/30):
		if len(stack_A) and len(stack_B):
			new_stackA = stack_A + []
			new_stackA, _ = pushB(new_stackA, [stack_B[0]])
			ll = LIS(new_stackA)
			# print(len(ll), len(lis), stack_B[0], stack_A == new_stackA)
			if len(ll) > len(lis):
				print('push early')
				lis = ll
				stack_A, stack_B = pushB(stack_A, stack_B)
				move_count += 1
				return stack_A, stack_B, move_count, lis, True
			new_stackA = stack_A + []
			new_stackB = stack_B + []
			lla = LIS(new_stackA)
			llb = LIS(new_stackB)
			new_stackA, new_stackB = swapA_swapB(new_stackA, new_stackB)
			new_lla = LIS(new_stackA)
			new_llb = LIS(new_stackB)
			# print(len(ll), len(lis), stack_B[0], stack_A == new_stackA)
			if len(new_lla) + len(new_llb) > len(lla) + len(llb):
				lis = new_lla
				stack_A = new_stackA
				stack_B = new_stackB
				print('swapped')
				move_count += 1
				return stack_A, stack_B, move_count, lis, True
		stack_A, stack_B = funct(stack_A, stack_B)
		move_count += 1
	return stack_A, stack_B, move_count, lis, break_it

def move_redux(mm):
	if mm:
		mm -= 1
	return mm

def next_op(slot, stack_A, stack_B, lis, move_count_in):
	global items_count
	opt_ind = slot['opind']
	mta = 0
	for _ in range(1):
		if opt_ind == 0:
			moves_A = slot['moves'][2]
			moves_B = slot['moves'][0]
			if moves_A > moves_B:
				stack_A, stack_B, mta, lis, break_it = rotate_and_check(stack_A, stack_B, moves_B, rr, lis)
				if break_it:
					break
				move_count_in += mta
				stack_A, stack_B, mta, lis, break_it = rotate_and_check(stack_A, stack_B, moves_A - moves_B, rotateA, lis)
				if break_it:
					break
				move_count_in += mta
			else:
				stack_A, stack_B, mta, lis, break_it = rotate_and_check(stack_A, stack_B, moves_A, rr, lis)
				if break_it:
					break
				move_count_in += mta
				mm = moves_B - moves_A
				mm = move_redux(mm)
				stack_A, stack_B, mta, lis, break_it = rotate_and_check(stack_A, stack_B, mm, rotateB, lis)
				if break_it:
					break
				move_count_in += mta
		elif opt_ind == 1:
			moves_A = slot['moves'][2]
			moves_B = slot['moves'][1]
			stack_A, stack_B, mta, lis, break_it = rotate_and_check(stack_A, stack_B, moves_A, rotateA, lis)
			if break_it:
				break
			move_count_in += mta
			mm = moves_B
			mm = move_redux(mm)
			stack_A, stack_B, mta, lis, break_it = rotate_and_check(stack_A, stack_B, mm, inv_rotateB, lis)
			if break_it:
				break
			move_count_in += mta
		elif opt_ind == 3:
			moves_A = slot['moves'][3]
			moves_B = slot['moves'][0]
			stack_A, stack_B, mta, lis, break_it = rotate_and_check(stack_A, stack_B, moves_A, inv_rotateA, lis)
			if break_it:
				break
			move_count_in += mta
			mm = moves_B
			mm = move_redux(mm)
			stack_A, stack_B, mta, lis, break_it = rotate_and_check(stack_A, stack_B, mm, rotateB, lis)
			if break_it:
				break
			move_count_in += mta
		else:
			moves_A = slot['moves'][3]
			moves_B = slot['moves'][1]
			if moves_A > moves_B:
				stack_A, stack_B, mta, lis, break_it = rotate_and_check(stack_A, stack_B, moves_B, rrr, lis)
				if break_it:
					break
				move_count_in += mta
				stack_A, stack_B, mta, lis, break_it = rotate_and_check(stack_A, stack_B, moves_A - moves_B, inv_rotateA, lis)
				if break_it:
					break
				move_count_in += mta
			else:
				stack_A, stack_B, mta, lis, break_it = rotate_and_check(stack_A, stack_B, moves_A, rrr, lis)
				if break_it:
					break
				move_count_in += mta
				mm = moves_B - moves_A
				mm = move_redux(mm)
				stack_A, stack_B, mta, lis, break_it = rotate_and_check(stack_A, stack_B, mm, inv_rotateB, lis)
				if break_it:
					break
				move_count_in += mta
	if not break_it:
		stack_A, stack_B = pushA(stack_A, stack_B)
		move_count_in += 1
	return stack_A, stack_B, lis, move_count_in


def get_slots(stack_A, stack_B, lis):
	slots = []
	for i, n in enumerate(stack_A):
		fc, bc = find_spot_lis(stack_B, n, rev=True)
		if n in lis:
			slots.append({
				'data': [9999, 9999, 9999, 9999]
			})
		else:
			slots.append({
				'data': [max([i, fc]), i + bc, max([len(stack_A) - i, bc]), i + fc]
			})
		slots[-1]['moves'] = [fc, bc, i, len(stack_A) - i]
	for i, s in enumerate(slots):
		slots[i]['min'] = min(s['data'])
		slots[i]['opind'] = s['data'].index((min(s['data'])))
	slots_sorted = sorted(slots, key= lambda x: x['min'])
	return slots_sorted

items_count = 5
if __name__ == '__main__':
	globa_count = []
	seed(1)
	# or_stack_A = [i for i in range(items_count, 0, -1)]
	or_stack_A = [i for i in range(items_count)]
	# or_stack_A = [1, 5, 2, 4, 3]
	shuffle(or_stack_A)
	for k in range(100):
		stack_A = or_stack_A + []
		# stack_A, _ = rotateA(stack_A, None)
		# stack_A, _ = rotateA(stack_A, None)
		# stack_A, _ = rotateA(stack_A, None)
		or_stack_A = stack_A + []
		shuffle(or_stack_A)
		stack_B = []
		move_count = 0
		lis = []
		new_stackA = stack_A + []
		ll = LIS(new_stackA)
		if len(ll) > len(lis):
			lis = ll
		# lis = []
		while len(stack_A) > len(lis):
			
			tree_width = 1
			slots_sorted = get_slots(stack_A, stack_B, lis)
			# stack_A, stack_B, lis, moves = no_res
			check_list = []
			for d in range(min(tree_width, len(stack_A))):
				no_res = next_op(slots_sorted[d], stack_A + [], stack_B + [], lis + [], move_count)
				check_list.append(no_res)
				# slots_sorted_in = get_slots(no_res[0], no_res[1], no_res[2])
				# for w in range(min(tree_width, len(no_res[0]))):
				# 	no_res_res = next_op(slots_sorted_in[w], no_res[0] + [], no_res[1] + [], no_res[2] + [], no_res[3])
				# 	slots_sorted_in_in = get_slots(no_res_res[0], no_res_res[1], no_res_res[2])
				# 	for g in range(min(tree_width, len(no_res_res[0]))):
				# 		no_res_res_res = next_op(slots_sorted_in_in[g], no_res_res[0] + [], no_res_res[1] + [], no_res_res[2] + [], no_res_res[3])
				# 		check_list.append(no_res_res_res)
				
			sorted_check = sorted(check_list, key=lambda branch: branch[3])
			sel_check = sorted_check[0]
			stack_A, stack_B, lis, mta = sel_check
			move_count = mta
			# print(mta)
		while len(stack_B):
			fc, bc = find_spot(stack_A, stack_B[0], rev=False)
			# print(stack_A)
			# print(stack_B)
			# print(fc, bc)
			# input('k')
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
		print(k, move_count)
		globa_count.append(move_count)
		print("aA", stack_A)
		print("aB", stack_B)
	print("Avg", round(sum(globa_count) / len(globa_count)))
	gcs = sorted(globa_count)
	print("Med", gcs[floor(len(gcs)/2)])
	print("Min", min(globa_count))
	print("Max", max(globa_count))
	print(globa_count)
	print(sorted(globa_count))
	LIMIT = 5500
	YES = 0
	NO = 0
	if items_count <= 100:
		LIMIT = 700
	for x in globa_count:
		if x <= LIMIT:
			YES += 1
		else:
			NO += 1
	print(round(100*YES/(YES+NO), 2))

		
