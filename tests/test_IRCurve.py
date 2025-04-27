import ValuationLibrary as ValLry
import numpy as np
import pytest

def test_rate_matches_benchmark():
    t = np.linspace(0.55, 10, 100)

    buckets = np.array([0.5, 1., 2., 3., 5., 10.])
    rates = np.array([0.2, 0.25, 0.28, 0.29, 0.3, 0.32])
    curve = ValLry.IRCurve(buckets, rates, "IRCurve")
    rate_v1 = curve.getValue(t)

    buckets_str = ["6M", "1Y", "2Y", "3Y", "5Y", "10Y"]
    rates = np.array([0.2, 0.25, 0.28, 0.29, 0.3, 0.32])
    curve = ValLry.IRCurve(buckets_str, rates,  "IRCurve")
    rate_v2 = curve.getValue(t)


    buckets_str = ["6M3D", "1Y1M10D", "2Y10M", "3Y", "5Y", "10Y1M"]
    buckets = np.array([0.5 + 3/360, 1. + 1/12 + 10/360, 2. + 10/12, 3., 5., 10. + 1/12])
    rates = np.array([0.2, 0.25, 0.28, 0.29, 0.3, 0.32])
    curve = ValLry.IRCurve(buckets_str, rates, "IRCurve")
    rate_v3 = curve.getValue(t)

    np.savetxt("tests/output/IRCurve.csv", np.column_stack((t, rate_v1, rate_v2, rate_v3)), delimiter=",", header="t,rate_v1,rate_v2,rate_v3", comments='')

    benchmark = np.loadtxt("tests/data/IRCurve.csv", delimiter=",", skiprows=1)
    assert np.allclose(np.column_stack((t, rate_v1, rate_v2, rate_v3)), benchmark, atol=1e-5)





