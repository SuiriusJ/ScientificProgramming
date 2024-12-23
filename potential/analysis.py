import numpy as np
import matplotlib.pyplot as plt


# 파일 이름
filename = 'output.txt'

# NumPy를 사용하여 파일에서 배열 읽기
ns = np.loadtxt(filename)
rs = np.linspace(0, 100, ns.shape[0])

ns /= np.sum(ns)

ns_ideal = rs / ((rs ** 2 + 1) ** (3/2))
ns_ideal /= np.sum(ns_ideal)

# 결과

plt.plot(rs, ns, label="measured")
plt.plot(rs, ns_ideal, linestyle='--', label="ideal")
plt.title("distribution of charge density")

plt.legend()

plt.xlabel('r')
plt.ylabel('ratio')

plt.savefig("output/result.png")