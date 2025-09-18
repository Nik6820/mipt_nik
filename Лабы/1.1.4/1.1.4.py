import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

plt.grid(True, which='major', linestyle='-')#мажорная сетка
plt.grid(True, which='minor', linestyle='--', linewidth=0.5)#минорная сетка
plt.minorticks_on()


k=4000
tau=10
t=[0]*k
n=[0]*k

def taumid(k,a,tau):
    t=[]
    n=[]
    if k%tau!=0:
        k-=tau
    for i in range(1,k,tau):
        t.append(i)
        count=0
        for j in range(tau):
            count+=a[i+j-1]
        n.append(count)
        k=np.array(n)
##        k+=1
    return t,k
        
def probabilitynum(a):
    a=np.array(a)
    mx=max(a)
    num=[0.0]*(mx+1)
    value=np.array([0.0]*(mx+1))
    for i in range(mx+1):
        num[i]=i
    for i in range(len(a)):
        value[a[i]]+=1
    value=value/sum(value)
    return num, value
        
        
    

file = open('1.1.4.txt', 'r')
for i in range(1,k+1):
    n[i-1]=int(file.readline()[:-1:])

rez=taumid(k,n,tau)
rezp=probabilitynum(rez[1])
plt.bar(rezp[0],rezp[1],width=1)
##plt.hist(rezp[1], width=0.5)
##print(rez)


plt.show()
         

