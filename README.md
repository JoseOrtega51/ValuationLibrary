### Valuation Library

Python library compiled in C++ to work with financial instruments and portfolios in an OOP style that mimics trading (in a didactic and naive way). You may configure options with their characteristics, choose a pricing model and set up a portfolio which you can price at once. This gives valuable insight about trading strategies.

```python

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

# Price the straddle at time t = 0.8
S = np.linspace(0., 200., 100)
Value_straddle = Straddle.price(0.99,S)
plt.plot(S,Value_straddle)
plt.show()

```

![Price](https://github.com/JoseOrtega51/ValuationLibrary/blob/main/readme_files/straddle.png)

The library is still under construction and for now it only allows Black Scholes pricing and European options. However, the use of portfolios allows to recreate many complex strategies.
