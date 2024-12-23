from mpi4py import MPI

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from scipy.stats import qmc




# mpi set
comm = MPI.COMM_WORLD

myrank = comm.Get_rank()
rank_size = comm.Get_size()

# mpi test
print("------------- Simulate for l=0.1 case ----------------")
for i in range(rank_size):
    if myrank == i:
        print("Processor " + str(i) + " is ready!")

# length
l = 0.1

# n = 2^m
ms = np.arange(7, 23)

# pi containors
if(myrank == 0):
    pi_est = np.zeros_like(ms, dtype=float)
    pi_est_err = np.zeros_like(ms, dtype=float)

# sample num
measure_num_per_mpi = 100

# quasi rng
sampler = qmc.Sobol(d=2, scramble=False)

# start
for i, m in enumerate(ms):
    if(myrank==0):
        print("Start for m = " + str(m))
    
    m_data = np.zeros(measure_num_per_mpi)
    
    for j in range(measure_num_per_mpi):
        
        #sample pos and theta from quasi random number (sobol)
        sample = sampler.random(2**m)
        sample = sample.T
        
        poss = sample[0]
        thetas = sample[1]*np.pi

        # calculate cos values
        
        coss = np.cos(thetas)
        
        #calculate the left point of bars
        
        left = poss - coss * 0.5 * l
        
        count = np.sum((left < 0))
        rat = 4*count / len(left)
        
        m_data[j] = 2.0 * l / rat

    m_data_global = comm.gather(m_data, root=0)

    if(myrank == 0):
        pi_est[i] = np.mean(m_data_global)
        pi_est_err[i] = np.std(m_data_global)


# analysis
if(myrank == 0):
    func = lambda x, a0, a1 : a0 + a1 * x
    pis_true = np.full(len(ms), np.pi)
    plot_ys = np.log2(np.abs(pi_est - pis_true))
    plot_yerrs = pi_est_err / np.abs(pi_est-np.pi)
    popt, pcov = curve_fit(func, ms, plot_ys, sigma = plot_yerrs, absolute_sigma = True)
    a0opt, a1opt = popt
    perr = np.sqrt(np.diag(pcov))
    plt.plot(ms, func(ms, a0opt, a1opt), linestyle='--')
    plt.xlabel('log10(# of Sample)')
    plt.ylabel('log2(pi_est - pi)')
    plt.errorbar(ms, plot_ys, yerr = plot_yerrs, fmt = 'ko')
    plt.savefig("output/result.png")