from MikeLearn import NeuralNetwork
from MikeLearn import ClassificationOptimizer
import matplotlib.pyplot as plt
import time

#=======================================================
# Training Set
#=======================================================

X = [[0,1],[1,0],[1,1],[0,0]]
Y = [[1],[1],[0],[0]]

nIn = len(X[0])
nOut = len(Y[0])

#=======================================================
# Model
#=======================================================
verbosity = 0

N = NeuralNetwork([nIn,2,nOut],['sigmoid','sigmoid','softmax'])
N.setLoggerVerbosity(verbosity)

Opt = ClassificationOptimizer(N,X,Y)

Opt.setLoggerVerbosity(verbosity)
start_time = time.time();
E = Opt.fit(10000,0.1)
print("--- %s seconds ---" % (time.time() - start_time))

#plt.plot(E)
#plt.show()
#================================

X2 = X
Y2 = Y

XL = Opt.predict(X2)

print(XL)


