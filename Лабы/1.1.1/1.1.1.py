import matplotlib.pyplot as plt
import numpy as np
dU = [0.1]*10
dI = [1.2]*10

fig, axs = plt.subplots(nrows = 3, ncols = 1, figsize=(5,8))
def mnk(x, y):
    b=(sum(x*y)-sum(x)*sum(y)/np.size(x))/(sum(x**2)-sum(x)**2/np.size(x))
    a=(sum(y)-b*sum(x))/np.size(y)
    print(a,b)
    return [b,a]

#l=50
U1 = [576, 488, 424, 392, 344, 320, 300, 268, 252, 404]
U1 = np.array(U1)
I1 = [114.1, 97.6, 85.1, 78.4, 69.0, 64.4, 60.0, 53.5, 50.1, 80.7]
I1 = np.array(I1)
R1raw = U1 / I1
R1 = R1raw * (1 + R1raw / 500)
I1 = U1 / R1
axs[0].errorbar(I1, U1, xerr=dU, yerr=dI, fmt="o", color="r", capsize=0.1)
axs[0].set_title('График напряжения от силы тока при длине проволке 50 см')
s1=mnk(I1,U1)
x1=[50,120]
y1=[50*s1[0]+s1[1],120*s1[0]+s1[1]]
axs[0].plot(x1,y1, label=f'прямая по мнк с угловым коэффициентом {s1[0]}')

#l=30
U2 = [580, 440, 364, 324, 284, 276, 248, 224, 204, 180]
U2 = np.array(U2)
I2 = [192.74, 146.39, 120.66, 108.06, 93.85, 91.24, 82.94, 75.05, 67.33, 60.11]
I2 = np.array(I2)
R2raw = U2 / I2
R2 = R2raw * (1 + R2raw / 500)
I2 = U2 / R2
axs[1].errorbar(I2, U2, xerr=dU, yerr=dI, fmt="o", color="r", capsize=0.1)
axs[1].set_title('График напряжения от силы тока при длине проволке 30 см')
s2=mnk(I2,U2)
x2=[60,200]
y2=[60*s2[0]+s2[1],200*s2[0]+s2[1]]
axs[1].plot(x2,y2, label=f'прямая по мнк с угловым коэффициентом {s2[0]}')

#l=20
U3 = [592, 492, 400, 336, 296, 268, 248, 212, 188, 180]
U3 = np.array(U3)
I3 = [291.80, 242.35, 199.57, 165.06, 145.87, 132.36, 122.33, 105.38, 92.60, 88.23]
I3 = np.array(I3)
R3raw = U3 / I3
R3 = R3raw * (1 + R3raw / 500)
I3 = U3 / R3
axs[2].errorbar(I3, U3, xerr=dU, yerr=dI, fmt="o", color="r", capsize=0.1)
axs[2].set_title('График напряжения от силы тока при длине проволке 20 см')
s3=mnk(I3,U3)
x3=[80,300]
y3=[80*s3[0]+s3[1],300*s3[0]+s3[1]]
axs[2].plot(x3,y3, label=f'прямая по мнк с угловым коэффициентом {s3[0]}')


#проба чистого сопротивления




plt.subplots_adjust(hspace=1)



for ax in [axs[0], axs[1], axs[2]]:
    ax.grid(True, which='major', linestyle='-')
    ax.grid(True, which='minor', linestyle='--', linewidth=0.5)
    ax.minorticks_on()
    ax.set_xlabel('I, мА')
    ax.set_ylabel('U, мВ')
    ax.legend()
##    ax.set_label_coords(I1,U1,transform=None)
print(s1[1])
plt.show()
