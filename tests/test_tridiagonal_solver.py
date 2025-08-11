import ValuationLibrary as ValLry
import numpy as np
import pytest
from scipy.sparse import diags
from collections import deque

def test_tridiagonal_solver():
    # Test case 1: Simple 3x3 system
    # [2 -1  0][x1]   [1]
    # [-1 2 -1][x2] = [2]
    # [0 -1  2][x3]   [3]
    k = 2
    # Make sure arrays are in the correct format
    a = np.array([2.0, 2.0, 2.0], dtype=np.float64)        # diagonal (vector)
    c = np.array([-1.0, -1.0], dtype=np.float64)      # upper diagonal
    b = np.array([-1.0, -1.0], dtype=np.float64)      # lower diagonal
    d = np.array([1.0, 2.0, 3.0], dtype=np.float64)   # right hand side (vector)

    result = ValLry.math.trisol(k, a, b, c, d)

    a = np.array(a, dtype=np.float64)
    b = np.array(b, dtype=np.float64)
    c = np.array(c, dtype=np.float64)
    d = np.array(d, dtype=np.float64)
    
    # Verify the solution using numpy's solve for comparison
    
    diagonals = [b, a, c]
    positions = [-1, 0, 1]
    A = diags(diagonals, positions).toarray()
    expected = np.linalg.solve(A, d)
    
    assert len(result) == k + 1, "Solution vector has incorrect length"
    np.testing.assert_allclose(result, expected, rtol=1e-10, atol=1e-10)
    
    # Test case 2: 4x4 system with different values
    # [4 -1  0  0][x1]   [1]
    # [-1 4 -1 0][x2] = [2]
    # [0 -1  4 -1][x3]   [3]
    # [0  0 -1 4][x4]    [4]
    k = 3
    a = np.array([4.0, 4.0, 4.0, 4.0], dtype=np.float64)           # diagonal
    c = np.array([-3.0, -1.0, 1.0], dtype=np.float64)      # upper diagonal
    b = np.array([-1.0, -1.0, -1.0], dtype=np.float64)      # lower diagonal
    d = np.array([1.0, 2.0, 3.0, 4.0], dtype=np.float64)    # right hand side

    result = ValLry.math.trisol(k, a, b, c, d)
    
    a = np.array(a, dtype=np.float64)
    b = np.array(b, dtype=np.float64)
    c = np.array(c, dtype=np.float64)
    d = np.array(d, dtype=np.float64)

    # Verify the solution
    diagonals = [b, a, c]
    positions = [-1, 0, 1]
    A = diags(diagonals, positions).toarray()
    expected = np.linalg.solve(A, d)

    assert len(result) == k + 1, "Solution vector has incorrect length"
    np.testing.assert_allclose(result, expected, rtol=1e-10, atol=1e-10)

    # Test case 3: Error handling - inconsistent sizes
    with pytest.raises(Exception):
        # Wrong size for diagonal vector
        k = 3
        a_wrong = [2.0, 2.0]  # Wrong size for diagonal
        d = [1.0, 2.0, 3.0]
        ValLry.math.trisol(k, a_wrong, b, c, d)

if __name__ == "__main__":
    test_tridiagonal_solver()
