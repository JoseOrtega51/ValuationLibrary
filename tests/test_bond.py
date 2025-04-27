import ValuationLibrary as ValLry
import numpy as np
import pytest

def test_rate_matches_benchmark():

    buckets = np.array([0.5, 1., 2., 3., 5., 10.])
    rates = np.array([0.02, 0.025, 0.028, 0.029, 0.03, 0.032])
    curve = ValLry.IRCurve(buckets, rates, "IRCurve")

    ############################# ZERO COUPON BOND #############################

    bond = ValLry.bond(1., 100, curve)
    NPV = bond.getNPV()
    YTM = bond.getYTM()
    Nominal = bond.getNominal()
    Maturity = bond.getMaturity()

    assert np.allclose(100., Nominal, atol=1e-5)
    assert np.allclose(1., Maturity, atol=1e-5)
    assert np.allclose(0.025, YTM, atol=1e-5)
    assert np.allclose(100*np.exp(-0.025*1.), NPV, atol=1e-5)


    ############################# COUPON BOND #############################

    bond_coupon = ValLry.bond(1., 100, [0.5, 1.], [0.02, 0.02], curve)
    NPV_coupon = bond_coupon.getNPV()
    YTM_coupon = bond_coupon.getYTM()
    Nominal_coupon = bond_coupon.getNominal()
    Maturity_coupon = bond_coupon.getMaturity()

    assert np.allclose(100., Nominal_coupon, atol=1e-5)
    assert np.allclose(1., Maturity_coupon, atol=1e-5)
    benchmark_NPV = 100*0.02*np.exp(-0.02*0.5) + 100*1.02*np.exp(-0.025*1.)
    assert np.allclose( benchmark_NPV, NPV_coupon, atol=1e-5)

    #check YTM
    price_YTM = 100*0.02*np.exp(-YTM_coupon*0.5) + 100*1.02*np.exp(-YTM_coupon*1.)
    assert np.allclose( price_YTM, NPV_coupon, atol=1e-5)

    ############################# COUPON BOND WITH MULTIPLE DATES #############################

    bond_coupon_multi = ValLry.bond(10., 100, [0.5, 1., 2., 3., 5., 10.], [0.01, 0.02, 0.03, 0.04, 0.05, 0.06], curve)
    NPV_coupon_multi = bond_coupon_multi.getNPV()
    YTM_coupon_multi = bond_coupon_multi.getYTM()
    Nominal_coupon_multi = bond_coupon_multi.getNominal()
    Maturity_coupon_multi = bond_coupon_multi.getMaturity()

    assert np.allclose(100., Nominal_coupon_multi, atol=1e-5)
    assert np.allclose(10., Maturity_coupon_multi, atol=1e-5)
    benchmark_NPV_multi = (
        100*0.01*np.exp(-0.02*0.5) +
        100*0.02*np.exp(-0.025*1.) +
        100*0.03*np.exp(-0.028*2.) +
        100*0.04*np.exp(-0.029*3.) +
        100*0.05*np.exp(-0.03*5.) +
        100*1.06*np.exp(-0.032*10.)
    )
    assert np.allclose(benchmark_NPV_multi, NPV_coupon_multi, atol=1e-5)

    #check YTM
    price_YTM_multi = (
        100*0.01*np.exp(-YTM_coupon_multi*0.5) +
        100*0.02*np.exp(-YTM_coupon_multi*1.) +
        100*0.03*np.exp(-YTM_coupon_multi*2.) +
        100*0.04*np.exp(-YTM_coupon_multi*3.) +
        100*0.05*np.exp(-YTM_coupon_multi*5.) +
        100*1.06*np.exp(-YTM_coupon_multi*10.)
    )
    assert np.allclose(price_YTM_multi, NPV_coupon_multi, atol=1e-5)




