import numpy as np
from scipy.integrate import odeint

# Параметры
omega_0 = 2 * np.pi / 1.329  # собственная частота
TIMER_FREQ = 1193180.0
delta_phi_n = 0.005208701185

# Экспериментальные данные
phi_prime_start = 1.993
phi_prime_end = 1.469
n_crossings = 101
T_avg = 1.329
t_segment = n_crossings * T_avg / 2  # полупериоды

# Численный подбор β
# Модель: φ'(t) = φ'₀ * exp(-β*t)
beta_fitted = -np.log(phi_prime_end / phi_prime_start) / t_segment

print(f"Подобранный β = {beta_fitted:.6f} с⁻¹")

# Уравнения движения
def pendulum(state, t, beta, omega_0):
    phi, phi_dot = state
    return [phi_dot, -beta*phi_dot - omega_0**2*np.sin(phi)]

# Численное интегрирование
t = np.linspace(0, 50*T_avg, 5000)
sol = odeint(pendulum, [0.0, phi_prime_start], t, args=(beta_fitted, omega_0))

phi_spiral = sol[:, 0]
phi_dot_spiral = sol[:, 1]

# Фазовый портрет
import matplotlib.pyplot as plt

plt.figure(figsize=(12, 12))

# Сепаратриса
phi_sep = np.linspace(-np.pi, np.pi, 500)
phi_dot_sep = omega_0 * np.sqrt(2*(1 + np.cos(phi_sep)))
plt.plot(phi_sep, phi_dot_sep, 'r--', lw=3, alpha=0.7, label='Сепаратриса')
plt.plot(phi_sep, -phi_dot_sep, 'r--', lw=3, alpha=0.7)

# Эллипсы
for i in range(12):
    frac = 1 - i/11
    amp_phi = 0.8 * frac
    amp_phi_dot = phi_prime_start * frac
    t_ellipse = np.linspace(0, 2*np.pi, 100)
    plt.plot(amp_phi*np.sin(t_ellipse), amp_phi_dot*np.cos(t_ellipse),
             'b-', lw=1.5, alpha=0.4)

# Спираль
plt.plot(phi_spiral, phi_dot_spiral, 'orange', lw=2.5, 
         alpha=0.9, label='Траектория с затуханием')

# Точки равновесия
plt.plot(0, 0, 'go', markersize=12, label='Устойчивое равновесие')
plt.plot([np.pi, -np.pi], [0, 0], 'rx', markersize=15, mew=3)

plt.xlabel('угол поворота φ (рад)', fontsize=14)
plt.ylabel('угловая скорость φ\'/φ₀', fontsize=14)
plt.title(f'Фазовый портрет (β={beta_fitted:.4f} с⁻¹)', fontsize=16, fontweight='bold')
plt.grid(True, ls=':', alpha=0.3)
plt.legend(fontsize=12)
plt.xlim(-3.5, 3.5)
plt.ylim(-10, 10)
plt.axhline(0, color='k', lw=0.5)
plt.axvline(0, color='k', lw=0.5)

plt.tight_layout()
plt.show()