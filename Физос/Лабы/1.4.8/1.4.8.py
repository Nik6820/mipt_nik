import matplotlib.pyplot as plt
import numpy as np
import random

def mnk(x, y):
    k=(sum(x*y)-sum(x)*sum(y)/np.size(x))/(sum(x**2)-sum(x)**2/np.size(x))
    b=(sum(y)-k*sum(x))/np.size(y)
    print(k)
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
    return(delk*a)

#fm = np.array([3.247, 6.510, 9.747, 12.987, 16.223])
fm = np.array([3.805, 7.611, 11.413, 15.215, 19.013])
fs = np.array([4.125, 8.262, 12.381, 16.512, 20.636])
fd = np.array([4.236, 8.476, 12.710, 16.945, 21.172])
x = np.array([1, 2, 3, 4, 5])

koef1, koef2 = mnk(x, fd)
x1=[-koef2/koef1, 5]
y1=[0, 5*koef1+koef2]
plt.plot(x1, y1, color = 'gray', label = 'Дюраль')
plt.scatter(x, fd, color =  'gray', label=f'', s = 30, linewidth = 0) # наносим прямую и задаем ей название
print(dmnk(x,fd,koef1,koef2))

koef1, koef2 = mnk(x, fs)
x2=[-koef2/koef1, 5]
y2=[0, 5*koef1+koef2]
plt.plot(x2, y2, color = 'black', label = 'Сталь', linestyle = '--')
plt.scatter(x, fs, color = 'black', label=f'', s = 30, linewidth = 0) # наносим прямую и задаем ей название
print(dmnk(x,fs,koef1,koef2))

koef1, koef2 = mnk(x, fm)
x3=[-koef2/koef1, 5]
y3=[0, 5*koef1+koef2]
plt.plot(x3, y3, color = 'red', label = 'Медь', linestyle = '-.')
plt.scatter(x, fm, color = 'red', label=f'', s = 30, linewidth = 0) # наносим прямую и задаем ей название
print(dmnk(x,fm,koef1,koef2))

plt.grid(True, which='major', linestyle='-')#мажорная сетка
plt.grid(True, which='minor', linestyle='--', linewidth=0.5)#минорная сетка
plt.minorticks_on()#обязательная функция для отображения минорной сетки
plt.xlabel('Значения n', fontsize=12)#подпись оси X
plt.ylabel('Частота резонанса, кГц',fontsize=12)#подпись оси Y
plt.legend()#отображение названия прямой
plt.title("Зависимость резонансной частоты, от количества полупериодов", fontsize=14)
plt.show()#воспроизведение всех графиков на экран