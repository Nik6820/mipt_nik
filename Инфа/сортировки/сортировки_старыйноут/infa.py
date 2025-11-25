import random as rnd
import time
import matplotlib.pyplot as plt
"""объявление функций сортировок"""
def bubblesort(a):
    for k in range(len(a)-1):
        for i in range(len(a)-k-1):
            if a[i]>a[i+1]:
                a[i], a[i+1] = a[i+1], a[i]
    return(0)


def bubblesortPro(b):
    for k in range(len(b)-1):
        flag=True
        for i in range(len(b)-k-1):
            if b[i]>b[i+1]:
                b[i], b[i+1] = b[i+1], b[i]
                flag=False
        if flag:
            break
    return(0)


def shakersort(c):
    for k in range(len(c)//2):
        flag=True
        for i in range(k, len(c)-k-1):
            if c[i]>c[i+1]:
                c[i], c[i+1] = c[i+1], c[i]
                flag=False
        for o in range(len(c)-k-1, k, -1):
            if c[o]<c[o-1]:
                c[o],c[o-1]=c[o-1],c[o]
                flag=False
        if flag:
            break
    return(0)


def insertsort(d):
    n=len(d)
    for q in range(0,n):
        for w in range(q,0,-1):
            if d[w]<d[w-1]:
                d[w],d[w-1]=d[w-1],d[w]
    return d


def selectionsort(e):
    n=len(e)
    for y in range(n-1):
        mx=e[0]
        ind=0
        for z in range(n-y):
            if e[z]>=mx:
                mx=e[z]
                ind=z
        e[ind], e[n-y-1] = e[n-y-1], e[ind]
    return e

def countsort(arr, res):
    n=len(arr)
    counts=[0]*10
    for i in range(len(arr)):
        counts[arr[i]]+=1
    indexes = [0]*10
    for i in range(1,10):
        indexes[i] =indexes[i-1]+counts[i-1]
    result = [0]*n
    for i in range(len(arr)):
        result[indexes[arr[i]]]=res[i]
     
        indexes[arr[i]]+=1
    return(result)
 
def radixsort(ar):
    n=len(ar)
    d=[0]*n
    for i in range(n):
        d[i]=ar[i]%10
    count=1
 #ar=countsort(d,ar)
    while True:
        ar=countsort(d,ar)
        for j in range(n):
            d[j]=ar[j]//(10*count)%10
        count+=1
        if max(d)==0:
            return ar





start= time.time()

Naxis=[i for i in range(2000, 22000, 1000)]

BubbleTime=[]
BubbleProTime=[]
ShakerTime=[]
InsertTime=[]
SelectionTime=[]
RadixTime=[]

for n in range(len(Naxis)):
    countBubble=0
    countBubblePro=0
    countShaker=0
    countInsert=0
    countSelection=0
    countRadix=0
    
    for y in range(5):
        arrb=[rnd.randint(1, 1e12) for m in range(Naxis[n])]
        arrbp=arrb.copy()
        arrsh=arrb.copy()
        arrins=arrb.copy()
        arrsel=arrb.copy()
        arrrx=arrb.copy()
        print(arrb)
        
        Bts = time.time()
        bubblesort(arrb)
        Btf = time.time()
        countBubble+=Btf-Bts
        print(n+1, "i = ", y, "bubble", Btf-Bts)

        Bpts = time.time()
        bubblesortPro(arrbp)
        Bptf = time.time()
        countBubblePro+=Bptf-Bpts
        print(n+1, "i = ", y, "bubblePro", Bptf-Bpts)
        
        Sts = time.time()
        shakersort(arrsh)
        Stf = time.time()
        countShaker+=Stf-Sts
        print(n+1, "i = ", y, "shaker", Stf-Sts)
        
        Its = time.time()
        insertsort(arrins)
        Itf = time.time()
        countInsert+=Itf-Its
        print(n+1, "i = ", y, "insert", Itf-Its)
        
        Sets = time.time()
        selectionsort(arrsel)
        Setf = time.time()
        countSelection+=Setf-Sets
        print(n+1, "i = ", y, "selection", Setf-Sets)
        
        Rxts = time.time()
        radixsort(arrrx)
        Rxtf = time.time()
        countRadix+=Rxtf-Rxts
        print(n+1, "i = ", y, "radix", Rxtf-Rxts)

    BubbleTime.append((countBubble/5)**0.5)
    BubbleProTime.append((countBubblePro/5)**0.5)
    ShakerTime.append((countShaker/5)**0.5)
    InsertTime.append((countInsert/5)**0.5)
    SelectionTime.append((countSelection/5)**0.5)
    RadixTime.append((countRadix/5)**0.5)
    
    print(n)
finish= time.time()
print(finish-start) 
plt.plot(Naxis,ShakerTime,'r-')
plt.plot(Naxis,BubbleProTime,'b-')
plt.plot(Naxis,BubbleTime,'g-')
plt.plot(Naxis,InsertTime,'y-')
plt.plot(Naxis,SelectionTime,'c-')
plt.plot(Naxis,RadixTime,'m-')


plt.xlabel('N, количество элементов') #Подпись для оси х
plt.ylabel('sqrt(t), корень из среднего времени выполнения') #Подпись для оси y
plt.title('red - Shaker; blue - BubblePro; green - Bubble; yellow - Insert; cyan - Selection; magenta - Radix') #Название
plt.show()

