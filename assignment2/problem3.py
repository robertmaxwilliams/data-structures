"""
Minimum sum and max product subsequence
"""
from random import randint as dice
import matplotlib.pyplot as plt
import time

def gen_seq(length):
    seq = list()
    for _ in range(length):
        seq.append(dice(-100, 100))
    return tuple(seq)

def max_product_forward(seq):
    """
    tried to find max product by multing everything since last zero
    fails with odd number of negatives tail heavy, so needs to be ran twice, 
    once forward and once negative, to ensure those solutions aren't hiding from us
    Only works for whole number lists
    """
    this_start = 0
    this_product = 1
    max_product = 0
    max_start, max_end = (0, 0)
    for i, x in enumerate(seq):
        this_product *= x

        if x == 0:
            this_start = i+1
            this_product = 1
            continue

        if this_product > max_product:
            max_product = this_product
            max_start, max_end = this_start, i+1

        ##print(seq[max_start:max_end])

    return (max_product, max_start, max_end)

def max_product(seq):
    """
    calls max_product_forward with seq and seq reversed, and returns whichever one
    makes the bigger number
    """
    forward_sum, forward_start, forward_end = max_product_forward(seq)
    backward_sum, backward_start, backward_end = max_product_forward(seq[::-1])

    if forward_sum > backward_sum:
        return seq[forward_start:forward_end]
    else:
        return (seq[::-1][backward_start:backward_end])[::-1]
    
##print(max_product([1, 2, 3, 0, 4, -2, 4, -2, 10, -2, 1000, 0, 1, 0, 10, 10, 0, 12]))

ys = list()
xs = list()
for n in range(2, 30):
    #seq = gen_seq(n)
    for _ in range(100):
        seq = gen_seq(n)
        ys.append(n)
        start = time.time()
        max_product(seq)
        xs.append((time.time()-start)*10**6) 

plt.plot(ys, xs, '.')
plt.title('Different list every point')
plt.ylabel('running time in micro seconds')
plt.xlabel('length of list')
plt.show()
