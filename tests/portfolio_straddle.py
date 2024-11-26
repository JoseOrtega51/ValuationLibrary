import ValuationLibrary as ValLry
import numpy as np
import matplotlib.pyplot as plt


#Define a strategy portfolio
Straddle = ValLry.portfolio()


################## CREATE STRADDLE ####################################

#Define a European Option
OpcionCall = ValLry.EuropeanOption(ValLry.OptionType.PUT,100., 1.)

#set the default model
OpcionCall.BSM.setup(0.2, 0.02)
OpcionCall.setPricingModel(ValLry.PricingModel.BLACK_SCHOLES)

#Add option to portfolio
Straddle.longInstrument("Option_PUT", OpcionCall)

#Define a European Option
OpcionCall = ValLry.EuropeanOption(ValLry.OptionType.CALL,100., 1.)

#set the default model
OpcionCall.BSM.setup(0.2, 0.02)
OpcionCall.setPricingModel(ValLry.PricingModel.BLACK_SCHOLES)

#Add option to portfolio
Straddle.longInstrument("Option_CALL", OpcionCall)

#get the list of instruments in the porfolio
portfolioList = Straddle.getLabelList()
print(portfolioList)

#####################################################################

# Price the straddle
S = np.linspace(0., 200., 100)
Value_straddle = Straddle.price(0.99,S)
plt.plot(S,Value_straddle)
plt.show()

# Create new big portfolio
book = ValLry.portfolio()

book.shortInstrument("Stradle", Straddle)

S = np.linspace(0., 200., 100)
Value_book = book.price(0.99,S)
plt.plot(S,Value_book)
plt.show()
