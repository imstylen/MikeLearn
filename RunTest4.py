from x64.Release.MikeLearn import NeuralNetwork
from x64.Release.MikeLearn import ClassificationOptimizer
import matplotlib.pyplot as plt
import numpy as np

verbosity = 1

N = NeuralNetwork([2,2,3,2,2,1],['sigmoid','sigmoid','softmax'])
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
E = Opt.fit(1000000,0.05)

plt.plot(E)
plt.show()

print(Opt.predict([0,0]))
print(Opt.predict([1,0]))
print(Opt.predict([0,1]))
print(Opt.predict([1,1]))
