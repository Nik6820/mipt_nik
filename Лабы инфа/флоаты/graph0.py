import matplotlib.pyplot as plt
import pandas as pd
import matplotlib.pyplot as plt
import pandas as pd

file = open('test.csv', 'r')
t1=[0]*100
t2=[0]*100
t3=[0]*100
n=[0]*100
for j in range(0, 100):
    inp=file.readline()
    t1[j], t2[j], t3[j] = map(float, inp.split())
    n[j]=j+1
plt.plot(n, t1, color='green', label="left S", linewidth=1)
plt.plot(n, t2, color='red', label="mid S", linewidth=1)
plt.plot(n, t3, color='purple', label="right S", linewidth=1)

plt.xlabel("Количество разбиений")##подпись оси абсцисс
plt.ylabel("Значение интеграла")##подпись оси ординат
plt.legend()
plt.show()
