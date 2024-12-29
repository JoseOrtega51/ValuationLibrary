import ValuationLibrary as ValLry
import numpy as np
import matplotlib.pyplot as plt

#BSM parameters
vol = 0.2
r = 0.02

#Define a strategy portfolio
BFS = ValLry.portfolio()

################## CREATE BUTTERFLY SPREAD ####################################
dK = 10.
K0 = 100.

strikes = [K0 - dK, K0, K0, K0 + dK]
positions = ['L', 'S', 'S', 'L']

i = 0
for K in strikes:

    #Define a European Option
    OpcionCall = ValLry.EuropeanOption(ValLry.OptionType.CALL,K, 1.)

    #set the default model
    OpcionCall.BSM.setup(vol, r)
    OpcionCall.setPricingModel(ValLry.PricingModel.BLACK_SCHOLES)

    #Add option to portfolio
    if(positions[i] == 'L'):
        BFS.longInstrument("Option_{}".format(i), OpcionCall)
    else:
        BFS.shortInstrument("Option_{}".format(i), OpcionCall)

    i += 1

#####################################################################

# Payoff butterfly spread
S = np.linspace(K0 - 2 * dK, K0 + 2 * dK, 100)
Value_straddle = BFS.price(1.,S)
plt.plot(S,Value_straddle)
plt.show()

# Price butterfly spread
Value_straddle = BFS.price(0.,S)
plt.plot(S,Value_straddle)
plt.show()

print("d2C/dK2 =(aprox)= {}".format(BFS.price(0.,K0)/(dK)**2))

#####################################################################

# Delta butterfly spread
Value_straddle = BFS.delta(0.,S)
plt.plot(S,Value_straddle)
plt.show()
