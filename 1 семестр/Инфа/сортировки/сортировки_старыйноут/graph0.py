import matplotlib.pyplot as plt
import pandas as pd

file = open('n2wO0.csv', 'r')
t1=[0]*9999
t2=[0]*9999
t3=[0]*9999
n=[0]*9999
for j in range(1, 10000):
    i=j-1
    inp=file.readline()
    t1[i], t2[i], t3[i] = map(float, inp.split())
    n[i]=j
plt.plot(n, t1)
plt.plot(n, t2, color='green')
plt.plot(n, t3, color='red')
plt.show()
