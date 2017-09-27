"""
Kadane’s Algorithm:

Initialize:
    max_so_far = 0
    max_ending_here = 0

Loop for each element of the array
  (a) max_ending_here = max_ending_here + a[i]
  (b) if(max_ending_here < 0)
            max_ending_here = 0
  (c) if(max_so_far < max_ending_here)
            max_so_far = max_ending_here
return max_so_far

"""
from random import randint as dice
import matplotlib.pyplot as plt
import time

def gen_seq(length):
    seq = list()
    for _ in range(length):
        seq.append(dice(-100, 100))
    return tuple(seq)

def max_subsequence(seq):
    max_so_far = 0
    max_ending_here = 0

    for i, x in enumerate(seq):
        max_ending_here += x
        if max_ending_here < 0:
            max_ending_here = 0
        if max_so_far < max_ending_here:
            max_so_far = max_ending_here
    return max_so_far

def min_subsequence(seq):
    negative_seq = (-x for x in seq)
    return -max_subsequence(negative_seq)

print(min_subsequence([1, 2, 3, -3, -4, 1, -2, -10, 20, 3]))
ys = list()
xs = list()
for n in range(2, 300):
    #seq = gen_seq(n)
    for _ in range(100):
        seq = gen_seq(n)
        ys.append(n)
        start = time.time()
        min_subsequence(seq)
        xs.append((time.time()-start)*10**6) 

plt.plot(ys, xs, '.')
plt.title('Different list every point')
plt.ylabel('running time in micro seconds')
plt.xlabel('length of list')
plt.show()
