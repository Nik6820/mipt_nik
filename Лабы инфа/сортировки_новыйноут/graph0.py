import matplotlib.pyplot as plt
import pandas as pd
import matplotlib.pyplot as plt
import pandas as pd

file = open('Mergediff.csv', 'r')
t1=[0]*2999
t2=[0]*2999
t3=[0]*2999
n=[0]*2999
for j in range(1, 3000):
    i=j-1
    inp=file.readline()
    t1[i], t2[i], t3[i] = map(float, inp.split())
    n[i]=j
    t1[i]=t1[i]**0.5
    t2[i]=t2[i]**0.5
    t3[i]=t3[i]**0.5
plt.plot(n, t1, color='green', label="Mergemid", linewidth=1)
plt.plot(n, t2, color='red', label="Mergegood", linewidth=1)
plt.plot(n, t3, color='purple', label="Mergebad", linewidth=1)

plt.xlabel("Количество элементов массива")##подпись оси абсцисс
plt.ylabel("Корень времени на сортировку, с")##подпись оси ординат
plt.legend()
plt.show()
