from MikeLearn import NeuralNetwork
from MikeLearn import ClassificationOptimizer
import matplotlib.pyplot as plt
import numpy as np
import pickle
import time

#=======================================================
# Training Set
#=======================================================

modeldata = pickle.load( open( "mnist_data.p", "rb" ) )
X = modeldata['X']
Y = modeldata['Y']

X = np.array(X)
X = X/255
X = X.tolist()

X1 = X[0:49999]
Y1 = Y[0:49999]

nIn = len(X[0])
nOut = len(Y[0])

#=======================================================
# Model
#=======================================================
verbosity = 1

N = NeuralNetwork([nIn,100,nOut],['sigmoid','sigmoid','softmax'])
N.setLoggerVerbosity(verbosity)

Opt = ClassificationOptimizer(N,X1,Y1)

Opt.setLoggerVerbosity(verbosity)
start_time = time.time();
E = Opt.fit(25,0.1)
print("--- %s seconds ---" % (time.time() - start_time))

#plt.plot(E)
#plt.show()
#================================

X2 = X1
Y2 = Y1

XL = Opt.predict(X2)

print(len(XL))

correct = 0
for i,x in enumerate(XL):
    if XL[i].index(max(XL[i])) == Y[i].index(max(Y2[i])):
        correct = correct + 1

print("Training set Correct = " +  str(correct))
Accuracy = correct/len(XL)*100;
print("Accuracy = " + str(Accuracy))

#==================================================

X2 = X[50000:59999]
Y2 = Y[50000:59999]

XL = Opt.predict(X2)

print(len(XL))

correct = 0
for i,x in enumerate(XL):
    if XL[i].index(max(XL[i])) == Y[i].index(max(Y2[i])):
        correct = correct + 1

print("Testing set Correct = " +  str(correct))
Accuracy = correct/len(XL)*100;
print("Accuracy = " + str(Accuracy))
