import pytest
import numpy as np
import os
import csv
import pandas as pd
from ValuationLibrary import IRCurve, bond, portfolio, math

# Helper function to save results to a CSV file
def save_to_csv(filepath, data, header=None):
    """Save data to a CSV file with optional header"""
    os.makedirs(os.path.dirname(filepath), exist_ok=True)
    df = pd.DataFrame(data)
    if header:
        df.columns = header
    df.to_csv(filepath, index=False)

# Helper function to compare results with reference values
def compare_with_reference(filepath, data, header=None, rtol=1e-5, atol=1e-8):
    """Compare current results with reference values
    
    If reference file doesn't exist, creates it (first run case)
    Otherwise compares the data with the reference
    """
    # Create reference file if it doesn't exist
    if not os.path.exists(filepath):
        print(f"Creating reference file: {filepath}")
        save_to_csv(filepath, data, header)
        return True
    
    # Load reference data
    ref_df = pd.read_csv(filepath)
    
    # Convert current data to DataFrame for comparison
    curr_df = pd.DataFrame(data, columns=header if header else None)
    
    # Check if shapes match
    assert ref_df.shape == curr_df.shape, f"Shape mismatch: reference {ref_df.shape} vs current {curr_df.shape}"
    
    # Compare values
    for col in ref_df.columns:
        # Convert to appropriate type before comparison
        ref_values = ref_df[col].values
        curr_values = curr_df[col].values
        
        # If the column contains strings, compare them directly
        if curr_df[col].dtype == object or ref_df[col].dtype == object:
            aux_ref = ref_df[col]
            aux_curr = curr_df[col]
            if isinstance(aux_ref[0], str) or isinstance(aux_curr[0], str):
                aux_ref = eval(aux_ref[0])
                aux_curr = aux_curr[0]

            if isinstance(aux_curr, dict) or isinstance(aux_ref, dict):
                for key in aux_curr.keys():
                    np.allclose(aux_curr[key], aux_ref[key], rtol=rtol, atol=atol)
            else:
                # Convert any numeric values to strings for comparison
                ref_str = [float(x) for x in ref_values]
                curr_str = [float(x) for x in curr_values]
                assert np.allclose(ref_str, curr_str, rtol=rtol, atol=atol), f"Values in column {col} don't match"
        else:
            # For numeric columns, use np.allclose
            assert np.allclose(ref_values, curr_values, rtol=rtol, atol=atol), \
                f"Numeric values in column {col} don't match reference within tolerance"
    
    return True

def test_ircurve_creation_and_values():
    # Test IRCurve creation with double tenors
    tenors = np.array([0.0, 1.0, 2.0, 5.0, 10.0])
    rates = np.array([0.02, 0.025, 0.03, 0.035, 0.04])
    curve = IRCurve(tenors, rates, "test_curve")
    
    # Test getValue with single point
    value = curve.getValue(2.5)
    assert isinstance(value, float)
    assert 0.03 <= value <= 0.035  # Value should be interpolated between 2Y and 5Y rates
    
    # Test getValue with array - generate more points for better curve validation
    test_points = np.linspace(0.0, 10.0, 100)
    values = curve.getValue(test_points)
    assert isinstance(values, np.ndarray)
    assert len(values) == len(test_points)
    
    # Save interpolated curve results to CSV and compare with reference
    results = np.column_stack((test_points, values))
    ref_path = os.path.join('tests', 'reference', 'ir_curve_interpolation.csv')
    compare_with_reference(ref_path, results, header=['tenor', 'rate'])
    
    # Test IRCurve creation with string tenors
    string_tenors = ["0D", "1Y", "2Y", "5Y", "10Y"]
    curve_str = IRCurve(string_tenors, rates, "test_curve_str")
    value_str = curve_str.getValue(2.5)
    assert isinstance(value_str, float)

def test_zero_coupon_bond():
    # Create an IR curve for testing
    tenors = np.array([0.0, 1.0, 2.0, 5.0, 10.0])
    rates = np.array([0.02, 0.025, 0.03, 0.035, 0.04])
    curve = IRCurve(tenors, rates, "test_curve")
    
    # Create a zero-coupon bond
    maturity = 5.0
    nominal = 1000.0
    zcb = bond(maturity, nominal, curve)
    
    # Test basic properties
    assert zcb.getNominal() == nominal
    assert zcb.getMaturity() == maturity
    
    # Test pricing
    price = zcb.price()
    assert isinstance(price, float)
    assert price < nominal  # Present value should be less than nominal for positive rates
    
    # Test IR Delta
    zcb.computeIRDelta()
    ir_delta = zcb.getIRDelta()
    
    # Save results to CSV and compare with reference
    results = np.array([[maturity, nominal, price, ir_delta]])
    ref_path = os.path.join('tests', 'reference', 'zero_coupon_bond.csv')
    compare_with_reference(ref_path, results, header=['maturity', 'nominal', 'price', 'ir_delta'])

def test_coupon_bond():
    # Create an IR curve for testing
    tenors = np.array([0.0, 1.0, 2.0, 5.0, 10.0])
    rates = np.array([0.02, 0.025, 0.03, 0.035, 0.04])
    curve = IRCurve(tenors, rates, "test_curve")
    
    # Create a coupon bond
    maturity = 5.0
    nominal = 1000.0
    coupon_dates = [1.0, 2.0, 3.0, 4.0, 5.0]
    coupon_yields = [0.03, 0.03, 0.03, 0.03, 0.03]  # 3% annual coupon
    
    cb = bond(maturity, nominal, coupon_dates, coupon_yields, curve)
    
    # Test basic properties
    assert cb.getNominal() == nominal
    assert cb.getMaturity() == maturity
    
    # Test pricing and YTM
    price = cb.price()
    assert isinstance(price, float)
    
    ytm = cb.getYTM()
    assert isinstance(ytm, float)
    
    # Test NPV
    npv = cb.getNPV()
    assert isinstance(npv, float)
    
    # Test IR Delta
    cb.computeIRDelta()
    ir_delta = cb.getIRDelta()

    # Save results to CSV and compare with reference
    results = np.array([[maturity, nominal, price, ytm, npv, ir_delta]])
    ref_path = os.path.join('tests', 'reference', 'coupon_bond.csv')
    compare_with_reference(ref_path, results, 
                          header=['maturity', 'nominal', 'price', 'ytm', 'npv', 'ir_delta'])

# def test_portfolio():
#     # Create test instruments
#     tenors = np.array([0.0, 1.0, 2.0, 5.0, 10.0])
#     rates = np.array([0.02, 0.025, 0.03, 0.035, 0.04])
#     curve = IRCurve(tenors, rates, "test_curve")
    
#     bond1 = bond(5.0, 1000.0, curve)  # Zero-coupon bond
#     bond2 = bond(3.0, 1000.0, [1.0, 2.0, 3.0], [0.03, 0.03, 0.03], curve)  # Coupon bond
    
#     # Create portfolio
#     port = portfolio()
    
#     # Test adding instruments
#     port.addInstrument(bond1, "bond1")
#     port.addInstrument(bond2, "bond2")
    
#     # Test getting label list
#     labels = port.getLabelList()
#     assert isinstance(labels, list)
#     assert "bond1" in labels
#     assert "bond2" in labels
    
#     # Test portfolio pricing
#     price_full = port.price()
#     assert isinstance(price_full, float)
#     assert price_full > 0
    
#     # Test removing instrument
#     port.eraseInstrument("bond1")
#     updated_labels = port.getLabelList()
#     assert "bond1" not in updated_labels
#     assert "bond2" in updated_labels
    
#     # Price after removal
#     price_partial = port.price()
    
#     # Save results to CSV and compare with reference
#     # Using a list of dictionaries for clearer handling of mixed types
#     results = [
#         {'portfolio_type': 'full_portfolio', 'price': price_full},
#         {'portfolio_type': 'partial_portfolio', 'price': price_partial}
#     ]
#     ref_path = os.path.join('tests', 'reference', 'portfolio.csv')
#     # Create DataFrame directly which handles mixed types better
#     df = pd.DataFrame(results)
    
#     # If reference file doesn't exist, create it
#     if not os.path.exists(ref_path):
#         print(f"Creating reference file: {ref_path}")
#         os.makedirs(os.path.dirname(ref_path), exist_ok=True)
#         df.to_csv(ref_path, index=False)
#     else:
#         # Load reference data
#         ref_df = pd.read_csv(ref_path)
        
#         # Check shapes
#         assert ref_df.shape == df.shape, f"Shape mismatch: reference {ref_df.shape} vs current {df.shape}"
        
#         # Compare portfolio types (strings)
#         assert list(ref_df['portfolio_type']) == list(df['portfolio_type']), "Portfolio types don't match"
        
#         # Compare prices (floats)
#         assert np.allclose(ref_df['price'].values, df['price'].values), "Portfolio prices don't match"

def test_math_tools():
    # Test normalCDF
    test_values = np.linspace(-3.0, 3.0, 20)
    cdf_values = np.array([math.normalCDF(x) for x in test_values])
    
    # Check specific values
    assert math.normalCDF(0.0) == pytest.approx(0.5, abs=1e-10)
    
    # Save normalCDF results
    normal_results = np.column_stack((test_values, cdf_values))
    ref_path = os.path.join('tests', 'reference', 'normalCDF.csv')
    compare_with_reference(ref_path, normal_results, header=['x', 'cdf'])
    
    # Test trisol (tridiagonal solver)
    n = 5
    b = np.ones(n-1)  # sub-diagonal
    a = 2 * np.ones(n)  # main diagonal
    c = np.ones(n-1)  # super-diagonal
    d = np.ones(n)  # right-hand side
    
    x = math.trisol(n-1, a, b, c, d)
    assert isinstance(x, np.ndarray)
    assert len(x) == n
    
    # Save trisol results
    result_df = pd.DataFrame({
        'index': np.arange(n),
        'solution': x
    })
    
    tri_ref_path = os.path.join('tests', 'reference', 'trisol.csv')
    # If reference file doesn't exist, create it
    if not os.path.exists(tri_ref_path):
        print(f"Creating reference file: {tri_ref_path}")
        os.makedirs(os.path.dirname(tri_ref_path), exist_ok=True)
        result_df.to_csv(tri_ref_path, index=False)
    else:
        # Load reference data and compare
        ref_df = pd.read_csv(tri_ref_path)
        assert ref_df.shape == result_df.shape, "Shape mismatch in trisol results"
        assert np.allclose(ref_df['solution'].values, result_df['solution'].values), "Trisol solutions don't match"
        
    # Test Cholesky decomposition
    # Create a symmetric positive definite matrix
    n = 3
    # Start with a random matrix
    rng = np.random.RandomState(42)  # Use fixed seed for reproducibility
    A_temp = rng.rand(n, n)
    # Make it symmetric positive definite by multiplying with its transpose and adding identity
    A = A_temp.dot(A_temp.T) + np.eye(n)
    
    # Compute Cholesky decomposition
    L = math.choleskyDecomposition(A)
    assert isinstance(L, np.ndarray)
    assert L.shape == (n, n)
    
    # Verify the decomposition: A should be approximately equal to L * L^T
    L_transpose = L.T
    A_reconstructed = L.dot(L_transpose)
    assert np.allclose(A, A_reconstructed, rtol=1e-10, atol=1e-10)
    
    # Check that L is lower triangular (all elements above diagonal are zero)
    for i in range(n):
        for j in range(i+1, n):
            assert abs(L[i, j]) < 1e-10
    
    # Save Cholesky results
    chol_ref_path = os.path.join('tests', 'reference', 'cholesky.csv')
    
    # Reshape for dataframe
    chol_df = pd.DataFrame(L)
    
    # If reference file doesn't exist, create it
    if not os.path.exists(chol_ref_path):
        print(f"Creating reference file: {chol_ref_path}")
        os.makedirs(os.path.dirname(chol_ref_path), exist_ok=True)
        chol_df.to_csv(chol_ref_path, index=False)
    else:
        # Load reference data and compare
        ref_df = pd.read_csv(chol_ref_path)
        ref_df.columns = chol_df.columns  # Ensure columns match for comparison
        assert ref_df.shape == chol_df.shape, "Shape mismatch in Cholesky results"
        pd.testing.assert_frame_equal(ref_df, chol_df, check_dtype=False, check_index_type=False, check_column_type = False)

if __name__ == "__main__":
    pytest.main([__file__])