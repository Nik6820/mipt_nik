import matplotlib.pyplot as plt
import numpy as np
plt.rcParams.update({'font.size': 16})##размер текста
def mnk(x, y):
    k=(sum(x*y)-sum(x)*sum(y)/np.size(x))/(sum(x**2)-sum(x)**2/np.size(x))
    b=(sum(y)-k*sum(x))/np.size(y)
    #print(k)
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
    return(delk*a, delb*b)


h=[0.0,0.3,1.0,2.3,4.0,6.3,9.0,12.3,16.0,20.3,25.0,30.3,36.0,42.3,49.0,56.3,64.0]
dh=[0]*17
for i in range(17):
    dh[i]=i/10
I=[10.1, 10.2, 10.3, 10.5, 10.8, 11.2, 11.6, 12.0, 12.7, 13.3, 14.1, 15.0, 15.8, 16.8, 17.9, 19.1, 20.3]
dI=[0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.6,0.6,0.6,0.7,0.7,0.7,0.8,0.8,0.9]
I=np.array(I)
I=I/1000
dI=np.array(dI)
dI=dI/1000
h=np.array(h)
h=h/10000
dh=np.array(dh)
dh=dh/10000
print(h)
plt.errorbar(h, I, xerr=dh, yerr=dI, fmt="o", color="r", capsize=0.1)
s1=mnk(h,I)
x1=[0,64/10000]
y1=[0*s1[0]+s1[1],64*s1[0]/10000+s1[1]]
print(s1[0],s1[1], end='\n')
print(dmnk(h,I,s1[0],s1[1]))
plt.plot(x1,y1)

plt.xlabel("Квадрат смещения полуцилиндров относительно центра h^2, м")
plt.ylabel("Момент инерции системы, кг*м^2")
plt.title("Зависимость момента инерции системы от квадрата смещения тел от оси вращения")
plt.show()
