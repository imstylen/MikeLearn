from x64.Release.MikeLearn import NeuralNetwork
from x64.Release.MikeLearn import ClassificationOptimizer
import matplotlib.pyplot as plt
import numpy as np
import pickle


#=======================================================
# Training Set
#=======================================================

modeldata = pickle.load( open( "modeldata.p", "rb" ) )
X = modeldata['X_flatten_list']
Y = modeldata['Y_flatten_list']
nIn = modeldata['ninputs']
nOut = modeldata['noutputs']

print(len(X))
print(len(Y))

verbosity = 1

N = NeuralNetwork([nIn,350,350,350,nOut],['sigmoid','sigmoid','softmax'])
N.setLoggerVerbosity(verbosity)

Opt = ClassificationOptimizer(N,X,Y)

Opt.setLoggerVerbosity(verbosity)
E = Opt.fit(1000000,0.05)

plt.plot(E)
plt.show()

print(Opt.predict([0,0]))
print(Opt.predict([1,0]))
print(Opt.predict([0,1]))
print(Opt.predict([1,1]))
