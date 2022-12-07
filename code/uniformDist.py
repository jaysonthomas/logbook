from matplotlib import pyplot as plt
import numpy as np

# A uniform distribution can be parameterized by two numbers, $a$ and $b$. 
# This distribution has probability 0 when $x<a$ or $x>b$ and probability 
# $1 / (b-a)$ otherwise.
# The code below is meant to demonstrate how the PDF, CDF, and 
# actual probabilities are all related. 

class UniformDistribution:
    def __init__(self,a,b):
        self.a = a
        self.b = b
        
    def f(self, x):
        """Probability Density Function (PDF) f(x)"""
        if x < self.a or x > self.b: 
            return 0.0
        return 1.0 / (self.b - self.a)
    
    def F(self,x):
        "Cumulative Density Function (CDF) F(x)"
        if x < self.a: return 0.0
        if x > self.b: return 1.0
        return (x - self.a) / (self.b - self.a)
    
    def p(self, x1, x2):
        """Calculates the probability that x1 < x < x2"""
        return self.F(x2) - self.F(x1)
    
    def plot_f(self, x_min, x_max):
        """Plots the PDF"""
        p = []
        X = np.linspace(x_min, x_max, 1000)
        for x in X:
            p.append(self.f(x))
        plt.plot(X, p)
        
    def plot_F(self, x_min, x_max):
        """Plots the CDF"""
        p = []
        X = np.linspace(x_min, x_max, 1000)
        for x in X:
            p.append(self.F(x))
        plt.plot(X, p)

# The code below plots the PDF and CDF of a uniform distribution. 
# Note that the **slope** of the CDF gives the **value** of the PDF. 

a, b = -1, 2
uniform = UniformDistribution(a,b)

uniform.plot_f(a-1, b+1)
uniform.plot_F(a-1, b+1)
plt.legend(["PDF of uniform distribution", 
            "CDF of uniform distribution"])
plt.show()

