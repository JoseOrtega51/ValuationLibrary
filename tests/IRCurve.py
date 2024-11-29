import ValuationLibrary as ValLry
import numpy as np
import matplotlib.pyplot as plt

buckets = np.array([0.5, 1., 2., 3., 5., 10.])
rates = np.array([0.2, 0.25, 0.28, 0.29, 0.3, 0.32])
curve = ValLry.IRCurve(buckets, rates)

t = np.linspace(0.5,10.,100)
r_t = np.zeros(100)

rate_v = curve.getValue(t)
plt.plot(t, rate_v)
plt.plot(buckets,rates,'o')
plt.show()