import sys
import poly_wrapper as poly
from time import time
import matplotlib.pyplot as plt

def plotMulti(max_degree=10000, prime=13):
    x={i for i in range(10000)}
    k={}
    t={}
    m={}
    for i in range(max_degree):
        A = poly.generate(i)
        B = poly.generate(i)
        t0 = time()
        poly.karatsuba(A,B)
        t1 = time()
        k.append(t1-t0)
        t0 = time()
        poly.toomcook(A,B,prime)
        t1 = time()
        t.append(t1-t0)
        t0 = time()
        poly.mult(A,B)
        t1 = time()
        t.append(t1-t0)
    
    plt.plot(x,k, label="karatsuba")
    plt.plot(x,t, label="toom-cook")
    plt.plot(x,m, label="naive")
    plt.xlabel("Polynome degree")
    plt.ylabel("execution time (s)")
    plt.title("Performance of the multiplication algorithms")
    plt.legend()
    plt.show()


if __name__=="__main__":
    n = len(sys.argv)
    max_degree = 10000
    prime = 13
    if n == 3:
        prime = int(sys.argv[1])
        max_degree = int(sys.argv[2])

    plotMulti(max_degree, prime)
    



