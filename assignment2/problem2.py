import csv
import time

def func_a(n):
    summ = 0
    for i in range(n):
        summ += 1
    return summ

def func_b(n):
    summ = 0
    for i in range(n):
        for j in range(n):
            summ += 1

    return summ

def func_c(n):
    summ = 0
    for i in range(n):
        for j in range(n**2):
            summ += 1

    return summ

def func_d(n):
    summ = 0
    for i in range(n):
        for j in range(i):
            summ += 1

    return summ

def func_e(n):
    summ = 0
    for i in range(n):
        for j in range(i**2):
            for k in range(j):
                summ += 1

    return summ

def func_f(n):
    summ = 0
    for i in range(1, n):
        for j in range(1, i**2):
            if j % i == 0:
                for k in range(j):
                    summ += 1

    return summ

with open('function-times.csv', 'w') as csvfile:
    writer = csv.writer(csvfile)
    
    fieldnames = ['n', 'a, steps', 'a, time', 'b, steps', 'b, time', 'c, steps', 'c, time', 
                  'd, steps', 'd, time', 'e, steps', 'e, time', 'f, steps', 'f, time']
    writer.writerow(fieldnames)
    for n in range(70):
        row = [n]
        for func in [func_a, func_b, func_c, func_d, func_e, func_f]:
            start = time.time()
            count = func(n)
            duration = (time.time() - start)*10**7
            print(n, count, duration)
            row += [count, duration]
        writer.writerow(row)
