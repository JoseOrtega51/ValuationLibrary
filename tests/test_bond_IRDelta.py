import ValuationLibrary as ValLry
import numpy as np
import pytest

def test_rate_matches_benchmark():

    buckets = np.array(["6M", "1Y", "2Y", "3Y", "5Y", "10Y"])
    rates = np.array([0.02, 0.025, 0.028, 0.029, 0.03, 0.032])
    curve = ValLry.IRCurve(buckets, rates, "IRCurve")

    ############################# ZERO COUPON BOND #############################

    bond = ValLry.bond(1., 100, curve)
    NPV = bond.getNPV()

    bond.computeIRDelta()
    IRDelta = bond.getIRDelta()
    print("IRDelta: ", IRDelta)

    IR_Delta_bumped = {}
    for i in range(len(buckets)):
        rates_bumped = rates.copy()
        rates_bumped[i] += 0.01 * rates[i]
        curve_bumped = ValLry.IRCurve(buckets, rates_bumped, "IRCurve_bumped")
        bond_bumped = ValLry.bond(1., 100, curve_bumped)
        NPV_bumped = bond_bumped.getNPV()
        IR_Delta_bumped[buckets[i]] = (NPV_bumped - NPV)
    
    for key in IRDelta:
        assert IRDelta[key] == pytest.approx(IR_Delta_bumped[key], rel=1e-5)

    ############################# COUPON BOND #############################

    bond_coupon = ValLry.bond(1., 100, [0.5, 1.], [0.02, 0.02], curve)
    NPV_coupon = bond_coupon.getNPV()

    bond_coupon.computeIRDelta()
    IRDelta_coupon = bond_coupon.getIRDelta()
    print("IRDelta_coupon: ", IRDelta_coupon)

    IRDelta_coupon_bumped = {}
    for i in range(len(buckets)):
        rates_bumped = rates.copy()
        rates_bumped[i] += 0.01 * rates[i]
        curve_bumped = ValLry.IRCurve(buckets, rates_bumped, "IRCurve_bumped")
        bond_coupon_bumped = ValLry.bond(1., 100, [0.5, 1.], [0.02, 0.02], curve_bumped)
        NPV_coupon_bumped = bond_coupon_bumped.getNPV()
        IRDelta_coupon_bumped[buckets[i]] = (NPV_coupon_bumped - NPV_coupon)

    for key in IRDelta_coupon:
        assert IRDelta_coupon[key] == pytest.approx(IRDelta_coupon_bumped[key], rel=1e-5)

    ############################# COUPON BOND WITH MULTIPLE DATES #############################

    bond_coupon_multi = ValLry.bond(10., 100, [0.7, 1.2, 2.2, 3.2, 4.2, 5.2], [0.01, 0.02, 0.03, 0.04, 0.05, 0.06], curve)
    NPV_coupon_multi = bond_coupon_multi.getNPV()
    
    bond_coupon_multi.computeIRDelta()
    IRDelta_coupon_multi = bond_coupon_multi.getIRDelta()
    print("IRDelta_coupon_multi: ", IRDelta_coupon_multi)

    IRDelta_coupon_multi_bumped = {}

    for i in range(len(buckets)):
        rates_bumped = rates.copy()
        rates_bumped[i] += 0.01 * rates[i]
        curve_bumped = ValLry.IRCurve(buckets, rates_bumped, "IRCurve_bumped")
        bond_coupon_multi_bumped = ValLry.bond(10., 100,[0.7, 1.2, 2.2, 3.2, 4.2, 5.2] , [0.01, 0.02, 0.03, 0.04, 0.05, 0.06], curve_bumped)
        NPV_coupon_multi_bumped = bond_coupon_multi_bumped.getNPV()
        IRDelta_coupon_multi_bumped[buckets[i]] = (NPV_coupon_multi_bumped - NPV_coupon_multi)

    for key in IRDelta_coupon_multi:
        assert IRDelta_coupon_multi[key] == pytest.approx(IRDelta_coupon_multi_bumped[key], rel=1e-5)

if __name__ == "__main__":
    test_rate_matches_benchmark()



