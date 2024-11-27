# Valuation Library

Python library compiled in C++ to work with financial instruments and portfolios in an OOP style that mimics trading (in a didactic and naive way). You may configure options with their characteristics, choose a pricing model and set up a portfolio which you can price at once. This gives valuable insight about trading strategies.

The most important class is ````FinancialInstrument````, which is not directly accesible from python, but many of its inherited classes are. One example is ````EuropeanOption````, which is a class modelling a European Option, another example is ````Portfolio````, which models a real portfolio. You can add different options to the Portfolio and then price it for an array of times or underlying asset prices. You can also buy or short other portfolios to a big Portfolio, creating a Trading Book of different strategies.

You may find some examples that you can easily open in colab:
- [Butterfly spread strategy](https://github.com/JoseOrtega51/ValuationLibrary/blob/main/examples/butterfly_spread_colab.ipynb).
- [Straddle strategy](https://github.com/JoseOrtega51/ValuationLibrary/blob/main/examples/Straddle_colab.ipynb)

## Installation:
### Colab:
The easiest way to use this repository is to clone it in colab and installing in just by copying the following cell:

```python

!git clone https://github.com/JoseOrtega51/ValuationLibrary.git
!cd ValuationLibrary/ && git checkout Stable
!apt-get update
!apt-get install -y build-essential
!pip install pybind11 setuptools
!cd ValuationLibrary/ && pip install .

import ValuationLibrary as ValLry

```

### Locally:
This way is more complicated and will probably take some time.

You should have a C++ compiler, python and pybind11 to install it. I strongly recommend creating a virtual environmenet for this and pip installing the required and standard libraries (such as numpy or matplotlib). It has been tested only in Windows 64 and Colab, so it might not work in other OS. The branch [Stable](https://github.com/JoseOrtega51/ValuationLibrary/tree/Stable) is the one that has been tested, so probably is best to start by trying to make that banch work.

If you have git in your computer you should be able to clone it. If not, just download and copy the unzipped folder in your desired destination.  Then run the following line:
```shell
python setup.py install
```

WARNING: The library is still under construction and for now it only allows Black Scholes pricing and European options. However, the use of portfolios allows to recreate many complex strategies.
