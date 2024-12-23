# legacy file

import numpy as np
import matplotlib.pyplot as plt

# sample theta, phi on sphere
# the dots must be sampled uniformly

# samples from uniform dist.

us = np.random.uniform(2)

# using cdf method, calculate theta. the dist must be shaped in sin().

thetas = np.acos(1 - 2* us[0])

# for phi, so  easy :)

phis = 2* np.pi * us[1]
