import matplotlib.pyplot as plt
import numpy as np
def mnk(x, y):
    k=(sum(x*y)-sum(x)*sum(y)/np.size(x))/(sum(x**2)-sum(x)**2/np.size(x))
    b=(sum(y)-k*sum(x))/np.size(y)
    print(k*2, b)
    return [k, b]
def dmnk(x,y,a,b):
    x1=sum(x)/np.size(x)
    dxx=0
    for i in range(np.size(x)):
        dxx+=(x[i]-x1)**2
    dxx=dxx/np.size(x)
    y1=sum(y)/np.size(y)
    dyy=0
    for i in range(np.size(y)):
        dyy+=(y[i]-y1)**2
    dyy=dyy/np.size(y)
    delk=(1/(np.size(x)-2)*(dyy/dxx-a**2))**0.5
    delb=delk*(sum(x**2)/np.size(x))**0.5
    print(delk*a, delb*b)
    return(delk*a)



t_n=[0.1193 , 0.2088 , 0.2856 , 0.3527 , 0.4120]
t_n = np.array(t_n)
y_n=[0]*5
for i in range(1,6):
    y_n[i-1]=i*0.4/t_n[i-1]
y_n = np.array(y_n)
s1=mnk(t_n,y_n)#получаем массив, где первый элемент k,  второй b (y=kx+b)
dmnk(t_n,y_n,s1[0],s1[1])
x1=[0,0.5]#заводим две точки для прямой
y1=[0*s1[0]+s1[1],0.5*s1[0]+s1[1]]
plt.grid(True, which='major', linestyle='-')#мажорная сетка
plt.grid(True, which='minor', linestyle='--', linewidth=0.5)#минорная сетка
plt.minorticks_on()
plt.xlabel('t_n, с')#подпись оси X
plt.ylabel('nl/t_n, м/с')#подпись оси Y
plt.scatter(t_n,y_n)
plt.plot(x1,y1)
plt.show()
