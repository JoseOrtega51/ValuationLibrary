import ValuationLibrary as ValLry
import numpy as np
import time
import scipy.linalg

"""
This short code compares the performance of different implementations of the Cholesky factorization.

Kyberion's implementation is faster than a pure python implementation but slower that scipy.linalg.cholesky (which is a wrapper for the highly optimized LAPACK library)
"""

def cholesky_python(A):
        n = len(A)
        L = np.zeros_like(A)
        for i in range(n):
            for j in range(i+1):
                if i == j:
                    L[i,i] = np.sqrt(A[i,i] - np.sum(L[i,:i]**2))
                else:
                    L[i,j] = (A[i,j] - np.sum(L[i,:j] * L[j,:j])) / L[j,j]
        return L


for n in [10, 100, 1000]:

    rng = np.random.RandomState(42)  # Use fixed seed for reproducibility
    A_temp = rng.rand(n, n)
    # Make it symmetric positive definite by multiplying with its transpose and adding identity
    A = A_temp.dot(A_temp.T) + np.eye(n)

    start_time = time.time()

    Chol_1 = ValLry.math.choleskyDecomposition(A)

    final_time = time.time()

    print(f"Kyberion   Cholesky decomposition took {final_time - start_time:.4f} seconds for matrix of size {n}x{n}")

    start_time = time.time()

    Chol_2 = scipy.linalg.cholesky(A, lower=True)

    final_time = time.time()

    print(f"Scipy Cholesky decomposition took {final_time - start_time:.4f} seconds for matrix of size {n}x{n}")

    start_time = time.time()

    Chol_3 = cholesky_python(A)

    final_time = time.time()

    print(f"Pure Python Cholesky decomposition took {final_time - start_time:.4f} seconds for matrix of size {n}x{n}")
