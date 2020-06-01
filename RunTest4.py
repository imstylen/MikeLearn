from x64.Release.MikeLearn import NeuralNetwork
from x64.Release.MikeLearn import ClassificationOptimizer
import matplotlib.pyplot as plt
import numpy as np

verbosity = 0

N = NeuralNetwork([2,2,1],['sigmoid','sigmoid','softmax'])
N.setLoggerVerbosity(verbosity)

X = [[0,1],
    [1,0],
    [1,1],
    [0,0]]

Y = [[1],
    [1],
    [0],
    [0]]

Opt = ClassificationOptimizer(N,X,Y)

Opt.setLoggerVerbosity(verbosity)
E = Opt.fit(10000,0.5)

plt.plot(E)
plt.show()

print(Opt.predict([[0,0],[1,0],[0,1],[1,1]]))

