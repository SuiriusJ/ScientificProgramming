import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


# 파일 이름
filename = 'output.txt'

# NumPy를 사용하여 파일에서 배열 읽기
data = np.loadtxt(filename, delimiter=' ')  # 구분자가 쉼표인 경우

# 결과
ms = np.log10(data[:, 0])
pi_est  = data[:, 1]
pi_est_err = data[:, 2]


func = lambda x, a0, a1 : a0 + a1 * x

pis_true = np.full(len(ms), np.pi)

plot_ys = np.log(np.abs(pi_est - pis_true))
plot_yerrs = pi_est_err / np.abs(pi_est-np.pi)

popt, pcov = curve_fit(func, ms, plot_ys, sigma = plot_yerrs, absolute_sigma = True)
a0opt, a1opt = popt
perr = np.sqrt(np.diag(pcov))


plt.errorbar(ms, plot_ys, yerr = plot_yerrs, fmt = 'ko')
plt.plot(ms, func(ms, a0opt, a1opt), linestyle='--')
plt.title("Error of estimated pi")
plt.xlabel('log10(# of Sample)')
plt.ylabel('log(pi_est - pi)')

plt.savefig("output/result.png")

print(f"chi^2 / DOF : {np.sum((plot_ys - func(ms, a0opt, a1opt))**2) / (len(ms) - 1)}")