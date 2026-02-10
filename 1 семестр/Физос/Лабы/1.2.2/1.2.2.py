import matplotlib.pyplot as plt
import numpy as np

def mnk(x, y):
    k=(sum(x*y)-sum(x)*sum(y)/len(y))/(sum(x**2)-sum(x)**2/len(y))
    b=(sum(y)-k*sum(x))/len(y)
    sigma_k = (1/(len(x))**0.5)*((sum(y*y)-sum(y)*sum(y)/len(y))/(sum(x*x)-sum(x)*sum(x)/len(y))-k*k)**0.5
    sigma_b = sigma_k*(sum(x*x)-sum(x)*sum(x)/len(x))**0.5
    print("k: ", k, sigma_k, "b: ", b, sigma_b)
    return k, b 



x=np.array([0.17**2, 0.09**2])
y=np.array([1/39.184164096547306, 0.034/1.4])
k, b = mnk(x, y)
print(b)
plt.plot(x,y)
plt.grid(True, which='major', linestyle='-')#мажорная сетка
plt.grid(True, which='minor', linestyle='--', linewidth=0.5)#минорная сетка
plt.minorticks_on()#обязательная функция для отображения минорной сетки
plt.xlabel('Момент силы натяжения, Н*м')#подпись оси X
plt.ylabel('Начальное угловое ускорение, рад/c^2')#подпись оси Y
plt.legend()#отображение названия прямой

plt.show()#воспроизведение всех графиков на экран