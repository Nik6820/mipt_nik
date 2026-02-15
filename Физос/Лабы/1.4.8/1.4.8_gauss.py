import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# Данные
x_data = np.array([4.23624, 4.2354, 4.23477, 4.23365, 4.23073, 4.2356, 4.23501,
                   4.23425, 4.23678, 4.23754, 4.23858, 4.24136, 4.23633, 4.23691, 4.2377])
y_data = np.array([1, 0.8, 0.6, 0.4, 0.2, 0.92, 0.72, 0.52, 0.8, 0.6, 0.4, 0.2, 0.92, 0.72, 0.52])

# Функция Гаусса с базовым уровнем
def gaussian(x, A, mu, sigma, baseline):
    return A * np.exp(-(x - mu)**2 / (2 * sigma**2)) + baseline

# Подбор параметров
initial_guess = [1, 4.236, 0.001, 0.2]
bounds = ([0.5, 4.23, 0.0001, 0], [2, 4.25, 0.01, 0.5])

popt, pcov = curve_fit(gaussian, x_data, y_data, p0=initial_guess, bounds=bounds)
A, mu, sigma, baseline = popt

# Целевое значение
target_y = 1 / np.sqrt(2)

# Находим точки пересечения с целевым значением
if target_y > baseline:
    delta_x = sigma * np.sqrt(-2 * np.log((target_y - baseline) / A))
    x1 = mu - delta_x
    x2 = mu + delta_x
else:
    x1 = x2 = np.nan
    print("Целевое значение ниже базового уровня!")

# Вычисляем качество аппроксимации
y_pred = gaussian(x_data, A, mu, sigma, baseline)
residuals = y_data - y_pred
rmse = np.sqrt(np.mean(residuals**2))
r_squared = 1 - np.sum(residuals**2) / np.sum((y_data - np.mean(y_data))**2)

# Вывод результатов
print("=" * 50)
print("РЕЗУЛЬТАТЫ АППРОКСИМАЦИИ")
print("=" * 50)
print(f"Параметры гауссовой кривой:")
print(f"  Амплитуда (A)    = {A:.5f}")
print(f"  Центр (μ)        = {mu:.5f}")
print(f"  Ширина (σ)       = {sigma:.5f}")
print(f"  Базовый уровень  = {baseline:.5f}")
print(f"  Качество аппроксимации:")
print(f"    R² = {r_squared:.4f}")
print(f"    RMSE = {rmse:.4f}")
print()
print(f"Целевое значение: 1/√2 = {target_y:.4f}")
print()
if not np.isnan(x1):
    print(f"Точки пересечения с y = 1/√2:")
    print(f"  x₁ = {x1:.5f}, y = {target_y:.4f}")
    print(f"  x₂ = {x2:.5f}, y = {target_y:.4f}")
    print(f"  Расстояние между точками: {abs(x2 - x1):.5f}")
else:
    print("Нет пересечений с целевым значением!")

x_fit = np.linspace(x_data.min() - 0.002, x_data.max() + 0.002, 1000)
y_fit = gaussian(x_fit, A, mu, sigma, baseline)

plt.scatter(x_data, y_data, color='blue', s=60, label='Экспериментальные данные', zorder=5)
plt.plot(x_fit, y_fit, 'r-', linewidth=2, label=f'Гаусс')

if not np.isnan(x1):
    plt.axhline(y=target_y, color='green', linestyle='--', alpha=0.7, label=f'y = 1/√2')
    plt.axvline(x=x1, color='green', linestyle='--', alpha=0.7)
    plt.axvline(x=x2, color='green', linestyle='--', alpha=0.7)
    plt.plot([x1, x2], [target_y, target_y], 'go', markersize=8)

plt.xlabel('Частота, КГц', fontsize=12)
plt.ylabel('Амплитуда, о.е.', fontsize=12)
plt.title('Аппроксимация нормализованных данных распределением Гаусса', fontsize=14)
plt.legend()
plt.grid(True, alpha=0.3)
plt.grid(True, which='major', linestyle='-')#мажорная сетка
plt.grid(True, which='minor', linestyle='--', linewidth=0.5)#минорная сетка
plt.minorticks_on()#обязательная функция для отображения минорной сетки
plt.show()

# Дополнительная информация о точках пересечения
if not np.isnan(x1):
    print("\n" + "=" * 50)
    print("ДОПОЛНИТЕЛЬНАЯ ИНФОРМАЦИЯ")
    print("=" * 50)
    print(f"Значения функции в точках пересечения:")
    print(f"  gaussian(x₁) = {gaussian(x1, A, mu, sigma, baseline):.6f}")
    print(f"  gaussian(x₂) = {gaussian(x2, A, mu, sigma, baseline):.6f}")
    print(f"  Целевое значение = {target_y:.6f}")
    print(f"  Погрешность: {abs(gaussian(x1, A, mu, sigma, baseline) - target_y):.6f}")