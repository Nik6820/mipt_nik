import matplotlib.pyplot as plt
import pandas as pd
import matplotlib.pyplot as plt
import pandas as pd

file = open('test.csv', 'r')
N=2500
t1=[0]*N
t2=[0]*N
t3=[0]*N
n=[0]*N
for j in range(0, N):
    inp=file.readline()
    t1[j], t2[j], t3[j] = map(float, inp.split())
    n[j]=j+1
plt.plot(n, t1, color='green', label="left S", linewidth=1)
plt.plot(n, t2, color='red', label="mid S", linewidth=1)
plt.plot(n, t3, color='purple', label="right S", linewidth=1)

plt.xlabel("Количество разбиений")##подпись оси абсцисс
plt.ylabel("Значение интеграла")##подпись оси ординат
plt.legend()
plt.grid(True, which='major', linestyle='-')#мажорная сетка
plt.grid(True, which='minor', linestyle='--', linewidth=0.5)#минорная сетка
plt.minorticks_on()#обязательная функция для отображения минорной сетки
plt.show()
